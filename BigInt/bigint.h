#include <queue>
#include <string>

namespace unlimitednumbers
{
	typedef int UINT64;

	class BigInt
	{		
	public:
		BigInt() = delete;
		BigInt(int value);
		explicit BigInt(char value[]);
		BigInt(const BigInt& other);
		BigInt& operator =(const BigInt& other);
		BigInt& operator =(const int other);
		~BigInt();

		void Print() const;

	protected:
		void ParseInt(int value);
		void ParseString(char value[]);
	private:
		std::deque<UINT64> digits;
		bool bNegative;
	};
}	// namespace end