package HiHiHoHo;
	String hi = "Hi";
	String ho = "Ho";
	String bye = "Bye!";

	(* synthesize *)
	module mkHiHiHoHo(Empty);
		Reg#(Bit#(3)) counter <- mkReg(0);

		/* The counter increases at every clock cycle. */
		rule inc_counter;
			counter <= counter + 1;
		endrule

		/* TODO: rule say_hi: print "Hi" once */
		rule say_hi(counter<2);
			$display("Hi");
		endrule

		/* TODO: rule say_ho: print "Ho" once */
		rule say_ho((counter<4)&&(counter>1));
			$display("Ho");
		endrule

		/* TODO: rule finish: print "Bye" and quit */
		rule say_bye(counter==4);
			$display("Bye!");
			$finish;
		endrule

	endmodule
endpackage