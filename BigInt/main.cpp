#include <iostream>
#include <cassert>
#include "bigint.h"

int main()
{
	unlimitedintegers::BigInt a(346);
	unlimitedintegers::BigInt b(419);
	unlimitedintegers::BigInt c;	

	c = a + b;

	unlimitedintegers::BigInt d(734);
	unlimitedintegers::BigInt e;

	e = c - d;

	unlimitedintegers::BigInt f(12);
	unlimitedintegers::BigInt g;

	g = e * f;

	unlimitedintegers::BigInt h(-67);
	unlimitedintegers::BigInt i;

	i = g / h;

	c.Print();	// 765
	e.Print();	// 31
	g.Print();	// 372
	i.Print();	// -5

	return 0;
}