#include "BigInt.h"
#include "test_runner.h"

#include <iostream>
#include <sstream>
#include <tuple>

void TestOut();
void TestIn();
void TestEqual();
void TestMore();
void TestLess();
void TestMoreEqual();
void TestLessEqual();
void TestSum();
void TestDif();
void TestSumEqual();
void TestDifEqual();
void TestMul();
void TestMulEqual();
void TestDivByTwo();
void TestDivMod();

int main() {
	TestRunner tr;

	RUN_TEST(tr, TestOut);
	RUN_TEST(tr, TestIn);
	RUN_TEST(tr, TestEqual);
	RUN_TEST(tr, TestMore);
	RUN_TEST(tr, TestLess);
	RUN_TEST(tr, TestMoreEqual);
	RUN_TEST(tr, TestLessEqual);
	RUN_TEST(tr, TestSum);
	RUN_TEST(tr, TestDif);
	RUN_TEST(tr, TestSumEqual);
	RUN_TEST(tr, TestDifEqual);
	RUN_TEST(tr, TestMul);
	RUN_TEST(tr, TestMulEqual);
	RUN_TEST(tr, TestDivByTwo);
	RUN_TEST(tr, TestDivMod);

	return 0;
}

void TestOut() {
	{
		BigInt a("12637");
		std::stringstream ss;
		ss << a;
		ASSERT_EQUAL(ss.str(), "12637");
	}

	{
		BigInt a("-12637");
		std::stringstream ss;
		ss << a;
		ASSERT_EQUAL(ss.str(), "-12637");
	}

	{
		BigInt a("0");
		std::stringstream ss;
		ss << a;
		ASSERT_EQUAL(ss.str(), "0");
	}

	{
		BigInt a;
		std::stringstream ss;
		ss << a;
		ASSERT_EQUAL(ss.str(), "0");
	}

	{
		BigInt a(126);
		std::stringstream ss;
		ss << a;
		ASSERT_EQUAL(ss.str(), "126");
	}

	{
		BigInt a(-15);
		std::stringstream ss;
		ss << a;
		ASSERT_EQUAL(ss.str(), "-15");
	}
}

void TestIn() {
	{
		std::stringstream ssOut("271271812");
		BigInt a;
		ssOut >> a;

		std::stringstream ssIn;
		ssIn << a;

		ASSERT_EQUAL(ssIn.str(), "271271812");
	}
	{
		std::stringstream ssOut("-271271812");
		BigInt a;
		ssOut >> a;

		std::stringstream ssIn;
		ssIn << a;

		ASSERT_EQUAL(ssIn.str(), "-271271812");
	}
}

void TestEqual() {
	{
		BigInt a;
		BigInt b;
		ASSERT(a == b);
	} 
	{
		BigInt a("-621781");
		BigInt b("-621781");
		ASSERT(a == b);
	}
	{
		BigInt a("621781");
		BigInt b("621781");
		ASSERT(a == b);
	}
	{
		BigInt a("-621781");
		BigInt b;
		b = a;
		ASSERT(a == b);
	}
}

void TestMore() {
	{
		BigInt a;
		BigInt b("0");
		ASSERT(!(a > b));
	}
	{
		BigInt a("6327");
		BigInt b("-4");
		ASSERT(a > b);
	}
	{
		BigInt a("-6327");
		BigInt b("-4");
		ASSERT(b > a);
	}
	{
		BigInt a("6327");
		BigInt b("4");
		ASSERT(a > b);
	}
}

void TestLess() {
	{
		BigInt a;
		BigInt b("0");
		ASSERT(!(b < a));
	}
	{
		BigInt a("6327");
		BigInt b("-4");
		ASSERT(b < a);
	}
	{
		BigInt a("-6327");
		BigInt b("-4");
		ASSERT(a < b);
	}
	{
		BigInt a("6327");
		BigInt b("4");
		ASSERT(b < a);
	}
}

