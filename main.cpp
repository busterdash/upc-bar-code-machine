#include <iostream>
#include "upc_bar_code.hpp"
using namespace std;

int main(int argument_count, char* argument_value[])
{
	cout << upc_bar_code::get_int_digit(-42503,4) << "\r\n";
	return 0;
}
