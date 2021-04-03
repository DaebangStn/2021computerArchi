import Multiplexer::*;
import FIFO::*;
import FIFOF::*;
import Vector::*;
import SpecialFIFOs::*;
/*shiftval TODOTODO*/
/* Interface of the basic right shifter module */
interface BarrelShifterRightPipelined;
	method Action shift_request(Bit#(64) operand, Bit#(6) shamt, Bit#(1) val);
	method ActionValue#(Bit#(64)) shift_response();
endinterface

function Bit#(64) fill1(Bit#(64) num, Integer j);
    for(Integer i=1; i<=j; i=i+1) 
		num[64-i] = 1;
	return num;
endfunction

module mkBarrelShifterRightPipelined(BarrelShifterRightPipelined);
	FIFOF#(Tuple3#(Bit#(64), Bit#(6), Bit#(1))) inFifo <- mkFIFOF;
	let outFifo <- mkFIFOF;
	Maybe#(Tuple3#(Bit#(64), Bit#(6), Bit#(1))) ini = tagged Invalid;
	Reg#(Maybe#(Tuple3#(Bit#(64), Bit#(6), Bit#(1)))) reg0 <- mkReg(ini);
	Reg#(Maybe#(Tuple3#(Bit#(64), Bit#(6), Bit#(1)))) reg1 <- mkReg(ini);
	Reg#(Maybe#(Tuple3#(Bit#(64), Bit#(6), Bit#(1)))) reg2 <- mkReg(ini);
	Reg#(Maybe#(Tuple3#(Bit#(64), Bit#(6), Bit#(1)))) reg3 <- mkReg(ini);
	Reg#(Maybe#(Tuple3#(Bit#(64), Bit#(6), Bit#(1)))) reg4 <- mkReg(ini);

	rule shift (True);
		if(inFifo.notEmpty())
			begin 
				let temp = inFifo.first();
				let result = tpl_1(temp);
				let result_temp = result >> 1;
			    if(tpl_3(temp) == 1)
					result_temp = fill1(result_temp, 1);
				result = multiplexer64(tpl_2(temp)[0], result, result_temp);
				reg0 <= tagged Valid tuple3(result, tpl_2(temp), tpl_3(temp));
				inFifo.deq();
			end
		else reg0 <= Invalid;
		case (reg0) matches
			tagged Valid .s: begin							
				let result = tpl_1(s);
				let result_temp = result >> 2;
			    if(tpl_3(s) == 1)
					result_temp = fill1(result_temp, 2);
				result = multiplexer64(tpl_2(s)[1], result, result_temp);
				reg1 <= tagged Valid tuple3(result, tpl_2(s), tpl_3(s));
			end
			tagged Invalid: reg1 <= Invalid;
		endcase
		case (reg1) matches
			tagged Valid .s: begin
				let result = tpl_1(s);
				let result_temp = result >> 4;
			    if(tpl_3(s) == 1)
					result_temp = fill1(result_temp, 4);
				result = multiplexer64(tpl_2(s)[2], result, result_temp);
				reg2 <= tagged Valid tuple3(result, tpl_2(s), tpl_3(s));
			end
			tagged Invalid: reg2 <= Invalid;
		endcase
		case (reg2) matches
			tagged Valid .s: begin
				let result = tpl_1(s);
				let result_temp = result >> 8;
			    if(tpl_3(s) == 1)
					result_temp = fill1(result_temp, 8);
				result = multiplexer64(tpl_2(s)[3], result, result_temp);
				reg3 <= tagged Valid tuple3(result, tpl_2(s), tpl_3(s));
			end
			tagged Invalid: reg3 <= Invalid;
		endcase
		case (reg3) matches
			tagged Valid .s: begin
				let result = tpl_1(s);
				let result_temp = result >> 16;
			    if(tpl_3(s) == 1)
					result_temp = fill1(result_temp, 16);
				result = multiplexer64(tpl_2(s)[4], result, result_temp);
				reg4 <= tagged Valid tuple3(result, tpl_2(s), tpl_3(s));
			end
			tagged Invalid: reg4 <= Invalid;
		endcase
		case (reg4) matches
			tagged Valid .s: begin
				let result = tpl_1(s);
				let result_temp = result >> 32;
			    if(tpl_3(s) == 1)
					result_temp = fill1(result_temp, 32);
				result = multiplexer64(tpl_2(s)[5], result, result_temp);
				outFifo.enq(result);				
			end
		endcase
	endrule

	method Action shift_request(Bit#(64) operand, Bit#(6) shamt, Bit#(1) val);
		inFifo.enq(tuple3(operand, shamt, val));
	endmethod

	method ActionValue#(Bit#(64)) shift_response();
		outFifo.deq;
		return outFifo.first;
	endmethod
endmodule


/* Interface of the three shifter modules
 *
 * They have the same interface.
 * So, we just copy it using typedef declarations.
 */
interface BarrelShifterRightLogicalPipelined;
	method Action shift_request(Bit#(64) operand, Bit#(6) shamt);
	method ActionValue#(Bit#(64)) shift_response();
endinterface

typedef BarrelShifterRightLogicalPipelined BarrelShifterRightArithmeticPipelined;
typedef BarrelShifterRightLogicalPipelined BarrelShifterLeftPipelined;

module mkBarrelShifterLeftPipelined(BarrelShifterLeftPipelined);
	let bsrp <- mkBarrelShifterRightPipelined;

	method Action shift_request(Bit#(64) operand, Bit#(6) shamt);
		bsrp.shift_request(reverseBits(operand), shamt, 0);
	endmethod

	method ActionValue#(Bit#(64)) shift_response();
		let result <- bsrp.shift_response();
		return reverseBits(result);
	endmethod
endmodule

module mkBarrelShifterRightLogicalPipelined(BarrelShifterRightLogicalPipelined);
	let bsrp <- mkBarrelShifterRightPipelined;

	method Action shift_request(Bit#(64) operand, Bit#(6) shamt);
		bsrp.shift_request(operand, shamt, 0);
	endmethod

	method ActionValue#(Bit#(64)) shift_response();
		let result <- bsrp.shift_response();
		return result;
	endmethod
endmodule

module mkBarrelShifterRightArithmeticPipelined(BarrelShifterRightArithmeticPipelined);
	let bsrp <- mkBarrelShifterRightPipelined;

	method Action shift_request(Bit#(64) operand, Bit#(6) shamt);
		let sign = operand[63];
		bsrp.shift_request(operand, shamt, sign);
	endmethod

	method ActionValue#(Bit#(64)) shift_response();
		let result <- bsrp.shift_response();
		return result;
	endmethod
endmodule
