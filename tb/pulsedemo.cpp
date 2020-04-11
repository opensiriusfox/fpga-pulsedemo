#include <verilated.h>		// Defines verilator's common routines
#include "Vpulsedemo_top.h"		// note the _top used in makefile target

#include "verilated_vcd_c.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>

Vpulsedemo_top	*uut;				// the module instance as a UUT
vluint64_t main_time = 0;			// current simulation time

double sc_time_stamp() {
	return main_time;				// i.e. typecast main+time
}

int main(int argc, char** argv) {
	// Argument to enable the trace generation
	bool vcdTrace = false;
	VerilatedVcdC* tfp = NULL;

	Verilated::commandArgs(argc, argv); // Steal the arguments	

	uut = new Vpulsedemo_top;		// setup a uuit
	uut->eval();					// make it startup.
	uut->eval();					// not sure why we do this twice?

	if (vcdTrace) {					// when we're tracing let's setup.
		Verilated::traceEverOn(true);

		tfp = new VerilatedVcdC;	// give us a trace
		uut->trace(tfp, 99);		// attach the trace with a depth? of 99?

		// and open up the output file for writing
		std::string vcdname = argv[0]; 
		vcdname += ".vcd";
		std::cout << vcdname << std::endl;
		tfp->open(vcdname.c_str());
	}

	uut->CLOCK = 0;					// start the clock low
	uut->eval();

	while (!Verilated::gotFinish()) {
		// and toggle the clock until we call $finish.
		uut->CLOCK = uut->CLOCK ? 0 : 1;
		uut->eval();

		if (tfp != NULL) {
			tfp->dump(main_time);
		}

		main_time++;
	}

	// close out the simulation
	uut->final();

	// close the trace file.
	if (tfp != NULL) {
		tfp->close();
		delete tfp;
	}

	// and clean everything up.
	delete uut;

	return 0;
}