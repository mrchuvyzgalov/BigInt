#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <tuple>

enum class Sign { MINUS, ZERO, PLUS };

void changeSign(Sign& sign);

class BigInt {
public:
	explicit BigInt();
	explicit BigInt(const std::string& number);
	explicit BigInt(const long long& number);
	
	BigInt(const BigInt& numb);

	friend std::ostream& operator <<(std::ostream& out, const BigInt& numb);
	friend std::istream& operator >>(std::istream& in, BigInt& numb);

	friend bool operator ==(const BigInt& numb1, const BigInt& numb2);

	friend bool operator >(const BigInt& numb1, const BigInt& numb2);
	friend bool operator >=(const BigInt& numb1, const BigInt& numb2);

	friend bool operator <(const BigInt& numb1, const BigInt& numb2);
	friend bool operator <=(const BigInt& numb1, const BigInt& numb2);

	friend BigInt operator +(const BigInt& numb1, const BigInt& numb2);
	friend BigInt operator -(const BigInt& numb1, const BigInt& numb2);
	friend BigInt operator *(const BigInt& numb1, const BigInt& numb2);
	friend BigInt operator /(const BigInt& numb1, const BigInt& numb2);
	friend BigInt operator %(const BigInt& numb1, const BigInt& numb2);

	friend std::tuple<BigInt, BigInt> DivMod(const BigInt& numb1, const BigInt& numb2);
	friend BigInt DivByTwo(const BigInt& numb);

	friend BigInt Abs(const BigInt& numb);


	void operator =(const BigInt& numb);
	void operator +=(const BigInt& numb);
	void operator -=(const BigInt& numb);
	void operator *=(const BigInt& numb);
	void operator /=(const BigInt& numb);
	void operator %=(const BigInt& numb);

private:
	void clearGarbage();

private:
	std::vector<long long> details;
	Sign sign;
	const long long base = 1e10;
};