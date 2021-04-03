package HelloWorld;
	String hello = "HelloWorld";

	(* synthesize *)
	module mkHelloWorld(Empty);
		/* TODO: Implement HelloWorld module */
		Reg#(Bit#(3)) counter <- mkReg(0);

		rule say_hello(counter < 5);
			$display(hello);
			counter <= counter+1;
		endrule

		rule say_bye(counter == 5);
			$display("Bye!");
			$finish;
		endrule

	endmodule
endpackage
