#include <iostream>
#include <cassert>
#include "bigint.h"

void t_Equality()
{
	unlimitedintegers::BigInt a(1);
	unlimitedintegers::BigInt b(1);
	assert(a == b);
}

int main()
{
	t_Equality();

	unlimitedintegers::BigInt a(100);
	unlimitedintegers::BigInt b(20);	
	unlimitedintegers::BigInt c;	

	c = a - b;

	a.Print();
	b.Print();
	c.Print();

	return 0;
}