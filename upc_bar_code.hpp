////////////////////////////////////////////////////////////////
// UPC-A Bar Code Class
//
// 9/29/17 - B.D.S.
//
// Purpose: Reads and writes UPC-A bar codes.
////////////////////////////////////////////////////////////////

#ifndef _UPC_BAR_CODE_HPP
#define _UPC_BAR_CODE_HPP

//#include "windows_bitmap.hpp"

class upc_bar_code
{
	private:
		short product_digit;
		long manufacturer_code;
		long product_code;
		short check_digit;
		short module_set[10];
		long bar_code[3];
	public:
		upc_bar_code(long mfc, long pc, short pd, short cd);
		~upc_bar_code();
		static short get_int_digit(int input, short index);
		write();
};

#endif