void TestMoreEqual() {
	{
		BigInt a;
		BigInt b("0");
		ASSERT(a >= b);
	}
	{
		BigInt a("6327");
		BigInt b("-4");
		ASSERT(a >= b);
	}
	{
		BigInt a("-6327");
		BigInt b("-4");
		ASSERT(b >= a);
	}
	{
		BigInt a("6327");
		BigInt b("4");
		ASSERT(a >= b);
	}
	{
		BigInt a("362736");
		BigInt b("362736");
		ASSERT(a >= b);
	}
	{
		BigInt a("-362736");
		BigInt b("-362736");
		ASSERT(a >= b);
	}
}

void TestLessEqual() {
	{
		BigInt a;
		BigInt b("0");
		ASSERT(b <= a);
	}
	{
		BigInt a("6327");
		BigInt b("-4");
		ASSERT(b <= a);
	}
	{
		BigInt a("-6327");
		BigInt b("-4");
		ASSERT(a <= b);
	}
	{
		BigInt a("6327");
		BigInt b("4");
		ASSERT(b <= a);
	}
	{
		BigInt a("362736");
		BigInt b("362736");
		ASSERT(a <= b);
	}
	{
		BigInt a("-362736");
		BigInt b("-362736");
		ASSERT(a <= b);
	}
}

void TestSum() {
	{
		BigInt a("123456789");
		BigInt b("987654321");
		std::stringstream ss;
		ss << a + b;
		ASSERT_EQUAL(ss.str(), "1111111110");
	}
	{
		BigInt a("-123456789");
		BigInt b("-987654321");
		std::stringstream ss;
		ss << a + b;
		ASSERT_EQUAL(ss.str(), "-1111111110");
	}
	{
		BigInt a;
		BigInt b("987654321");
		std::stringstream ss;
		ss << a + b;
		ASSERT_EQUAL(ss.str(), "987654321");
	}
	{
		BigInt a;
		BigInt b("-987654321");
		std::stringstream ss;
		ss << b + a;
		ASSERT_EQUAL(ss.str(), "-987654321");
	}
	{
		BigInt a;
		BigInt b("0");
		std::stringstream ss;
		ss << b + a;
		ASSERT_EQUAL(ss.str(), "0");
	}
	{
		BigInt a("123456789");
		BigInt b("-987654321");
		std::stringstream ss;
		ss << b + a;
		ASSERT_EQUAL(ss.str(), "-864197532");
	}
	{
		BigInt a("123456789");
		BigInt b("-987654321");
		std::stringstream ss;
		ss << a + b;
		ASSERT_EQUAL(ss.str(), "-864197532");
	}
	{
		BigInt a("-123456789");
		BigInt b("987654321");
		std::stringstream ss;
		ss << b + a;
		ASSERT_EQUAL(ss.str(), "864197532");
	}
	{
		BigInt a("-123456789");
		BigInt b("987654321");
		std::stringstream ss;
		ss << a + b;
		ASSERT_EQUAL(ss.str(), "864197532");
	}
	{
		BigInt a("123456789");
		BigInt b("-123456789");
		std::stringstream ss;
		ss << a + b;
		ASSERT_EQUAL(ss.str(), "0");
	}
}

