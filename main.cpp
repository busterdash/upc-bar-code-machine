#include <iostream>
#include <string>
#include "upc_bar_code.hpp"
using namespace std;

int main(int argument_count, char* argument_value[])
{
	short product_type = 0;
	long manufacturer_code = 0;
	long product_code = 0;
	short check_digit = 0;
	string filename = "";
	
	if (argument_count == 6)
	{
		product_type = atoi(argument_value[2]);
		manufacturer_code = atoi(argument_value[3]);
		product_code = atoi(argument_value[4]);
		check_digit = atoi(argument_value[5]);
		filename = string(argument_value[1]);
	}
	else
	{
		cout << "Arguments: <bitmap name> <product_type> <manufacturer_code> <product_code> <check_digit>\r\n";
		return 0;
	}
	
	upc_bar_code* upcbc = new upc_bar_code(product_type, manufacturer_code, product_code, check_digit);
	upcbc->write(filename);
	
	delete upcbc;
	return 0;
}
