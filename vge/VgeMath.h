#pragma once

namespace Vge
{
	class VGE_API Math
	{
	public:
		template < typename T >
		inline static T Max( T a, T b );

		template < typename T >
		inline static T Min( T a, T b );

		static float Sqrt( float x );

		static float Sin( float x );

		static float Cos( float x );

		static float Atan( float x );

		static float Atan2( float y, float x );

		static float Floor( float x );

		static float Ceil( float x );

		static int Abs( int x );

		static float Abs( float x );

		static float Fmod( float x, float y );

		static float Exp( float x );

	};

	template < typename T >
	inline T Math::Max( T a, T b )
	{
		return a > b ? a : b;
	}

	template < typename T >
	inline T Math::Min( T a, T b )
	{
		return a < b ? a : b;
	}

	/*
	#define MAX(a, b) ((a > b) ? (a) : (b))

	class BigNumber
	{
	public:
	BigNumber(){}
	BigNumber(const vchar* bignum)
	{
	FromString(bignum);
	}

	BigNumber( const BigNumber& bignum)
	{
	mBigNumber = bignum.mBigNumber;
	}

	BigNumber& operator =(const BigNumber& bignum)
	{
	mBigNumber = bignum.mBigNumber;
	return *this;
	}

	void FromString(const vchar* bignum)
	{
	mBigNumber.clear();

	vchar* p =(vchar*)bignum;
	while (*p != VT('\0'))
	{
	if (!IsNumber(*p))
	{
	mBigNumber.clear();
	break;
	}
	else
	{
	int num = (*p) - VT('0');
	mBigNumber.push_back(num);
	}

	p++;
	}
	}

	String ToString()
	{
	StrStream str;

	for (dword i = 0; i < mBigNumber.size(); i++)
	{
	vchar vch = vchar(mBigNumber[i] + VT('0'));
	if (vch != VT('0'))
	str << vch;
	}

	return str.str();
	}

	BigNumber operator +(const BigNumber& bignum)
	{
	BigNumber retbignum;

	dword max = (dword)MAX(mBigNumber.size(), bignum.mBigNumber.size());
	vector<int>& retnum = retbignum.mBigNumber;
	retnum.resize(max+1);

	for (dword i = 0; i < retnum.size(); i++)
	retnum[i] = 0;

	dword acc = 0;
	dword i, j, k;
	for (i = 0, j = 0, k = 0; i < mBigNumber.size(), j < bignum.mBigNumber.size(); i++, j++, k++)
	{
	int num = mBigNumber[mBigNumber.size()-i-1] +
	bignum.mBigNumber[bignum.mBigNumber.size()-j-1];
	retnum[retnum.size()-k-1] = mBigNumber[mBigNumber.size()-i-1] +
	bignum.mBigNumber[bignum.mBigNumber.size()-j-1];

	retnum[retnum.size()-k-1] += acc;
	acc = retnum[retnum.size()-k-1] / 10;
	retnum[retnum.size()-k-1] %= 10;
	}

	if (i > j)
	{
	for (; i < mBigNumber.size(); i++, k++)
	{
	retnum[retnum.size()-k-1] = mBigNumber[mBigNumber.size()-i-1];

	retnum[retnum.size()-k-1] += acc;
	acc = retnum[retnum.size()-k-1] / 10;
	retnum[retnum.size()-k-1] %= 10;
	}
	}
	else
	{
	for (; j < bignum.mBigNumber.size(); j++, k++)
	{
	retnum[retnum.size()-k-1] = bignum.mBigNumber[bignum.mBigNumber.size()-j-1];

	retnum[retnum.size()-k-1] += acc;
	acc = retnum[retnum.size()-k-1] / 10;
	retnum[retnum.size()-k-1] %= 10;
	}
	}

	if (acc > 0)
	retnum[0] = acc;

	return retbignum;
	}

	private:
	inline bool IsNumber(vchar vch)
	{
	return vch >= VT('0') && vch <= VT('9');
	}

	vector<int>	mBigNumber;

	};
	*/

}