import Types::*;
import ProcTypes::*;
import CMemTypes::*;
import RFile::*;
import IMemory::*;
import DMemory::*;
import Decode::*;
import Exec::*;
import CsrFile::*;
import Vector::*;
import Fifo::*;
import Ehr::*;
import GetPut::*;

typedef struct {
  Instruction inst;
  Addr pc;
  Addr ppc;
  Bool epoch;
} Fetch2Decode deriving(Bits, Eq);

typedef struct {
  DecodedInst dInst;
  Addr pc;
  Addr ppc;
  Bool epoch;
} Decode2Execute deriving(Bits, Eq);

(*synthesize*)
module mkProc(Proc);
  Reg#(Addr)    pc  <- mkRegU;
  RFile         rf  <- mkRFile;
  IMemory     iMem  <- mkIMemory;
  DMemory     dMem  <- mkDMemory;
  CsrFile     csrf <- mkCsrFile;

  Reg#(ProcStatus)   stat		<- mkRegU;
  Fifo#(1,ProcStatus) statRedirect <- mkBypassFifo;

  // Control hazard handling Elements
  Reg#(Bool) fEpoch <- mkRegU;
  Reg#(Bool) eEpoch <- mkRegU;

  Fifo#(1, Addr)         execRedirect <- mkBypassFifo;

  Fifo#(2, Fetch2Decode)  f2d <- mkPipelineFifo;
  Fifo#(2, Decode2Execute) d2e <- mkPipelineFifo;

  Bool memReady = iMem.init.done() && dMem.init.done();
  rule test (!memReady);
    let e = tagged InitDone;
    iMem.init.request.put(e);
    dMem.init.request.put(e);
  endrule


  rule doFetch(csrf.started && stat == AOK);
		Addr pc_tmp;
		Bool epo_tmp;

    if(execRedirect.notEmpty) begin
      execRedirect.deq;
	  	pc_tmp = execRedirect.first;
	  	epo_tmp = !fEpoch;
    end
		else begin
			pc_tmp = pc;
			epo_tmp = fEpoch;
		end


		let inst = iMem.req(pc_tmp);
		let ppc = pc_tmp + 4;

		pc <= ppc;
		fEpoch <= epo_tmp;

    f2d.enq(Fetch2Decode{inst:inst, pc:pc_tmp, ppc:ppc, epoch:epo_tmp}); 
    $display("Fetch : from Pc %d, fEpoch %b\n", pc_tmp, epo_tmp);
  endrule


  rule doDecode(csrf.started && stat == AOK);
    let inst   = f2d.first.inst;
    let _pc   = f2d.first.pc;
    let ppc    = f2d.first.ppc;
    let iEpoch = f2d.first.epoch;
    f2d.deq;

		if(iEpoch == eEpoch) begin
		d2e.enq(Decode2Execute{dInst:decode(inst), pc:_pc, ppc:ppc, epoch:iEpoch});
		end
		$display("Decode : inst from Pc %d, epoch %b", _pc, iEpoch);
 endrule


  rule doRest(csrf.started && stat == AOK);
		let dInst = d2e.first.dInst;
		let iiType = dInst.iType;
		d2e.deq;
		$display("Execute : inst form Pc %d, iEpoch %b, eEpoch %b", d2e.first.pc, d2e.first.epoch, eEpoch);
    if(d2e.first.epoch == eEpoch) begin
        // Register Read 
        let rVal1 = isValid(dInst.src1) ? rf.rd1(validValue(dInst.src1)) : ?;
        let rVal2 = isValid(dInst.src2) ? rf.rd2(validValue(dInst.src2)) : ?;
        let csrVal = isValid(dInst.csr) ? csrf.rd(validValue(dInst.csr)) : ?;

    		// Execute         
        let eInst = exec(dInst, rVal1, rVal2, d2e.first.pc, d2e.first.ppc, csrVal);               
        
        if(eInst.mispredict) begin
          eEpoch <= !eEpoch;
          execRedirect.enq(eInst.addr);
		 		 	csrf.incBPMissCnt;

		  		case(iiType)
						J : csrf.incMissInstTypeCnt(JMiss);
						Jr : csrf.incMissInstTypeCnt(JRMiss);
						Br : csrf.incMissInstTypeCnt(BRMiss);
		 			endcase

          $display("jump! :mispredicted, address %d eEpoch %b", eInst.addr, eEpoch);
        end
				else begin
		  		case(iiType)
						J : csrf.incMissInstTypeCnt(J_);
						Jr : csrf.incMissInstTypeCnt(JR_);
						Br : csrf.incMissInstTypeCnt(BR_);
		  		endcase
  			end

      //Memory 
      let iType = eInst.iType;
      case(iType)
        Ld :
        begin
          let d <- dMem.req(MemReq{op: Ld, addr: eInst.addr, data: ?});
          eInst.data = d;
        end

        St:
        begin
          let d <- dMem.req(MemReq{op: St, addr: eInst.addr, data: eInst.data});
        end
        Unsupported :
        begin
          $fwrite(stderr, "ERROR: Executing unsupported instruction\n");
          $finish;
        end
      endcase

      //WriteBack 
      if (isValid(eInst.dst)) begin
          rf.wr(fromMaybe(?, eInst.dst), eInst.data);
      end
      csrf.wr(eInst.iType == Csrw ? eInst.csr : Invalid, eInst.data);

      case(iiType)
		J : csrf.incInstTypeCnt(Ctr);
		Jr : csrf.incInstTypeCnt(Ctr);
		Br : csrf.incInstTypeCnt(Ctr);
		Ld : csrf.incInstTypeCnt(Mem);
		St : csrf.incInstTypeCnt(Mem);
	  endcase
  end
  endrule

  rule upd_Stat(csrf.started);
	$display("Stat update");
  	statRedirect.deq;
    stat <= statRedirect.first;
  endrule

  method ActionValue#(CpuToHostData) cpuToHost;
    let retV <- csrf.cpuToHost;
    return retV;
  endmethod

  method	Action hostToCpu(Bit#(32) startpc) if (!csrf.started && memReady);
    csrf.start(0);
    eEpoch <= False;
    fEpoch <= False;
    pc <= startpc;
    stat <= AOK;
  endmethod

  interface iMemInit = iMem.init;
  interface dMemInit = dMem.init;

endmodule
