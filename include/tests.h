#pragma once

#include "UnitTestFramework.h"
#include "BigInt.h"

#include <sstream>
#include <tuple>

void TestOut() {
	{
		BigInt a("12637");
		std::stringstream ss;
		ss << a;
		AssertEqual(ss.str(), "12637", "First test");
	}

	{
		BigInt a("-12637");
		std::stringstream ss;
		ss << a;
		AssertEqual(ss.str(), "-12637", "Second test");
	}

	{
		BigInt a("0");
		std::stringstream ss;
		ss << a;
		AssertEqual(ss.str(), "0", "Third test");
	}

	{
		BigInt a;
		std::stringstream ss;
		ss << a;
		AssertEqual(ss.str(), "0", "Forth test");
	}
}

void TestIn() {
	{
		std::stringstream ssOut("271271812");
		BigInt a;
		ssOut >> a;

		std::stringstream ssIn;
		ssIn << a;

		AssertEqual(ssIn.str(), "271271812", "First test");
	}
	{
		std::stringstream ssOut("-271271812");
		BigInt a;
		ssOut >> a;

		std::stringstream ssIn;
		ssIn << a;

		AssertEqual(ssIn.str(), "-271271812", "Second test");
	}
}

void TestEqual() {
	{
		BigInt a;
		BigInt b;
		Assert(a == b, "First test");
	} 
	{
		BigInt a("-621781");
		BigInt b("-621781");
		Assert(a == b, "Second test");
	}
	{
		BigInt a("621781");
		BigInt b("621781");
		Assert(a == b, "Third test");
	}
	{
		BigInt a("-621781");
		BigInt b;
		b = a;
		Assert(a == b, "Forth test");
	}
}

void TestMore() {
	{
		BigInt a;
		BigInt b("0");
		Assert(!(a > b), "First test");
	}
	{
		BigInt a("6327");
		BigInt b("-4");
		Assert(a > b, "Second test");
	}
	{
		BigInt a("-6327");
		BigInt b("-4");
		Assert(b > a, "Third test");
	}
	{
		BigInt a("6327");
		BigInt b("4");
		Assert(a > b, "Forth test");
	}
}

void TestLess() {
	{
		BigInt a;
		BigInt b("0");
		Assert(!(b < a), "First test");
	}
	{
		BigInt a("6327");
		BigInt b("-4");
		Assert(b < a, "Second test");
	}
	{
		BigInt a("-6327");
		BigInt b("-4");
		Assert(a < b, "Third test");
	}
	{
		BigInt a("6327");
		BigInt b("4");
		Assert(b < a, "Forth test");
	}
}

void TestMoreEqual() {
	{
		BigInt a;
		BigInt b("0");
		Assert(a >= b, "First test");
	}
	{
		BigInt a("6327");
		BigInt b("-4");
		Assert(a >= b, "Second test");
	}
	{
		BigInt a("-6327");
		BigInt b("-4");
		Assert(b >= a, "Third test");
	}
	{
		BigInt a("6327");
		BigInt b("4");
		Assert(a >= b, "Forth test");
	}
	{
		BigInt a("362736");
		BigInt b("362736");
		Assert(a >= b, "Fifth test");
	}
	{
		BigInt a("-362736");
		BigInt b("-362736");
		Assert(a >= b, "Sixth test");
	}
}

void TestLessEqual() {
	{
		BigInt a;
		BigInt b("0");
		Assert(b <= a, "First test");
	}
	{
		BigInt a("6327");
		BigInt b("-4");
		Assert(b <= a, "Second test");
	}
	{
		BigInt a("-6327");
		BigInt b("-4");
		Assert(a <= b, "Third test");
	}
	{
		BigInt a("6327");
		BigInt b("4");
		Assert(b <= a, "Forth test");
	}
	{
		BigInt a("362736");
		BigInt b("362736");
		Assert(a <= b, "Fifth test");
	}
	{
		BigInt a("-362736");
		BigInt b("-362736");
		Assert(a <= b, "Sixth test");
	}
}

