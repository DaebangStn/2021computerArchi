import BarrelShifterRight::*;

interface BarrelShifterLeft;
	method ActionValue#(Bit#(64)) leftShift(Bit#(64) val, Bit#(6) shiftAmt);
endinterface

module mkBarrelShifterLeft(BarrelShifterLeft);
	let bsr <- mkBarrelShifterRightLogical;
	method ActionValue#(Bit#(64)) leftShift(Bit#(64) val, Bit#(6) shiftAmt);
		let temp <- bsr.rightShift(reverseBits(val), shiftAmt);
		temp = reverseBits(temp);
		return temp;
	endmethod
endmodule
