function Bit#(1) and1(Bit#(1) a, Bit#(1) b);
  return a & b;
endfunction

function Bit#(1) or1(Bit#(1) a, Bit#(1) b);
  return a | b;
endfunction

function Bit#(1) not1(Bit#(1) a);
  return ~ a;
endfunction

function Bit#(1) multiplexer1(Bit#(1) sel, Bit#(1) a, Bit#(1) b);
  return or1(and1(a, not1(sel)), and1(b, sel));
endfunction

function Bit#(64) multiplexer64(Bit#(1) sel, Bit#(64) a, Bit#(64) b);
///*
  Bit#(64) result;
  for(Integer i=0; i<64; i = i+1)
    result[i] = multiplexer1(sel, a[i], b[i]);
  return result;
//*/
//  return multiplexer_n(sel, a, b);
endfunction

typedef 64 N;
function Bit#(N) multiplexerN(Bit#(1) sel, Bit#(N) a, Bit#(N) b);
  return (sel == 0)? a : b;
endfunction

//typedef 64 N; // Not needed
function Bit#(N) multiplexer_n(Bit#(1) sel, Bit#(N) a, Bit#(N) b);
  Bit#(N) result;
  for(Integer i=0; i<valueOf(N); i=i+1)
    result[i] = multiplexer1(sel, a[i], b[i]);
  return result;
endfunction