void TestSum() {
	{
		BigInt a("123456789");
		BigInt b("987654321");
		std::stringstream ss;
		ss << a + b;
		AssertEqual(ss.str(), "1111111110", "First test");
	}
	{
		BigInt a("-123456789");
		BigInt b("-987654321");
		std::stringstream ss;
		ss << a + b;
		AssertEqual(ss.str(), "-1111111110", "Second test");
	}
	{
		BigInt a;
		BigInt b("987654321");
		std::stringstream ss;
		ss << a + b;
		AssertEqual(ss.str(), "987654321", "Third test");
	}
	{
		BigInt a;
		BigInt b("-987654321");
		std::stringstream ss;
		ss << b + a;
		AssertEqual(ss.str(), "-987654321", "Forth test");
	}
	{
		BigInt a;
		BigInt b("0");
		std::stringstream ss;
		ss << b + a;
		AssertEqual(ss.str(), "0", "Fifth test");
	}
	{
		BigInt a("123456789");
		BigInt b("-987654321");
		std::stringstream ss;
		ss << b + a;
		AssertEqual(ss.str(), "-864197532", "Sixth test");
	}
	{
		BigInt a("123456789");
		BigInt b("-987654321");
		std::stringstream ss;
		ss << a + b;
		AssertEqual(ss.str(), "-864197532", "Seventh test");
	}
	{
		BigInt a("-123456789");
		BigInt b("987654321");
		std::stringstream ss;
		ss << b + a;
		AssertEqual(ss.str(), "864197532", "Eighth test");
	}
	{
		BigInt a("-123456789");
		BigInt b("987654321");
		std::stringstream ss;
		ss << a + b;
		AssertEqual(ss.str(), "864197532", "Nineth test");
	}
	{
		BigInt a("123456789");
		BigInt b("-123456789");
		std::stringstream ss;
		ss << a + b;
		AssertEqual(ss.str(), "0", "Tenth test");
	}
}

void TestDif() {
	{
		BigInt a("123456789");
		BigInt b("987654321");
		std::stringstream ss;
		ss << b - a;
		AssertEqual(ss.str(), "864197532", "First test");
	}
	{
		BigInt a("123456789");
		BigInt b("987654321");
		std::stringstream ss;
		ss << a - b;
		AssertEqual(ss.str(), "-864197532", "Second test");
	}
	{
		BigInt a("-123456789");
		BigInt b("-987654321");
		std::stringstream ss;
		ss << a - b;
		AssertEqual(ss.str(), "864197532", "Third test");
	}
	{
		BigInt a("-123456789");
		BigInt b("-987654321");
		std::stringstream ss;
		ss << b - a;
		AssertEqual(ss.str(), "-864197532", "Forth test");
	}
	{
		BigInt a;
		BigInt b("-987654321");
		std::stringstream ss;
		ss << a - b;
		AssertEqual(ss.str(), "987654321", "Fifth test");
	}
	{
		BigInt a;
		BigInt b("-987654321");
		std::stringstream ss;
		ss << b - a;
		AssertEqual(ss.str(), "-987654321", "Sixth test");
	}
	{
		BigInt a;
		BigInt b("0");
		std::stringstream ss;
		ss << b - a;
		AssertEqual(ss.str(), "0", "Seventh test");
	}
	{
		BigInt a("123456789");
		BigInt b("-987654321");
		std::stringstream ss;
		ss << b - a;
		AssertEqual(ss.str(), "-1111111110", "Eighth test");
	}
	{
		BigInt a("123456789");
		BigInt b("-987654321");
		std::stringstream ss;
		ss << a - b;
		AssertEqual(ss.str(), "1111111110", "Nineth test");
	}
	{
		BigInt a("-123456789");
		BigInt b("987654321");
		std::stringstream ss;
		ss << b - a;
		AssertEqual(ss.str(), "1111111110", "Tenth test");
	}
	{
		BigInt a("-123456789");
		BigInt b("987654321");
		std::stringstream ss;
		ss << a - b;
		AssertEqual(ss.str(), "-1111111110", "Eleventh test");
	}
	{
		BigInt a("123456789");
		BigInt b("123456789");
		std::stringstream ss;
		ss << a - b;
		AssertEqual(ss.str(), "0", "Twelveth test");
	}
}

