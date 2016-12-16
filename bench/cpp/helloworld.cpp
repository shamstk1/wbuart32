////////////////////////////////////////////////////////////////////////////////
//
// Filename: 	helloworld.cpp
//
// Project:	wbuart32, a full featured UART with simulator
//
// Purpose:	To demonstrate a useful Verilog file which could be used as a
//		toplevel program later, to demo the transmit UART.
//
// Creator:	Dan Gisselquist, Ph.D.
//		Gisselquist Technology, LLC
//
////////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015-2016, Gisselquist Technology, LLC
//
// This program is free software (firmware): you can redistribute it and/or
// modify it under the terms of  the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTIBILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
// for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program.  (It's in the $(ROOT)/doc directory, run make with no
// target there if the PDF file isn't present.)  If not, see
// <http://www.gnu.org/licenses/> for a copy.
//
// License:	GPL, v3, as defined and found on www.gnu.org,
//		http://www.gnu.org/licenses/gpl.html
//
//
////////////////////////////////////////////////////////////////////////////////
//
//
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <signal.h>
#include "verilated.h"
#include "Vhelloworld.h"
#include "uartsim.h"

int	main(int argc, char **argv) {
	Verilated::commandArgs(argc, argv);
	Vhelloworld	tb;
	UARTSIM		*uart;
	int		port = 0;
	unsigned	setup = 25, testcount = 0;

	tb.i_setup = setup;
	uart = new UARTSIM(port);
	uart->setup(tb.i_setup);

	while(testcount++ < 0x8000000) {

		tb.i_clk = 1;
		tb.eval();
		tb.i_clk = 0;
		tb.eval();

		(*uart)(tb.o_uart);
	}
}
