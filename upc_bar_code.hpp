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
		short module_set[10];
		long bar_code[3];
	public:
		upc_bar_code();
		~upc_bar_code();
		write();
};

#endif