void TestSumEqual() {
	{
		BigInt a("123456789");
		BigInt b("987654321");
		a += b;
		std::stringstream ss;
		ss << a;
		AssertEqual(ss.str(), "1111111110", "First test");
	}
	{
		BigInt a("-123456789");
		BigInt b("-987654321");
		a += b;
		std::stringstream ss;
		ss << a;
		AssertEqual(ss.str(), "-1111111110", "Second test");
	}
	{
		BigInt a;
		BigInt b("987654321");
		a += b;
		std::stringstream ss;
		ss << a;
		AssertEqual(ss.str(), "987654321", "Third test");
	}
	{
		BigInt a;
		BigInt b("-987654321");
		b += a;
		std::stringstream ss;
		ss << b;
		AssertEqual(ss.str(), "-987654321", "Forth test");
	}
	{
		BigInt a;
		BigInt b("0");
		b += a;
		std::stringstream ss;
		ss << b;
		AssertEqual(ss.str(), "0", "Fifth test");
	}
	{
		BigInt a("123456789");
		BigInt b("-987654321");
		b += a;
		std::stringstream ss;
		ss << b;
		AssertEqual(ss.str(), "-864197532", "Sixth test");
	}
	{
		BigInt a("123456789");
		BigInt b("-987654321");
		a += b;
		std::stringstream ss;
		ss << a;
		AssertEqual(ss.str(), "-864197532", "Seventh test");
	}
	{
		BigInt a("-123456789");
		BigInt b("987654321");
		b += a;
		std::stringstream ss;
		ss << b;
		AssertEqual(ss.str(), "864197532", "Eighth test");
	}
	{
		BigInt a("-123456789");
		BigInt b("987654321");
		a += b;
		std::stringstream ss;
		ss << a;
		AssertEqual(ss.str(), "864197532", "Nineth test");
	}
	{
		BigInt a("123456789");
		BigInt b("-123456789");
		a += b;
		std::stringstream ss;
		ss << a;
		AssertEqual(ss.str(), "0", "Tenth test");
	}
}

void TestDifEqual() {
	{
		BigInt a("123456789");
		BigInt b("987654321");
		b -= a;
		std::stringstream ss;
		ss << b;
		AssertEqual(ss.str(), "864197532", "First test");
	}
	{
		BigInt a("123456789");
		BigInt b("987654321");
		a -= b;
		std::stringstream ss;
		ss << a;
		AssertEqual(ss.str(), "-864197532", "Second test");
	}
	{
		BigInt a("-123456789");
		BigInt b("-987654321");
		a -= b;
		std::stringstream ss;
		ss << a;
		AssertEqual(ss.str(), "864197532", "Third test");
	}
	{
		BigInt a("-123456789");
		BigInt b("-987654321");
		b -= a;
		std::stringstream ss;
		ss << b;
		AssertEqual(ss.str(), "-864197532", "Forth test");
	}
	{
		BigInt a;
		BigInt b("-987654321");
		a -= b;
		std::stringstream ss;
		ss << a;
		AssertEqual(ss.str(), "987654321", "Fifth test");
	}
	{
		BigInt a;
		BigInt b("-987654321");
		b -= a;
		std::stringstream ss;
		ss << b;
		AssertEqual(ss.str(), "-987654321", "Sixth test");
	}
	{
		BigInt a;
		BigInt b("0");
		b -= a;
		std::stringstream ss;
		ss << b;
		AssertEqual(ss.str(), "0", "Seventh test");
	}
	{
		BigInt a("123456789");
		BigInt b("-987654321");
		b -= a;
		std::stringstream ss;
		ss << b;
		AssertEqual(ss.str(), "-1111111110", "Eighth test");
	}
	{
		BigInt a("123456789");
		BigInt b("-987654321");
		a -= b;
		std::stringstream ss;
		ss << a;
		AssertEqual(ss.str(), "1111111110", "Nineth test");
	}
	{
		BigInt a("-123456789");
		BigInt b("987654321");
		b -= a;
		std::stringstream ss;
		ss << b;
		AssertEqual(ss.str(), "1111111110", "Tenth test");
	}
	{
		BigInt a("-123456789");
		BigInt b("987654321");
		a -= b;
		std::stringstream ss;
		ss << a;
		AssertEqual(ss.str(), "-1111111110", "Eleventh test");
	}
	{
		BigInt a("123456789");
		BigInt b("123456789");
		a -= b;
		std::stringstream ss;
		ss << a;
		AssertEqual(ss.str(), "0", "Twelveth test");
	}
}

