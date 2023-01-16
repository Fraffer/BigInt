#include <iostream>
#include <cassert>
#include "bigint.h"

void t_Equality()
{
	unlimitedintegers::BigInt a(1);
	unlimitedintegers::BigInt b(1);
	unlimitedintegers::BigInt c(2);
	assert((a == b) == true);
	assert((b == a) == true);
	assert((a != b) == false);
	assert((b != a) == false);
	assert((a == c) == false);
	assert((a != c) == true);
}

void t_Sum()
{
	unlimitedintegers::BigInt a(119);
	unlimitedintegers::BigInt b(15);
}

void t_Difference()
{
	unlimitedintegers::BigInt a(10000);
	unlimitedintegers::BigInt b(9);
	unlimitedintegers::BigInt c(0);
	c = a - b;
}

int main()
{
	//t_Equality();
	//t_Sum();
	//t_Difference();

	unlimitedintegers::BigInt a(-1000);
	unlimitedintegers::BigInt b(9);
	unlimitedintegers::BigInt c;	

	c = b + a;

	a.Print();
	b.Print();
	c.Print();

	return 0;
}