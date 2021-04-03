import Vector::*;

import FftCommon::*;
import Fifo::*;

interface Fft;
  method Action enq(Vector#(FftPoints, ComplexData) in);
  method ActionValue#(Vector#(FftPoints, ComplexData)) deq;
endinterface

(* synthesize *)
module mkFftCombinational(Fft);
  Fifo#(2, Vector#(FftPoints, ComplexData)) inFifo <- mkCFFifo;
  Fifo#(2, Vector#(FftPoints, ComplexData)) outFifo <- mkCFFifo;
  Vector#(NumStages, Vector#(BflysPerStage, Bfly4)) bfly <- replicateM(replicateM(mkBfly4));

  function Vector#(FftPoints, ComplexData) stage_f(StageIdx stage, Vector#(FftPoints, ComplexData) stage_in);
    Vector#(FftPoints, ComplexData) stage_temp, stage_out;
    for (FftIdx i = 0; i < fromInteger(valueOf(BflysPerStage)); i = i + 1)
    begin
      FftIdx idx = i * 4;
      Vector#(4, ComplexData) x;
      Vector#(4, ComplexData) twid;
      for (FftIdx j = 0; j < 4; j = j + 1 )
      begin
        x[j] = stage_in[idx+j];
        twid[j] = getTwiddle(stage, idx+j);
      end
      let y = bfly[stage][i].bfly4(twid, x);

      for(FftIdx j = 0; j < 4; j = j + 1 )
        stage_temp[idx+j] = y[j];
    end

    stage_out = permute(stage_temp);

    return stage_out;
  endfunction

  rule doFft;
    inFifo.deq;
    Vector#(4, Vector#(FftPoints, ComplexData)) stage_data;
    stage_data[0] = inFifo.first;

    for (StageIdx stage = 0; stage < 3; stage = stage + 1)
      stage_data[stage+1] = stage_f(stage, stage_data[stage]);
    outFifo.enq(stage_data[3]);
  endrule

  method Action enq(Vector#(FftPoints, ComplexData) in);
    inFifo.enq(in);
  endmethod

  method ActionValue#(Vector#(FftPoints, ComplexData)) deq;
    outFifo.deq;
    return outFifo.first;
  endmethod
endmodule

(* synthesize *)
module mkFftFolded(Fft);
  Fifo#(2, Vector#(FftPoints, ComplexData)) inFifo <- mkCFFifo;
  Fifo#(2, Vector#(FftPoints, ComplexData)) outFifo <- mkCFFifo;
  Reg#(Vector#(FftPoints, ComplexData)) sReg <- mkRegU();
  Reg#(StageIdx) iReg <- mkReg(0);
  Vector#(BflysPerStage, Bfly4) bfly <- replicateM(mkBfly4);

  function Vector#(FftPoints, ComplexData) stage_f(StageIdx stage, Vector#(FftPoints, ComplexData) stage_in);
    Vector#(FftPoints, ComplexData) stage_temp, stage_out;
    for (FftIdx i = 0; i < fromInteger(valueOf(BflysPerStage)); i = i + 1)
    begin
      FftIdx idx = i * 4;
      Vector#(4, ComplexData) x;
      Vector#(4, ComplexData) twid;
      for (FftIdx j = 0; j < 4; j = j + 1 )
      begin
        x[j] = stage_in[idx+j];
        twid[j] = getTwiddle(stage, idx+j);
      end
      let y = bfly[i].bfly4(twid, x);

      for(FftIdx j = 0; j < 4; j = j + 1 )
        stage_temp[idx+j] = y[j];
    end

    stage_out = permute(stage_temp);

    return stage_out;
  endfunction

  rule doFft;
    Vector#(FftPoints, ComplexData) stage_data;
    if(iReg==0)
    begin stage_data = inFifo.first(); inFifo.deq(); end
    else stage_data = sReg;

    let stage_result = stage_f(iReg, stage_data);

    if(iReg == 2) outFifo.enq(stage_result);
    else sReg <= stage_result;
    iReg <= (iReg == 2) ? 0 : iReg+1;
  endrule

  method Action enq(Vector#(FftPoints, ComplexData) in);
    inFifo.enq(in);
  endmethod

  method ActionValue#(Vector#(FftPoints, ComplexData)) deq;
    outFifo.deq;
    return outFifo.first;
  endmethod
endmodule

(* synthesize *)
module mkFftPipelined(Fft);
  Vector#(NumStages, Vector#(BflysPerStage, Bfly4)) bfly <- replicateM(replicateM(mkBfly4));
  Fifo#(2, Vector#(FftPoints, ComplexData)) inFifo <- mkCFFifo;
  Fifo#(2, Vector#(FftPoints, ComplexData)) outFifo <- mkCFFifo;
  Reg#(Maybe#(Vector#(FftPoints, ComplexData))) s1Reg <- mkReg(tagged Invalid);
  Reg#(Maybe#(Vector#(FftPoints, ComplexData))) s2Reg <- mkReg(tagged Invalid);

  function Vector#(FftPoints, ComplexData) stage_f(StageIdx stage, Vector#(FftPoints, ComplexData) stage_in);
    Vector#(FftPoints, ComplexData) stage_temp, stage_out;
    for (FftIdx i = 0; i < fromInteger(valueOf(BflysPerStage)); i = i + 1)
    begin
      FftIdx idx = i * 4;
      Vector#(4, ComplexData) x;
      Vector#(4, ComplexData) twid;
      for (FftIdx j = 0; j < 4; j = j + 1 )
      begin
        x[j] = stage_in[idx+j];
        twid[j] = getTwiddle(stage, idx+j);
      end
      let y = bfly[stage][i].bfly4(twid, x);

      for(FftIdx j = 0; j < 4; j = j + 1 )
        stage_temp[idx+j] = y[j];
    end

    stage_out = permute(stage_temp);

    return stage_out;
  endfunction

  rule doFft;
    if(inFifo.notEmpty())begin s1Reg <= tagged Valid stage_f(0, inFifo.first()); inFifo.deq(); end
    else s1Reg <= tagged Invalid;

    case(s1Reg) matches
      tagged Valid .in: s2Reg <= tagged Valid stage_f(1, in);
      tagged Invalid: s2Reg <= tagged Invalid;
    endcase

    case(s2Reg) matches
      tagged Valid .in: outFifo.enq(stage_f(2, in));
    endcase
  endrule

  method Action enq(Vector#(FftPoints, ComplexData) in);
    inFifo.enq(in);
  endmethod

  method ActionValue#(Vector#(FftPoints, ComplexData)) deq;
    outFifo.deq;
    return outFifo.first;
  endmethod
endmodule

interface SuperFoldedFft#(numeric type radix);
  method ActionValue#(Vector#(FftPoints, ComplexData)) deq;
  method Action enq(Vector#(FftPoints, ComplexData) in);
endinterface

module mkFftSuperFolded(SuperFoldedFft#(radix)) provisos(Div#(TDiv#(FftPoints, 4), radix, times), Mul#(radix, times, TDiv#(FftPoints, 4)));
  Fifo#(2, Vector#(FftPoints, ComplexData)) inFifo <- mkCFFifo;
  Fifo#(2, Vector#(FftPoints, ComplexData)) outFifo <- mkCFFifo;

  Reg#(StageIdx) stageReg <- mkReg(0);
  Reg#(Bit#(6)) timesReg <- mkReg(0);
  Reg#(Vector#(FftPoints, ComplexData)) sReg <- mkRegU();

  Vector#(radix, Bfly4) bfly <- replicateM(mkBfly4);
  Integer radix_i = valueOf(radix);

  function Vector#(FftPoints, ComplexData) stage_f(StageIdx stage, Bit#(6) ttimes, Vector#(FftPoints, ComplexData) stage_in);
    Vector#(FftPoints, ComplexData) stage_temp, stage_out;
    stage_temp = stage_in;

    for (FftIdx i = 0; i < fromInteger(radix_i); i = i + 1)
    begin
      FftIdx idx = (i + fromInteger(radix_i) * ttimes) * 4;
      Vector#(4, ComplexData) x;
      Vector#(4, ComplexData) twid;
      for (FftIdx j = 0; j < 4; j = j + 1 )
      begin
        x[j] = stage_in[idx+j];
        twid[j] = getTwiddle(stage, idx+j);
      end

      let y = bfly[i].bfly4(twid, x);

      for(FftIdx j = 0; j < 4; j = j + 1 )
        stage_temp[idx+j] = y[j];
    end
    stage_out = stage_temp;

    if(ttimes == 16/fromInteger(radix_i)-1)
      stage_out = permute(stage_temp);

    return stage_out;
  endfunction

  rule doFft;
  Vector#(FftPoints, ComplexData) stage_data;
  if(stageReg == 0 && timesReg == 0) begin
    stage_data = inFifo.first();
    inFifo.deq();
  end
  else stage_data = sReg;

  let stage_result = stage_f(stageReg, timesReg, stage_data);

  if(stageReg == 2 && timesReg == 16/fromInteger(radix_i)-1) outFifo.enq(stage_result);
  else sReg <= stage_result;

  if(timesReg == 16/fromInteger(radix_i)-1) begin
    if(stageReg == 2) stageReg <= 0;
    else stageReg <= stageReg + 1;

    timesReg <= 0;
  end
  else timesReg <= timesReg + 1;
  endrule

  method Action enq(Vector#(FftPoints, ComplexData) in);
    inFifo.enq(in);
  endmethod

  method ActionValue#(Vector#(FftPoints, ComplexData)) deq;
    outFifo.deq;
    return outFifo.first;
  endmethod
endmodule

function Fft getFft(SuperFoldedFft#(radix) f);
  return (interface Fft;
    method enq = f.enq;
    method deq = f.deq;
  endinterface);
endfunction