void TestDif() {
	{
		BigInt a("123456789");
		BigInt b("987654321");
		std::stringstream ss;
		ss << b - a;
		ASSERT_EQUAL(ss.str(), "864197532");
	}
	{
		BigInt a("123456789");
		BigInt b("987654321");
		std::stringstream ss;
		ss << a - b;
		ASSERT_EQUAL(ss.str(), "-864197532");
	}
	{
		BigInt a("-123456789");
		BigInt b("-987654321");
		std::stringstream ss;
		ss << a - b;
		ASSERT_EQUAL(ss.str(), "864197532");
	}
	{
		BigInt a("-123456789");
		BigInt b("-987654321");
		std::stringstream ss;
		ss << b - a;
		ASSERT_EQUAL(ss.str(), "-864197532");
	}
	{
		BigInt a;
		BigInt b("-987654321");
		std::stringstream ss;
		ss << a - b;
		ASSERT_EQUAL(ss.str(), "987654321");
	}
	{
		BigInt a;
		BigInt b("-987654321");
		std::stringstream ss;
		ss << b - a;
		ASSERT_EQUAL(ss.str(), "-987654321");
	}
	{
		BigInt a;
		BigInt b("0");
		std::stringstream ss;
		ss << b - a;
		ASSERT_EQUAL(ss.str(), "0");
	}
	{
		BigInt a("123456789");
		BigInt b("-987654321");
		std::stringstream ss;
		ss << b - a;
		ASSERT_EQUAL(ss.str(), "-1111111110");
	}
	{
		BigInt a("123456789");
		BigInt b("-987654321");
		std::stringstream ss;
		ss << a - b;
		ASSERT_EQUAL(ss.str(), "1111111110");
	}
	{
		BigInt a("-123456789");
		BigInt b("987654321");
		std::stringstream ss;
		ss << b - a;
		ASSERT_EQUAL(ss.str(), "1111111110");
	}
	{
		BigInt a("-123456789");
		BigInt b("987654321");
		std::stringstream ss;
		ss << a - b;
		ASSERT_EQUAL(ss.str(), "-1111111110");
	}
	{
		BigInt a("123456789");
		BigInt b("123456789");
		std::stringstream ss;
		ss << a - b;
		ASSERT_EQUAL(ss.str(), "0");
	}
}

void TestSumEqual() {
	{
		BigInt a("123456789");
		BigInt b("987654321");
		a += b;
		std::stringstream ss;
		ss << a;
		ASSERT_EQUAL(ss.str(), "1111111110");
	}
	{
		BigInt a("-123456789");
		BigInt b("-987654321");
		a += b;
		std::stringstream ss;
		ss << a;
		ASSERT_EQUAL(ss.str(), "-1111111110");
	}
	{
		BigInt a;
		BigInt b("987654321");
		a += b;
		std::stringstream ss;
		ss << a;
		ASSERT_EQUAL(ss.str(), "987654321");
	}
	{
		BigInt a;
		BigInt b("-987654321");
		b += a;
		std::stringstream ss;
		ss << b;
		ASSERT_EQUAL(ss.str(), "-987654321");
	}
	{
		BigInt a;
		BigInt b("0");
		b += a;
		std::stringstream ss;
		ss << b;
		ASSERT_EQUAL(ss.str(), "0");
	}
	{
		BigInt a("123456789");
		BigInt b("-987654321");
		b += a;
		std::stringstream ss;
		ss << b;
		ASSERT_EQUAL(ss.str(), "-864197532");
	}
	{
		BigInt a("123456789");
		BigInt b("-987654321");
		a += b;
		std::stringstream ss;
		ss << a;
		ASSERT_EQUAL(ss.str(), "-864197532");
	}
	{
		BigInt a("-123456789");
		BigInt b("987654321");
		b += a;
		std::stringstream ss;
		ss << b;
		ASSERT_EQUAL(ss.str(), "864197532");
	}
	{
		BigInt a("-123456789");
		BigInt b("987654321");
		a += b;
		std::stringstream ss;
		ss << a;
		ASSERT_EQUAL(ss.str(), "864197532");
	}
	{
		BigInt a("123456789");
		BigInt b("-123456789");
		a += b;
		std::stringstream ss;
		ss << a;
		ASSERT_EQUAL(ss.str(), "0");
	}
}

