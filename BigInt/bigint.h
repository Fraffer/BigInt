#include <queue>

namespace unlimitednumbers
{
	typedef unsigned __int64 UINT64;

	class BigInt
	{		
	public:
		BigInt() = delete;
		explicit BigInt(const int value);
		explicit BigInt(const char value[]);
		BigInt(const BigInt& other);
		BigInt& operator =(const BigInt& other);
		~BigInt();

	protected:

	private:
		std::deque<UINT64> digits;
		bool bNegative;
	};
}	// namespace end