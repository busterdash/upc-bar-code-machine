#include <iostream>
#include "upc_bar_code.hpp"
using namespace std;

int main(int argument_count, char* argument_value[])
{
	upc_bar_code* upcbc = new upc_bar_code(0,76737,12232,2);
	upcbc->write();
	
	//cout << upcbc->bar_code[2] << "\r\n";
	//cout << upcbc->bar_code[1] << "\r\n";
	//cout << upcbc->bar_code[0] << "\r\n";
	
	delete upcbc;
	return 0;
}
