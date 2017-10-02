#include "upc_bar_code.hpp"

short upc_bar_code::get_int_digit(int input, short index)
{
	int term1x = 1;
	int term10x = 1;
	
	for (short i = 0; i < index; i++)
	{
		term1x *= 10;
	}
	
	term10x = term1x * 10;
	
	return ((input % term10x) - ((input % term10x) % term1x)) / term1x;
}

upc_bar_code::upc_bar_code(long mfc, long pc, short pd, short cd)
{
	module_set[0] = 13; //0001101
	module_set[1] = 25; //0011001
	module_set[2] = 19; //0010011
	module_set[3] = 61; //0111101
	module_set[4] = 35; //0100011
	module_set[5] = 49; //0110001
	module_set[6] = 47; //0101111
	module_set[7] = 59; //0111011
	module_set[8] = 55; //0110111
	module_set[9] = 11; //0001011
	
	bar_code[0] = 0x50000000; //Bar code start pattern.
	bar_code[1] = 0x14000; //Bar code middle pattern.
	bar_code[2] = 0x5; //Bar code end pattern.
	
	if (pd < 0 or pd > 9)
		product_digit = 0;
	else
		product_digit = pd;
	
	if (cd < 0 or cd > 9)
		check_digit = 0;
	else
		check_digit = cd;
	
	if (mfc < 0 or mfc > 99999)
		manufacturer_code = 0;
	else
		manufacturer_code = mfc;
	
	if (pc < 0 or pc > 99999)
		product_code = 0;
	else
		product_code = pc;
}

upc_bar_code::~upc_bar_code()
{
	
}

upc_bar_code::write()
{
	bar_code[2] = bar_code[2] | (module_set[check_digit] << 3); //Append check digit.
	//bar_code[2] = bar_code[2] | (module_set[
}
