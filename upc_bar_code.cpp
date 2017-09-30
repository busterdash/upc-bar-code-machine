#include "upc_bar_code.hpp"

upc_bar_code::upc_bar_code()
{
	module_set[0] = 13;
	module_set[1] = 25;
	module_set[2] = 19;
	module_set[3] = 61;
	module_set[4] = 35;
	module_set[5] = 49;
	module_set[6] = 47;
	module_set[7] = 59;
	module_set[8] = 55;
	module_set[9] = 11;
	
	bar_code[0] = 0x50000000;
	bar_code[0] = 0x14000;
	bar_code[0] = 0x5;
}

upc_bar_code::~upc_bar_code()
{
	
}

upc_bar_code::write()
{
	
}
