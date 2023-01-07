#include <iostream>
#include "bigint.h"

namespace unlimitednumbers
{
	BigInt::BigInt(int value)
	{		
		ParseInt(value);
	}

	BigInt::BigInt(char value[])
	{		
		ParseString(value);
	}

	BigInt::BigInt(const BigInt& other)
	{

	}

	BigInt& BigInt::operator=(const BigInt& other)
	{
		digits = other.digits;
		bNegative = other.bNegative;

		return *this;
	}

	BigInt::~BigInt()
	{
	}

	// WIP
	void BigInt::ParseString(char value[])
	{
		int size = sizeof(value) / sizeof(value[0]);
		for(int i = 0; i < size; i++)
		{			
			UINT64 r = value[i] - '0'; // since in ASCII numbers start from 48, I need to subtract the corresponding char, that is '0'
			digits.push_front(r);
		}				
	}

	void BigInt::ParseInt(int value)
	{
		if (value >= 10)
			ParseInt(value / 10);

		int digit = value % 10;

		digits.push_back(digit);
	}

	void BigInt::Print() const
	{
		for (auto d : digits)
		{
			std::cout << d;
		}

		std::cout << std::endl;
	}
}	// namespace end