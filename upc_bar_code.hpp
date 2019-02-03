/*==============================================================================================
	
	upc_bar_code_machine.cpp
	Copyright 2018 Buster Schrader
	
	This file is part of The UPC Bar Code Machine.
	
	The UPC Bar Code Machine is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	any later version.
	
	The UPC Bar Code Machine is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
	
	You should have received a copy of the GNU General Public License
	along with The UPC Bar Code Machine.  If not, see <https://www.gnu.org/licenses/>.
	
==============================================================================================
	
	UPC-A Bar Code Class
	9/29/17 - B.D.S.
	Purpose: Reads and writes UPC-A bar codes.

==============================================================================================*/

#ifndef _UPC_BAR_CODE_HPP
#define _UPC_BAR_CODE_HPP

#include <string>
#include "bitmap-machine/raster_image.hpp"

class upc_bar_code
{
	private:
		long bar_code[3];
		short product_digit;
		long manufacturer_code;
		long product_code;
		short check_digit;
		short module_set[10];
		short get_int_digit(int input, short index);
		void render_num_char(raster_image* ri, short value, int x_offset, int y_offset);
	public:
		upc_bar_code(short pd, long mfc, long pc, short cd);
		~upc_bar_code();
		void write(std::string filename);
};

#endif

