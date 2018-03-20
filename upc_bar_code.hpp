////////////////////////////////////////////////////////////////
// UPC-A Bar Code Class
//
// 9/29/17 - B.D.S.
//
// Purpose: Reads and writes UPC-A bar codes.
////////////////////////////////////////////////////////////////

#ifndef _UPC_BAR_CODE_HPP
#define _UPC_BAR_CODE_HPP

#include <string>
#include "basic-bitmap-fileio/raster_image.hpp"

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

