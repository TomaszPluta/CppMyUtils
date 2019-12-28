#include "doubleBuff.h"
#include <iostream>




int main(int argc, char **argv)
{
	dBuff<int> db(100);
	db.write(4);
//	std::cout<<db.read();
}


