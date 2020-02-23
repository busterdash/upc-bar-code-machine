/*==============================================================================================
	
	main.cpp
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

#include <iostream>
#include <string>
#include <cstdlib>
#include "upc_bar_code.hpp"

int main(int argument_count, char* argument_value[])
{
	short product_type = 0;
	long manufacturer_code = 0;
	long product_code = 0;
	short check_digit = 0;
	std::string filename = "";
	
	if (argument_count == 6)
	{
		product_type = std::atoi(argument_value[2]);
		manufacturer_code = std::atoi(argument_value[3]);
		product_code = std::atoi(argument_value[4]);
		check_digit = std::atoi(argument_value[5]);
		filename = std::string(argument_value[1]);
	}
	else
	{
		std::cout << "Arguments: <png filename> <product_type> <manufacturer_code> <product_code> <check_digit>\r\n";
		return 0;
	}
	
	upc_bar_code* upcbc = new upc_bar_code(product_type, manufacturer_code, product_code, check_digit);
	unsigned int error = upcbc->write(filename);
    
    if (error)
        std::cout << "Could not write " << filename << '!';
	
	delete upcbc;
	return 0;
}
