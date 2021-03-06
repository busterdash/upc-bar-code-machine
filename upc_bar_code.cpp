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
	
==============================================================================================*/

#include "upc_bar_code.hpp"
#include "lodepng/lodepng.h"

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

void upc_bar_code::render_num_char(std::vector<unsigned char> &img, short value, int x_offset, int y_offset)
{
	unsigned char char_cc = 255;
	unsigned int pos = 0;
	short char_set[10];
	char_set[0] = 0x3B6E;
	char_set[1] = 0x2C97;
	char_set[2] = 0x62E7;
	char_set[3] = 0x628F;
	char_set[4] = 0x1BC9;
	char_set[5] = 0x79CE;
	char_set[6] = 0x39AB;
	char_set[7] = 0x7A52;
	char_set[8] = 0x3AAB;
	char_set[9] = 0x7BCA;
	
	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 3; x++)
		{
            pos = 4*img_width*(y+y_offset) + 4*(x+x_offset);
			char_cc = 255-(((char_set[value]>>(14-(y*3+x)))&1)*255);
            img[pos+0] = char_cc;
            img[pos+1] = char_cc;
            img[pos+2] = char_cc;
            img[pos+3] = 255;
		}
	}
}

upc_bar_code::upc_bar_code(short pd, long mfc, long pc, short cd)
{
	module_set[0] = 0x0D; //0001101
	module_set[1] = 0x19; //0011001
	module_set[2] = 0x13; //0010011
	module_set[3] = 0x3D; //0111101
	module_set[4] = 0x23; //0100011
	module_set[5] = 0x31; //0110001
	module_set[6] = 0x2F; //0101111
	module_set[7] = 0x3B; //0111011
	module_set[8] = 0x37; //0110111
	module_set[9] = 0x0B; //0001011
	
	bar_code[0] = 0x50000000; //Bar code start pattern.
	bar_code[1] = 0x14000;    //Bar code middle pattern.
	bar_code[2] = 0x5;        //Bar code end pattern.
	
	//Validate inputs.
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

unsigned int upc_bar_code::write(std::string filename)
{
	const int bc_w = 96;    //Bar code width in pixels. 
	const int bc_h = 64;    //Bar code height in pixels.
	const int bc_sec = 32;  //Size of bar_code[] data item.
	const int bc_units = 3; //Number of elements required to contain barcode.
	const int brdr = 16;    //Border size in pixels.
	
    img_width = brdr+bc_w+brdr;
    img_height = brdr+bc_h+brdr;
    std::vector<unsigned char> img;
    img.resize(img_width * img_height * 4);
    
	unsigned char bar_cc = 255;
	
	//This builds the barcode from a character set we defined in the constructor.
	//Right-side bar characters are inverted as stated in the format.
	//Five and six lines down from here, we have a value that sits over an int boundary.
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
	
    int pos = 0;
    
	for (int y = 0; y < bc_h; y++) //Vertical plotting.
	{
		for (int x = 0; x < bc_units; x++) //Run through all elements of bar_code[].
		{
			for (int i = 0; i < bc_sec; i++) //Plot each bit from value in bar_code[i].
			{
				int true_x = x*bc_sec+i; //The x position within the entire bar code.
				int plot_x = (bc_w-1+brdr)-true_x; //We plot from left to right.
				bar_cc = 255-(((bar_code[bc_units-1-x]>>i)&1)*255); //Get color component from binary data.
                pos = 4*img_width*(y+brdr) + 4*plot_x;
                
				if (y < bc_h-6) 
				{
					//Most of the print work is done here.
                    img[pos+0] = bar_cc;
                    img[pos+1] = bar_cc;
                    img[pos+2] = bar_cc;
                    img[pos+3] = 255;
				}
				else 
				{
					//Generates space in bar code for human-readable values.
					if (true_x <= 10 or true_x >= bc_w-11 or (true_x > 44 and true_x < 50))
                    {
						img[pos+0] = bar_cc;
                        img[pos+1] = bar_cc;
                        img[pos+2] = bar_cc;
                        img[pos+3] = 255;
                    }
				}
			}
		}
	}
	
	//Generate human-readable values. 
	for (int u = 0; u < 5; u++)
	{
		render_num_char(img, get_int_digit(manufacturer_code,4-u), 13+brdr+(7*u), brdr+64-5);
		render_num_char(img, get_int_digit(product_code,4-u), 53+brdr+(7*u), brdr+64-5);
	}
	
	render_num_char(img, product_digit, -4+brdr, brdr+64-5);
	render_num_char(img, check_digit, brdr+bc_w+2, brdr+64-5);

	return lodepng::encode(filename.c_str(), img, img_width, img_height);
}
