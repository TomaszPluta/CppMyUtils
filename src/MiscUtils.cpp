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
	std::cout<<db[0]<<"\n"<<std::endl; /* print read buff value, just after swap*/

	db.write(10);
	db.write(20);
	db.write(30);
	db.write(40);
	db.write(50);
	std::cout<<db[0]<<"\n"<<std::endl;

	db.write(100);
	db.write(200);
	db.write(300);
	db.write(400);
	db.write(500);
  	std::cout<<db[0]<<"\n"<<std::endl;

}


