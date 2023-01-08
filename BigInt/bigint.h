#include <queue>
#include <string>

namespace unlimitedintegers
{
	typedef int UINT64;

	class BigInt
	{		
	public:
		BigInt();
		BigInt(int value);
		explicit BigInt(char value[]);
		BigInt(const BigInt& other);
		BigInt& operator =(const BigInt& other);
		BigInt operator +(const BigInt& other) const;
		BigInt operator -(const BigInt& other) const;
		BigInt operator *(const BigInt& other) const;
		BigInt operator /(const BigInt& other) const;
		BigInt& operator +=(const BigInt& other);
		BigInt& operator -=(const BigInt& other);		
		BigInt& operator *=(const BigInt& other);		
		BigInt& operator /=(const BigInt& other);
		~BigInt();

		void Print() const;

	protected:
		void ParseInt(int value);
		void ParseString(char value[]);
		void AddZerosPadding(int count);
	private:
		std::deque<UINT64> digits;
		bool bNegative;
	};
}	// namespace end