#include "doubleBuff.h"
#include <iostream>





int main(int argc, char **argv)
{
	dBuff<std::string> dbuff(10);
	TestDoubleBuffReadWrite(dbuff);

}


