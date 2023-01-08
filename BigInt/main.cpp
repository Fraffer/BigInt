#include "bigint.h"

int main()
{
	unlimitedintegers::BigInt a(100);
	unlimitedintegers::BigInt b(20);	
	unlimitedintegers::BigInt c;	

	c = a + b;

	a.Print();
	b.Print();
	c.Print();

	return 0;
}