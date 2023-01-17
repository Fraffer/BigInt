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
	
	bool BigInt::operator!=(const BigInt& other) const
	{
		return !(*this == other);
	}

	BigInt BigInt::operator+(const BigInt& other) const
	{
		BigInt result;

		BigInt max = GetAbsMax(*this, other);
		BigInt min = GetAbsMin(*this, other);

		// the sign is determined by the max operand
		if (max.bNegative == false && min.bNegative == true)
		{
			BigInt tmp = min;
			tmp.bNegative = false;
			result = max - tmp;
			return result;
		}
		if (max.bNegative == true && min.bNegative == false)
		{
			BigInt tmp = min;
			tmp.bNegative = true;
			result = max - tmp;
			return result;
		}

		int carry = 0, newDigit = 0;
		int thisSize = digits.size(), otherSize = other.digits.size();		

		for (int i = 0; i < max.digits.size(); i++)
		{
			if (i >= min.digits.size())
			{
				newDigit = max.digits[i] + carry;
			}
			else
				newDigit = max.digits[i] + min.digits[i] +  carry;

			carry = newDigit >= 10 ? 1 : 0;
			result.digits.push_back(newDigit % 10);
		}

		result.bNegative = bNegative;
		return result;
	}

	BigInt& BigInt::operator+=(const BigInt& other)
	{
		BigInt result = *this + other;
		return result;
	}

	BigInt& BigInt::operator-=(const BigInt& other)
	{		
		BigInt result = *this - other;
		return result;
	}

	BigInt BigInt::operator-(const BigInt& other) const
	{
		BigInt result;

		BigInt max = GetAbsMax(*this, other);
		BigInt min = GetAbsMin(*this, other);

		// the sign is determined by the first operand
		if (this->bNegative == false && other.bNegative == true)
		{
			BigInt tmp = other;
			tmp.bNegative = false;
			result = *this + tmp;
			return result;
		}
		if (this->bNegative == true && other.bNegative == false)
		{
			BigInt tmp = other;
			tmp.bNegative = true;
			result = *this + tmp;
			return result;
		}

		int borrow = 0, newDigit = 0;
		int minSize = min.digits.size(), maxSize = max.digits.size(), thisSize = digits.size(), otherSize = other.digits.size();

		min.AddZerosPadding(maxSize - minSize);
		minSize = min.digits.size();

		int i;
		for (i = 0; i < minSize; i++)
		{
			UINT64 tmp = max[i] - borrow;

			borrow = tmp < min[i] ? 1 : 0;

			newDigit = (tmp + borrow * 10) - min[i];

			result.digits.push_back(newDigit);
		}

		result.RemoveZerosPadding();

		if (bNegative == false)
		{
			if (max == other) result.bNegative = true;
			else result.bNegative = false;
		}
		else
		{
			if (max == other) result.bNegative = false;
			else result.bNegative = true;
		}

		return result;
	}

	BigInt BigInt::operator*(const BigInt& other) const
	{
		BigInt result(0);		

		BigInt max = GetAbsMax(*this, other);
		BigInt min = GetAbsMin(*this, other);

		int minSize = min.digits.size(), maxSize = max.digits.size(), thisSize = digits.size(), otherSize = other.digits.size();

		min.AddZerosPadding(maxSize - minSize);
		minSize = min.digits.size();

		for (int i = 0; i < otherSize; i++)
		{
			UINT64 tmp = 0;
			UINT64 multiplier = other[i];
			for (int j = 0; j < thisSize; j++)
			{
				UINT64 currentDigit = digits[j];
				int innerExponent = pow(10, j);
				tmp += currentDigit * multiplier * innerExponent;
			}
			int outerExponent = pow(10, i);
			BigInt a(tmp * outerExponent);

			BigInt value = result + a;
			result = value;
		}

		if (bNegative == true &&  other.bNegative == true)
			result.bNegative = false;
		if (bNegative == false && other.bNegative == false)
			result.bNegative = false;
		if (bNegative == false && other.bNegative == true)
			result.bNegative = true;
		if (bNegative == true && other.bNegative == false)
			result.bNegative = true;

		return result;
	}

	bool BigInt::operator >(const BigInt& other) const
	{	
		if (*this == other) return false;

		if (bNegative == true && other.bNegative == false)
			return false;
		if (bNegative == other.bNegative == true)
		{
			if (digits.size() > other.digits.size())
				return false;
			if (digits.front() > other.digits.front())
				return false;
			if (digits.back() > other.digits.back())
				return false;

			for (int i = 0; i < digits.size(); i++)
			{
				if (digits[i] >= other.digits[i])
					return false;
			}
		}
		if (bNegative == other.bNegative == false)
		{
			if (digits.size() < other.digits.size())
				return false;
			if (digits.front() < other.digits.front())
				return false;
			if (digits.back() < other.digits.back())
				return false;

			for (int i = 0; i < digits.size(); i++)
			{
				if (digits[i] <= other.digits[i])
					return false;
			}
		}

		return true;
	}

	bool BigInt::operator >=(const BigInt& other) const
	{
		if (*this == other) return true;

		return *this > other;
	}

	bool BigInt::operator <(const BigInt& other) const
	{
		if (*this == other) return false;

		if (bNegative == false && other.bNegative == true)
			return false;
		if (bNegative == other.bNegative == false)
		{
			if (digits.size() > other.digits.size())
				return false;
			if (digits.front() > other.digits.front())
				return false;
			if (digits.back() > other.digits.back())
				return false;

			for (int i = 0; i < digits.size(); i++)
			{
				if (digits[i] >= other.digits[i])
					return false;
			}
		}
		if (bNegative == other.bNegative == true)
		{
			if (digits.size() < other.digits.size())
				return false;
			if (digits.front() < other.digits.front())
				return false;
			if (digits.back() < other.digits.back())
				return false;

			for (int i = 0; i < digits.size(); i++)
			{
				if (digits[i] <= other.digits[i])
					return false;
			}
		}

		return true;
	}

	bool BigInt::operator <=(const BigInt& other) const
	{
		if (*this == other) return true;

		return *this < other;
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
			else if (aMSDigit >= bMSDigit)
				return a;
			else
				return b;				 
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