import Multiplexer::*;

interface BarrelShifterRight;
  method ActionValue#(Bit#(64)) rightShift(Bit#(64) val, Bit#(6) shiftAmt, Bit#(1) shiftValue);
endinterface

module mkBarrelShifterRight(BarrelShifterRight);
  method ActionValue#(Bit#(64)) rightShift(Bit#(64) val, Bit#(6) shiftAmt, Bit#(1) shiftValue);
    Bit#(64) result = val;
    Bit#(64) result_temp = result;
    for(Integer j=1, Integer k=0; j<64; j=j*2, k=k+1)
    begin
      result_temp = (result_temp >> j);

      if(shiftValue == 1)
        for(Integer i=1; i<=j; i=i+1)
        begin
          result_temp[64-i] = shiftValue;
        end

      result = multiplexer64(shiftAmt[k], result, result_temp);
      result_temp = result;
    end
    return result;
  endmethod
endmodule

interface BarrelShifterRightLogical;
  method ActionValue#(Bit#(64)) rightShift(Bit#(64) val, Bit#(6) shiftAmt);
endinterface

module mkBarrelShifterRightLogical(BarrelShifterRightLogical);
  let bsr <- mkBarrelShifterRight;

  method ActionValue#(Bit#(64)) rightShift(Bit#(64) val, Bit#(6) shiftAmt);
    Bit#(64) result;
    result <- bsr.rightShift(val, shiftAmt, 0);
    return result;
  endmethod
endmodule

typedef BarrelShifterRightLogical BarrelShifterRightArithmetic;

module mkBarrelShifterRightArithmetic(BarrelShifterRightArithmetic);
  let bsr <- mkBarrelShifterRight;

  method ActionValue#(Bit#(64)) rightShift(Bit#(64) val, Bit#(6) shiftAmt);
    Bit#(64) result;
    Bit#(1) sign = val[63];
    result <- bsr.rightShift(val, shiftAmt, sign);
    return result;
  endmethod
endmodule
