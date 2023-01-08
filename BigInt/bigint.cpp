#include <iostream>
#include <cmath>
#include "bigint.h"

namespace unlimitedintegers
{
	BigInt::BigInt() { }

	BigInt::BigInt(int value)
	{		
		bNegative = value < 0;
		ParseInt(abs(value));
	}

	BigInt::BigInt(char value[])
	{		
		ParseString(value);
	}

	BigInt::BigInt(const BigInt& other)
	{
		digits = other.digits;
		bNegative = other.bNegative;
	}

	BigInt& BigInt::operator=(const BigInt& other)
	{
		digits = other.digits;
		bNegative = other.bNegative;

		return *this;
	}
	
	BigInt BigInt::operator+(const BigInt& other) const
	{
		BigInt result;		

		result = *this;
		result += other;
		
		return result;
	}

	BigInt& BigInt::operator+=(const BigInt& other)
	{
		int carry = 0, newDigit = 0;
		int thisSize = digits.size(), otherSize = other.digits.size();		

		// if this BigInt has less digits then the other, then I add zeros in order to get the same size, since I will loop always on this BigInt size
		if (otherSize > thisSize)
		{ 
			AddZerosPadding(otherSize - thisSize);
			thisSize = digits.size();
		}

		for (int i = 0; i < thisSize; i++)
		{
			// this check will guarantee the case when the other BigInt has a lower size than this BigInt
			if (i < otherSize)		
				newDigit = digits.at(i) + other.digits.at(i) + carry;			
			else
				newDigit = digits.at(i) + carry;			
			
			// if the current digit result is higher than 9, than I need to carry 1 to next digits index
			carry = newDigit >= 10 ? 1 : 0;

			digits[i] = (newDigit % 10);
		}

		return *this;
	}

	BigInt BigInt::operator-(const BigInt& other) const
	{
		BigInt result;

		return result;
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

		digits.push_front(digit);
	}

	void BigInt::Print() const
	{
		if (bNegative) std::cout << '-';

		int size = digits.size();
		for (int i = size-1; i >= 0; i--)
		{
			std::cout << digits.at(i);
		}

		std::cout << std::endl;
	}

	void BigInt::AddZerosPadding(int count)
	{
		for (int i = 0; i < count; i++)
		{
			digits.push_back(0);
		}
	}
}	// namespace end