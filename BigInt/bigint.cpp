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

	bool BigInt::operator==(const BigInt& other) const
	{
		if (bNegative != other.bNegative)
			return false;
		if (digits.size() != other.digits.size())
			return false;
		if (digits.front() != other.digits.front())
			return false;
		if (digits.back() != other.digits.back())
			return false;

		for (int i = 0; i < digits.size(); i++)
		{
			if (digits[i] != other.digits[i])
				return false;
		}

		return true;
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

	BigInt& BigInt::operator-=(const BigInt& other)
	{
		// if the two numbers have opposite signs, then I need to keep the sign of the first operand
		if (bNegative != other.bNegative)
		{
			*this += other;
		}
		else
		{
			const BigInt& max = GetAbsMax(*this, other);
			const BigInt& min = GetAbsMin(*this, other);

			int borrow = 0, newDigit = 0;
			int minSize = min.digits.size(), maxSize = max.digits.size();
			
			int i;
			for (i = 0; i < minSize; i++)
			{								
				UINT64 tmp = max[i] - borrow;	

				borrow = tmp < min[i] ? 1 : 0;

				newDigit = (tmp + borrow * 10) - min[i];

				digits[i] = (newDigit);
			}

			while (borrow == 1)
			{
				if (max[i] > 0)
				{
					digits[i] -= borrow;
					borrow = 0;
				}
				else
					digits[i] = 9;
			}

			RemoveZerosPadding();
			
			bNegative = max.bNegative;
		}

		return *this;
	}

	BigInt BigInt::operator-(const BigInt& other) const
	{
		BigInt result;

		result = *this;
		result -= other;

		return result;
	}

	UINT64& BigInt::operator[](int i)
	{
		return digits[i];
	}

	const UINT64& BigInt::operator[](int i) const
	{
		return digits[i];
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

	int BigInt::Size() const
	{
		return digits.size();
	}

	bool BigInt::Sign() const
	{
		return bNegative;
	}
	
	UINT64 BigInt::GetMostSignificantDigit() const
	{
		return digits.back();
	}

	UINT64 BigInt::GetLessSignificantDigit() const
	{
		return digits.front();
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

	void BigInt::RemoveZerosPadding(int count/*=0*/)
	{
		int counter = 0;
		for (int i = digits.size() - 1; i > count; i--)
		{
			if (digits[i] != 0)
				return;

			if (count != 0 && counter == count)
				return;

			digits.pop_back();
			counter++;
		}
	}

	/*const BigInt& GetMax(const BigInt& a, const BigInt& b) 
	{
		int aSize = a.Size(), bSize = b.Size();
		UINT64 aMSDigit = a.GetMostSignificantDigit(), bMSDigit = b.GetMostSignificantDigit();		
		bool aSign = a.Sign(), bSign = b.Sign();

		if (aSize == bSize)
		{
			if (aMSDigit == bMSDigit)
			{
				if (aSign == bSign)
					return a;
				else if (aSign == false && bSign == true)
					return a;
				else if (aSign == true && bSign == false)
					return b;
			}
			else if (aMSDigit > bMSDigit)
			{
				if (aSign == false)
					return a;
				else 
					return b;
			}
			else
			{
				if (bSign == false)
					return b;
				else
					return a;
			}
		}
		else if (aSize > bSize)
		{
			if (aSign == false)
				return a;
			else
				return b;
		}
		else
		{
			if (bSign == false)
				return b;
			else
				return a;
		}
	}*/

	const BigInt& GetAbsMax(const BigInt& a, const BigInt& b)
	{
		int aSize = a.Size(), bSize = b.Size();
		UINT64 aMSDigit = a.GetMostSignificantDigit(), bMSDigit = b.GetMostSignificantDigit();
		bool aSign = a.Sign(), bSign = b.Sign();

		if (aSize == bSize)
		{
			if (aMSDigit == bMSDigit)
			{
				for (int i = aSize - 1; i > 0; i--)
				{
					if (a[i] > b[i])
						return a;
					else if (b[i] > a[i])
						return b;
					else
						continue;
				}

				return a;
			}
		}
		else if (aSize > bSize)
			return a;		
		else		
			return b;		
	}

	/*const BigInt& GetMin(const BigInt& a, const BigInt& b)
	{
		int aSize = a.Size(), bSize = b.Size();
		UINT64 aMSDigit = a.GetMostSignificantDigit(), bMSDigit = b.GetMostSignificantDigit();
		bool aSign = a.Sign(), bSign = b.Sign();

		if (aSize == bSize)
		{
			if (aMSDigit == bMSDigit)
			{
				if (aSign == bSign)
					return a;
				else if (aSign == false && bSign == true)
					return b;
				else if (aSign == true && bSign == false)
					return a;
			}
			else if (aMSDigit > bMSDigit)
			{
				if (aSign == false)
					return b;
				else
					return a;
			}
			else
			{
				if (bSign == false)
					return a;
				else
					return b;
			}
		}
		else if (aSize > bSize)
		{
			if (aSign == false)
				return b;
			else
				return a;
		}
		else
		{
			if (bSign == false)
				return a;
			else
				return b;
		}
	}*/

	const BigInt& GetAbsMin(const BigInt& a, const BigInt& b)
	{
		if (a == b) return a;

		int aSize = a.Size(), bSize = b.Size();
		UINT64 aMSDigit = a.GetMostSignificantDigit(), bMSDigit = b.GetMostSignificantDigit();
		bool aSign = a.Sign(), bSign = b.Sign();

		if (aSize == bSize)
		{
			if (aMSDigit == bMSDigit)
			{
				for (int i = aSize - 1; i > 0; i--)
				{
					if (a[i] > b[i])
						return b;
					else if (b[i] > a[i])
						return a;
					else
						continue;
				}

				return b;
			}
			else if (aMSDigit > bMSDigit)
				return b;
			else
				return a;
		}
		else if (aSize > bSize)
			return b;
		else
			return a;
	}

	bool GetSignOfMax(const BigInt& a, const BigInt& b)
	{
		return GetAbsMax(a, b).Sign();
	}
}	// namespace end