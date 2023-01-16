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
		bool operator ==(const BigInt& other) const;
		bool operator !=(const BigInt& other) const;
		BigInt operator +(const BigInt& other) const;
		BigInt operator -(const BigInt& other) const;
		BigInt operator *(const BigInt& other) const;
		BigInt operator /(const BigInt& other) const;
		BigInt& operator +=(const BigInt& other);
		BigInt& operator -=(const BigInt& other);		
		BigInt& operator *=(const BigInt& other);		
		BigInt& operator /=(const BigInt& other);
		BigInt& operator ++();
		BigInt& operator --();
		bool operator >(const BigInt& other) const;
		bool operator >=(const BigInt& other) const;
		bool operator <(const BigInt& other) const;
		bool operator <=(const BigInt& other) const;
		UINT64& operator [](int i);
		const UINT64& operator [](int i) const;
		~BigInt();

		int Size() const;
		bool Sign() const;
		UINT64 GetMostSignificantDigit() const;
		UINT64 GetLessSignificantDigit() const;
		void Print() const;

	protected:
		void ParseInt(int value);
		void ParseString(char value[]);
		void AddZerosPadding(int count);
		void RemoveZerosPadding(int count=0);
		
	private:
		std::deque<UINT64> digits;
		bool bNegative;
	};

	//const BigInt& GetMax(const BigInt& a, const BigInt& b);
	const BigInt& GetAbsMax(const BigInt& a, const BigInt& b);
	const BigInt& GetAbsMin(const BigInt& a, const BigInt& b);
	//const BigInt& GetMin(const BigInt& a, const BigInt& b);
	bool GetSignOfMax(const BigInt& a, const BigInt& b);
}	// namespace end