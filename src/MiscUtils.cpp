#include "doubleBuff.h"
#include <iostream>




int main(int argc, char **argv)
{
	dBuff<int> db(5);
	db.write(1);
	db.write(2);
	db.write(3);
	db.write(4);
	db.write(5);
	db.write(6);
	db.write(7);
	db.write(8);

}