void TestAbs() {
	{
		BigInt a("6323323");
		std::stringstream ss;
		ss << Abs(a);
		AssertEqual(ss.str(), "6323323", "First test");
	}
	{
		BigInt a("-6323323");
		std::stringstream ss;
		ss << Abs(a);
		AssertEqual(ss.str(), "6323323", "Second test");
	}
	{
		BigInt a("-6323323");
		std::stringstream ss;
		ss << Abs(a);
		AssertEqual(ss.str(), "6323323", "Second test");
	}
}

void TestMul() {
	{
		BigInt a;
		BigInt b;
		std::stringstream ss;
		ss << a * b;
		AssertEqual(ss.str(), "0", "First test");
	}
	{
		BigInt a("362732");
		BigInt b;
		std::stringstream ss;
		ss << a * b;
		AssertEqual(ss.str(), "0", "Second test");
	}
	{
		BigInt a("362732");
		BigInt b;
		std::stringstream ss;
		ss << b * a;
		AssertEqual(ss.str(), "0", "Third test");
	}
	{
		BigInt a("362732");
		BigInt b("2162");
		std::stringstream ss;
		ss << b * a;
		AssertEqual(ss.str(), "784226584", "Forth test");
	}
	{
		BigInt a("-362732");
		BigInt b("2162");
		std::stringstream ss;
		ss << b * a;
		AssertEqual(ss.str(), "-784226584", "Fifth test");
	}
}

void TestMulEqual() {
	{
		BigInt a;
		BigInt b;
		a *= b;
		std::stringstream ss;
		ss << a;
		AssertEqual(ss.str(), "0", "First test");
	}
	{
		BigInt a("362732");
		BigInt b;
		a *= b;
		std::stringstream ss;
		ss << a;
		AssertEqual(ss.str(), "0", "Second test");
	}
	{
		BigInt a("362732");
		BigInt b;
		b *= a;
		std::stringstream ss;
		ss << b;
		AssertEqual(ss.str(), "0", "Third test");
	}
	{
		BigInt a("362732");
		BigInt b("2162");
		b *= a;
		std::stringstream ss;
		ss << b;
		AssertEqual(ss.str(), "784226584", "Forth test");
	}
	{
		BigInt a("-362732");
		BigInt b("2162");
		b *= a;
		std::stringstream ss;
		ss << b;
		AssertEqual(ss.str(), "-784226584", "Fifth test");
	}
}

void TestDivByTwo() {
	{
		BigInt a("125612");
		std::stringstream ss;
		ss << DivByTwo(a);
		AssertEqual(ss.str(), "62806", "First test");
	}
	{
		BigInt a;
		std::stringstream ss;
		ss << DivByTwo(a);
		AssertEqual(ss.str(), "0", "Second test");
	}
	{
		BigInt a("-125612");
		std::stringstream ss;
		ss << DivByTwo(a);
		AssertEqual(ss.str(), "-62806", "Third test");
	}
	{
		BigInt a("125613");
		std::stringstream ss;
		ss << DivByTwo(a);
		AssertEqual(ss.str(), "62806", "Forth test");
	}
	{
		BigInt a("-125613");
		std::stringstream ss;
		ss << DivByTwo(a);
		AssertEqual(ss.str(), "-62806", "Fifth test");
	}
}

