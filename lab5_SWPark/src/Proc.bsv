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
} Decode2Register deriving(Bits, Eq);

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

	Fifo#(2, Fetch2Decode)		f2d <- mkPipelineFifo;
	Fifo#(2, Decode2Register)	d2r <- mkPipelineFifo;

	Bool memReady = iMem.init.done() && dMem.init.done();
	rule test (!memReady);
		let e = tagged InitDone;
		iMem.init.request.put(e);
		dMem.init.request.put(e);
	endrule


	rule doFetch(csrf.started && stat == AOK);
		Addr tempPc;
		Bool tempFEpoch;

		if(execRedirect.notEmpty) begin
			execRedirect.deq;
			tempPc = execRedirect.first;
			tempFEpoch = !fEpoch;
		end
		else begin
			tempPc = pc;
			tempFEpoch = fEpoch;
		end

		let inst = iMem.req(tempPc);
		let ppc = tempPc + 4;

		f2d.enq(Fetch2Decode{inst:inst, pc:tempPc, ppc:ppc, epoch:tempFEpoch});
		pc <= ppc;
		fEpoch <= tempFEpoch;

		$display("Fetch : from Pc %d , \n", tempPc);
	endrule

	rule doDecode(csrf.started && stat == AOK);
		let inst	= f2d.first.inst;
		let pc		= f2d.first.pc;
		let ppc		= f2d.first.ppc;
		let iEpoch	= f2d.first.epoch;
		f2d.deq;

		if(iEpoch == eEpoch) begin
			// Decode
			let dInst = decode(inst);
			d2r.enq(Decode2Register{dInst:dInst, pc:pc, ppc:ppc, epoch:iEpoch});
		end
		$display("decode %d \n", pc);
	endrule

	rule dpRest(csrf.started && stat == AOK);
		let dInst	= d2r.first.dInst;
		let pc		= d2r.first.pc;
		let ppc		= d2r.first.ppc;
		let iEpoch	= d2r.first.epoch;
		d2r.deq;
		
		$display("rest: %d, \n", pc);
		if(iEpoch == eEpoch) begin
			// Register Read 
			let rVal1 = isValid(dInst.src1) ? rf.rd1(validValue(dInst.src1)) : ?;
			let rVal2 = isValid(dInst.src2) ? rf.rd2(validValue(dInst.src2)) : ?;
			let csrVal = isValid(dInst.csr) ? csrf.rd(validValue(dInst.csr)) : ?;

			// Execute         
			let eInst = exec(dInst, rVal1, rVal2, pc, ppc, csrVal);
			let iType = eInst.iType;
				
			if(eInst.mispredict) begin
				eEpoch <= !eEpoch;
				execRedirect.enq(eInst.addr);
				$display("jump! :mispredicted, address %d ", eInst.addr);
				csrf.incBPMissCnt();
			end

			//Memory 
			case(iType)
				Ld:
				begin
					let d <- dMem.req(MemReq{op: Ld, addr: eInst.addr, data: ?});
					eInst.data = d;
				end

				St:
				begin
					let d <- dMem.req(MemReq{op: St, addr: eInst.addr, data: eInst.data});
				end

				Unsupported:
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
			
			/*
			case(iType)
				J, Jr, Br:	csrf.incInstTypeCnt(Ctr);
				Ld, St:		csrf.incInstTypeCnt(Mem);
			endcase
			*/

			case(iType)
				J:	begin
					csrf.incInstTypeCnt(JCnt);
					if(eInst.mispredict) csrf.incMissInstTypeCnt(JMiss);
				end
				Jr:	begin
					csrf.incInstTypeCnt(JrCnt);
					if(eInst.mispredict) csrf.incMissInstTypeCnt(JrMiss);
				end
				Br:	begin
					csrf.incInstTypeCnt(BrCnt);
					if(eInst.mispredict) csrf.incMissInstTypeCnt(BrMiss);
				end
				Ld, St: begin
					csrf.incInstTypeCnt(Mem);
				end
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

	method Action hostToCpu(Bit#(32) startpc) if (!csrf.started && memReady);
		csrf.start(0);
		eEpoch <= False;
		fEpoch <= False;
		pc <= startpc;
		stat <= AOK;
	endmethod

	interface iMemInit = iMem.init;
	interface dMemInit = dMem.init;

endmodule