void TestDifEqual() {
	{
		BigInt a("123456789");
		BigInt b("987654321");
		b -= a;
		std::stringstream ss;
		ss << b;
		ASSERT_EQUAL(ss.str(), "864197532");
	}
	{
		BigInt a("123456789");
		BigInt b("987654321");
		a -= b;
		std::stringstream ss;
		ss << a;
		ASSERT_EQUAL(ss.str(), "-864197532");
	}
	{
		BigInt a("-123456789");
		BigInt b("-987654321");
		a -= b;
		std::stringstream ss;
		ss << a;
		ASSERT_EQUAL(ss.str(), "864197532");
	}
	{
		BigInt a("-123456789");
		BigInt b("-987654321");
		b -= a;
		std::stringstream ss;
		ss << b;
		ASSERT_EQUAL(ss.str(), "-864197532");
	}
	{
		BigInt a;
		BigInt b("-987654321");
		a -= b;
		std::stringstream ss;
		ss << a;
		ASSERT_EQUAL(ss.str(), "987654321");
	}
	{
		BigInt a;
		BigInt b("-987654321");
		b -= a;
		std::stringstream ss;
		ss << b;
		ASSERT_EQUAL(ss.str(), "-987654321");
	}
	{
		BigInt a;
		BigInt b("0");
		b -= a;
		std::stringstream ss;
		ss << b;
		ASSERT_EQUAL(ss.str(), "0");
	}
	{
		BigInt a("123456789");
		BigInt b("-987654321");
		b -= a;
		std::stringstream ss;
		ss << b;
		ASSERT_EQUAL(ss.str(), "-1111111110");
	}
	{
		BigInt a("123456789");
		BigInt b("-987654321");
		a -= b;
		std::stringstream ss;
		ss << a;
		ASSERT_EQUAL(ss.str(), "1111111110");
	}
	{
		BigInt a("-123456789");
		BigInt b("987654321");
		b -= a;
		std::stringstream ss;
		ss << b;
		ASSERT_EQUAL(ss.str(), "1111111110");
	}
	{
		BigInt a("-123456789");
		BigInt b("987654321");
		a -= b;
		std::stringstream ss;
		ss << a;
		ASSERT_EQUAL(ss.str(), "-1111111110");
	}
	{
		BigInt a("123456789");
		BigInt b("123456789");
		a -= b;
		std::stringstream ss;
		ss << a;
		ASSERT_EQUAL(ss.str(), "0");
	}
}

void TestAbs() {
	{
		BigInt a("6323323");
		std::stringstream ss;
		ss << Abs(a);
		ASSERT_EQUAL(ss.str(), "6323323");
	}
	{
		BigInt a("-6323323");
		std::stringstream ss;
		ss << Abs(a);
		ASSERT_EQUAL(ss.str(), "6323323");
	}
	{
		BigInt a("-6323323");
		std::stringstream ss;
		ss << Abs(a);
		ASSERT_EQUAL(ss.str(), "6323323");
	}
}

void TestMul() {
	{
		BigInt a;
		BigInt b;
		std::stringstream ss;
		ss << a * b;
		ASSERT_EQUAL(ss.str(), "0");
	}
	{
		BigInt a("362732");
		BigInt b;
		std::stringstream ss;
		ss << a * b;
		ASSERT_EQUAL(ss.str(), "0");
	}
	{
		BigInt a("362732");
		BigInt b;
		std::stringstream ss;
		ss << b * a;
		ASSERT_EQUAL(ss.str(), "0");
	}
	{
		BigInt a("362732");
		BigInt b("2162");
		std::stringstream ss;
		ss << b * a;
		ASSERT_EQUAL(ss.str(), "784226584");
	}
	{
		BigInt a("-362732");
		BigInt b("2162");
		std::stringstream ss;
		ss << b * a;
		ASSERT_EQUAL(ss.str(), "-784226584");
	}
}

void TestMulEqual() {
	{
		BigInt a;
		BigInt b;
		a *= b;
		std::stringstream ss;
		ss << a;
		ASSERT_EQUAL(ss.str(), "0");
	}
	{
		BigInt a("362732");
		BigInt b;
		a *= b;
		std::stringstream ss;
		ss << a;
		ASSERT_EQUAL(ss.str(), "0");
	}
	{
		BigInt a("362732");
		BigInt b;
		b *= a;
		std::stringstream ss;
		ss << b;
		ASSERT_EQUAL(ss.str(), "0");
	}
	{
		BigInt a("362732");
		BigInt b("2162");
		b *= a;
		std::stringstream ss;
		ss << b;
		ASSERT_EQUAL(ss.str(), "784226584");
	}
	{
		BigInt a("-362732");
		BigInt b("2162");
		b *= a;
		std::stringstream ss;
		ss << b;
		ASSERT_EQUAL(ss.str(), "-784226584");
	}
}

