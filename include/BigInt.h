#pragma once

#include <vector>
#include <string>
#include <sstream>

enum class Sign { MINUS, ZERO, PLUS };

void changeSign(Sign& sign);

class BigInt {
public:
	explicit BigInt();
	explicit BigInt(const std::string& number);
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

	friend BigInt Abs(const BigInt& numb);


	void operator =(const BigInt& numb);
	void operator +=(const BigInt& numb);
	void operator -=(const BigInt& numb);
	void operator *=(const BigInt& numb);

private:
	void clearGarbage();

private:
	Sign sign;
	std::vector<int> details;
	const int base = 1e1;
};