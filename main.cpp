#include <iostream>
#include "upc_bar_code.hpp"
using namespace std;

int main(int argument_count, char* argument_value[])
{
	upc_bar_code* upcbc = new upc_bar_code(8,52109,403,4);
	upcbc->write("barcode.bmp");
	delete upcbc;
	return 0;
}