void TestDivByTwo() {
	{
		BigInt a("125612");
		std::stringstream ss;
		ss << DivByTwo(a);
		ASSERT_EQUAL(ss.str(), "62806");
	}
	{
		BigInt a;
		std::stringstream ss;
		ss << DivByTwo(a);
		ASSERT_EQUAL(ss.str(), "0");
	}
	{
		BigInt a("-125612");
		std::stringstream ss;
		ss << DivByTwo(a);
		ASSERT_EQUAL(ss.str(), "-62806");
	}
	{
		BigInt a("125613");
		std::stringstream ss;
		ss << DivByTwo(a);
		ASSERT_EQUAL(ss.str(), "62806");
	}
	{
		BigInt a("-125613");
		std::stringstream ss;
		ss << DivByTwo(a);
		ASSERT_EQUAL(ss.str(), "-62806");
	}
}

void TestDivMod() {
	{
		BigInt a("1234");
		BigInt b("35");
		std::tuple<BigInt, BigInt> t = DivMod(a, b);
		BigInt div = std::get<0>(t);
		BigInt mod = std::get<1>(t);
		std::stringstream smod, sdiv;
		sdiv << div;
		smod << mod;
		ASSERT_EQUAL(sdiv.str(), "35");
		ASSERT_EQUAL(smod.str(), "9");
	}
	{
		BigInt a("-1234");
		BigInt b("35");
		std::tuple<BigInt, BigInt> t = DivMod(a, b);
		BigInt div = std::get<0>(t);
		BigInt mod = std::get<1>(t);
		std::stringstream smod, sdiv;
		sdiv << div;
		smod << mod;
		ASSERT_EQUAL(sdiv.str(), "-35");
		ASSERT_EQUAL(smod.str(), "-9");
	}
	{
		BigInt a("-1234");
		BigInt b("-35");
		std::tuple<BigInt, BigInt> t = DivMod(a, b);
		BigInt div = std::get<0>(t);
		BigInt mod = std::get<1>(t);
		std::stringstream smod, sdiv;
		sdiv << div;
		smod << mod;
		ASSERT_EQUAL(sdiv.str(), "35");
		ASSERT_EQUAL(smod.str(), "-9");
	}
	{
		BigInt a("1234");
		BigInt b("-35");
		std::tuple<BigInt, BigInt> t = DivMod(a, b);
		BigInt div = std::get<0>(t);
		BigInt mod = std::get<1>(t);
		std::stringstream smod, sdiv;
		sdiv << div;
		smod << mod;
		ASSERT_EQUAL(sdiv.str(), "-35");
		ASSERT_EQUAL(smod.str(), "9");
	}
	{
		BigInt a;
		BigInt b("-35");
		std::tuple<BigInt, BigInt> t = DivMod(a, b);
		BigInt div = std::get<0>(t);
		BigInt mod = std::get<1>(t);
		std::stringstream smod, sdiv;
		sdiv << div;
		smod << mod;
		ASSERT_EQUAL(sdiv.str(), "0");
		ASSERT_EQUAL(smod.str(), "0");
	}
	{
		BigInt a("172");
		BigInt b("-356");
		std::tuple<BigInt, BigInt> t = DivMod(a, b);
		BigInt div = std::get<0>(t);
		BigInt mod = std::get<1>(t);
		std::stringstream smod, sdiv;
		sdiv << div;
		smod << mod;
		ASSERT_EQUAL(sdiv.str(), "0");
		ASSERT_EQUAL(smod.str(), "172");
	}
	{
		BigInt a("-172");
		BigInt b("-356");
		std::tuple<BigInt, BigInt> t = DivMod(a, b);
		BigInt div = std::get<0>(t);
		BigInt mod = std::get<1>(t);
		std::stringstream smod, sdiv;
		sdiv << div;
		smod << mod;
		ASSERT_EQUAL(sdiv.str(), "0");
		ASSERT_EQUAL(smod.str(), "-172");
	}
}