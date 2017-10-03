#include "upc_bar_code.hpp"
#include "windows_bitmap.hpp"

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

upc_bar_code::upc_bar_code(short pd, long mfc, long pc, short cd)
{
	module_set[0] = 13; //0001101
	module_set[1] = 25; //0011001
	module_set[2] = 19; //0010011
	module_set[3] = 61; //0111101
	module_set[4] = 35; //0100011
	module_set[5] = 49; //0110001
	module_set[6] = 47; //01l01111
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
	bar_code[2] = bar_code[2]|((~module_set[check_digit]&127)<<3);
	bar_code[2] = bar_code[2]|((~module_set[get_int_digit(product_code,0)]&127)<<10);
	bar_code[2] = bar_code[2]|((~module_set[get_int_digit(product_code,1)]&127)<<17);
	bar_code[2] = bar_code[2]|((~module_set[get_int_digit(product_code,2)]&127)<<24);
	bar_code[2] = bar_code[2]|((~module_set[get_int_digit(product_code,3)]&1)<<31);
	bar_code[1] = bar_code[1]|((~module_set[get_int_digit(product_code,3)]&126)>>1);
	bar_code[1] = bar_code[1]|((~module_set[get_int_digit(product_code,4)]&127)<<6);
	bar_code[1] = bar_code[1]|(module_set[get_int_digit(manufacturer_code,0)]<<18);
	bar_code[1] = bar_code[1]|(module_set[get_int_digit(manufacturer_code,1)]<<25);
	bar_code[0] = bar_code[0]|(module_set[get_int_digit(manufacturer_code,2)]);
	bar_code[0] = bar_code[0]|(module_set[get_int_digit(manufacturer_code,3)]<<7);
	bar_code[0] = bar_code[0]|(module_set[get_int_digit(manufacturer_code,4)]<<14);
	bar_code[0] = bar_code[0]|(module_set[product_digit]<<21);
	
	windows_bitmap* wb = new windows_bitmap("barcode.bmp",96,64);
	raster_image* ri = wb->get_dib()->get_image();
	
	for (int y = 0; y < 64; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			for (int i = 0; i < 32; i++)
			{
				color_component comp = 255-(((bar_code[2-x]>>i)&1)*255);
				color pix = (comp<<16)|(comp<<8)|comp;
				ri->set_pixel(95-(x*32+i), y, pix);
			}
		}
	}
	
	wb->save();
	delete wb;
}
