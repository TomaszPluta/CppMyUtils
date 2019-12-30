#include "doubleBuff.h"
#include <iostream>





int main(int argc, char **argv)
{
	dBuff<int> dbuff(10);
	TestDoubleBuffReadWrite(dbuff);

}