void TestDivMod() {
	{
		BigInt a("1234");
		BigInt b("35");
		std::tuple t = DivMod(a, b);
		BigInt div = std::get<0>(t);
		BigInt mod = std::get<1>(t);
		std::stringstream smod, sdiv;
		sdiv << div;
		smod << mod;
		AssertEqual(sdiv.str(), "35", "First div test");
		AssertEqual(smod.str(), "9", "First mod test");
	}
	{
		BigInt a("-1234");
		BigInt b("35");
		std::tuple t = DivMod(a, b);
		BigInt div = std::get<0>(t);
		BigInt mod = std::get<1>(t);
		std::stringstream smod, sdiv;
		sdiv << div;
		smod << mod;
		AssertEqual(sdiv.str(), "-35", "Second div test");
		AssertEqual(smod.str(), "-9", "Second mod test");
	}
	{
		BigInt a("-1234");
		BigInt b("-35");
		std::tuple t = DivMod(a, b);
		BigInt div = std::get<0>(t);
		BigInt mod = std::get<1>(t);
		std::stringstream smod, sdiv;
		sdiv << div;
		smod << mod;
		AssertEqual(sdiv.str(), "35", "Third div test");
		AssertEqual(smod.str(), "-9", "Third mod test");
	}
	{
		BigInt a("1234");
		BigInt b("-35");
		std::tuple t = DivMod(a, b);
		BigInt div = std::get<0>(t);
		BigInt mod = std::get<1>(t);
		std::stringstream smod, sdiv;
		sdiv << div;
		smod << mod;
		AssertEqual(sdiv.str(), "-35", "Forth div test");
		AssertEqual(smod.str(), "9", "Forth mod test");
	}
	{
		BigInt a;
		BigInt b("-35");
		std::tuple t = DivMod(a, b);
		BigInt div = std::get<0>(t);
		BigInt mod = std::get<1>(t);
		std::stringstream smod, sdiv;
		sdiv << div;
		smod << mod;
		AssertEqual(sdiv.str(), "0", "Fifth div test");
		AssertEqual(smod.str(), "0", "Fifth mod test");
	}
	{
		BigInt a("172");
		BigInt b("-356");
		std::tuple t = DivMod(a, b);
		BigInt div = std::get<0>(t);
		BigInt mod = std::get<1>(t);
		std::stringstream smod, sdiv;
		sdiv << div;
		smod << mod;
		AssertEqual(sdiv.str(), "0", "Fifth div test");
		AssertEqual(smod.str(), "172", "Fifth mod test");
	}
	{
		BigInt a("-172");
		BigInt b("-356");
		std::tuple t = DivMod(a, b);
		BigInt div = std::get<0>(t);
		BigInt mod = std::get<1>(t);
		std::stringstream smod, sdiv;
		sdiv << div;
		smod << mod;
		AssertEqual(sdiv.str(), "0", "Fifth div test");
		AssertEqual(smod.str(), "-172", "Fifth mod test");
	}
}

void TestAll() {
	TestRunner tr;
	tr.RunTest(TestOut, "TestOut");
	tr.RunTest(TestIn, "TestIn");
	tr.RunTest(TestEqual, "TestEqual");
	tr.RunTest(TestMore, "TestMore");
	tr.RunTest(TestLess, "TestLess");
	tr.RunTest(TestMoreEqual, "TestMoreEqual");
	tr.RunTest(TestLessEqual, "TestLessEqual");
	tr.RunTest(TestSum, "TestSum");
	tr.RunTest(TestDif, "TestDif");
	tr.RunTest(TestSumEqual, "TestSumEqual");
	tr.RunTest(TestDifEqual, "TestDifEqual");
	tr.RunTest(TestMul, "TestMul");
	tr.RunTest(TestMulEqual, "TestMulEqual");
	tr.RunTest(TestDivByTwo, "TestDivByTwo");
	tr.RunTest(TestDivMod, "TestDivMod");
}