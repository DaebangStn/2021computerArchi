import Types::*;
import ProcTypes::*;
import CMemTypes::*;
import MemInit::*;
import RFile::*;
import IMemory::*;
import DMemory::*;
import Decode::*;
import Exec::*;
import CsrFile::*;
import Fifo::*;
import Scoreboard::*;
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
  RFile         rf  <- mkBypassRFile;  // Refer to p.20, M10
  IMemory     iMem  <- mkIMemory;
  DMemory     dMem  <- mkDMemory;
  CsrFile     csrf <- mkCsrFile;

  Reg#(Bool) fEpoch <- mkRegU;
  Reg#(Bool) eEpoch <- mkRegU;
  Fifo#(1, Addr)  execRedirect <- mkBypassFifo; 

  Fifo#(1, Fetch2Decode)  f2d <- mkPipelineFifo;
	Fifo#(1, Decode2Execute) d2e <- mkPipelineFifo;
	Fifo#(1, Maybe#(ExecInst)) e2m <- mkPipelineFifo;
	Fifo#(1, Maybe#(ExecInst)) m2w <- mkPipelineFifo;

  Scoreboard#(4) sb <- mkPipelineScoreboard;

/* TODO: Lab 6-1: Implement 5-stage pipelined processor with scoreboard. 
   Scoreboard is already implemented. Refer to the scoreboard module and learning materials about scoreboard(ppt). */
  rule doFetch(csrf.started);
  	let inst = iMem.req(pc);
   	let ppc = pc + 4;

		// prediction 1 dead cycle exists
    if(execRedirect.notEmpty) begin
      execRedirect.deq;
      pc <= execRedirect.first;
      fEpoch <= !fEpoch;
    end
    else begin
      pc <= ppc;
    end
 
    f2r.enq(Fetch2Rest{inst:inst, pc:pc, ppc:ppc, epoch:fEpoch}); 
    $display("Fetch : from Pc %d , \n", pc);
  endrule

	rule doDecode(csrf.started);
		let temp = f2d.first;
		let dInst = decode(temp.inst);

		let stall = sb.search1(dInst.src1) || sb.search2(dInst.src2);

		if(!stall) begin
			f2d.deq;

			sb.insert(dInst.dst);

			if(iEpoch == eEpoch) begin
				let temp = f2d.first;
				let dInst = decode(temp.inst);
				d2e.enq(Decode2Execute{dInst:dInst, pc:temp.pc, ppc:temp.ppc, epoch:iEpoch});
			end

		end

	   $display("Decode : inst from Pc %d, epoch %b", f2d.first.pc, iEpoch);
	endrule

	rule doExecute(csrf.started);
		d2e.deq;

		let temp = d2e.first;
		let dInst = temp.dInst;

		if(temp.epoch == eEpoch) begin
      let rVal1 = isValid(dInst.src1) ? rf.rd1(validValue(dInst.src1)) : ?;
      let rVal2 = isValid(dInst.src2) ? rf.rd2(validValue(dInst.src2)) : ?;
      let csrVal = isValid(dInst.csr) ? csrf.rd(validValue(dInst.csr)) : ?;

    	// Execute         
      let eInst = exec(dInst, rVal1, rVal2, temp.pc, temp.ppc, csrVal);               
        
      if(eInst.mispredict) begin
        eEpoch <= !eEpoch;
        execRedirect.enq(eInst.addr);
        $display("Jump to  %d ", eInst.addr);
      end

			e2m.enq(Valid(eInst));
		end
		else e2m.enq(Invalid);

		$display("Execute : inst form Pc %d, iEp %b, eEp %b", temp.pc, temp.epoch, eEpoch);
	endrule

	rule doMemory(csrf.started);
		e2m.deq;

		if(isValid(e2m.first)) begin

		let eInst = validValue(e2m.first);
    let iType = eInst.iType;
    case(iType)
      Ld :
      begin
        let d ← dMem.req(MemReq{op: Ld, addr: eInst.addr, data: ?});
        eInst.data = d;
      end
      St:
      begin
        let d ← dMem.req(MemReq{op: St, addr: eInst.addr, data: eInst.data});
      end
      Unsupported :
      begin
        $fwrite(stderr, "ERROR: Executing unsupported instruction\n");
        $finish;
      end
    endcase

		m2w.enq(Valid(eInst));
		end
		else m2w.enq(Invalid);
	endrule

	rule doWriteback(csrf.started);
		m2w.deq;

		if(isValid(m2w.first)) begin

		let eInst = validValue(m2w.first);
    //WriteBack
    if (isValid(eInst.dst)) begin
      rf.wr(fromMaybe(?, eInst.dst), eInst.data);
			sb.remove;
    end
    csrf.wr(eInst.iType ≡ Csrw ? eInst.csr : Invalid, eInst.data);

		end
	endrule

  method ActionValue#(CpuToHostData) cpuToHost;
    let retV <- csrf.cpuToHost;
    return retV;
  endmethod

  method Action hostToCpu(Bit#(32) startpc) if (!csrf.started);
    csrf.start(0);
    eEpoch <= False;
    fEpoch <= False;
    pc <= startpc;
  endmethod

  interface iMemInit = iMem.init;
  interface dMemInit = dMem.init;

endmodule
