#include "BigInt.h"

#include <exception>
#include <algorithm>
#include <iostream>

void changeSign(Sign& sign) {
	if (sign == Sign::PLUS) sign = Sign::MINUS;
	else if (sign == Sign::MINUS) sign = Sign::PLUS;
}


BigInt::BigInt() : details({0, 0}), sign(Sign::ZERO) { }

BigInt::BigInt(const std::string& number) {
	if (number.size() == 0) throw std::invalid_argument("Error: wrong number format\n");
	
	size_t start = 0;
	if (number[0] == '-') {
		sign = Sign::MINUS;
		start = 1;
	}
	else sign = Sign::PLUS;

	if (start == 1 && number.size() == 1) throw std::invalid_argument("Error: wrong number format\n");
	if (start == 1 && number[1] == '0') throw std::invalid_argument("Error: wrong number format\n");

	details = { 0, 0 };


	for (size_t i = start; i < number.size(); ++i) {
		char digit = number[i];
		if (digit < '0' || digit > '9') throw std::invalid_argument("Error: wrong number format\n");

		for (long long i = details[0]; i > 0; --i) {
			if (static_cast<long long>(details.size()) == i + 1) {
				details.push_back(0);
			}
			details[i + 1] += (details[i] * 10) / base;
			details[i] = (details[i] * 10) % base;
		}

		details[1] += digit - '0';

		if (details[details[0] + 1] > 0) details[0]++;
	}

	if (details[0] == 0) sign = Sign::ZERO;

	clearGarbage();
}

BigInt::BigInt(const long long& number) {
	*this = BigInt(std::to_string(number));
}

BigInt::BigInt(const BigInt& numb) : details(numb.details), sign(numb.sign) { }

std::ostream& operator <<(std::ostream& out, const BigInt& numb) {
	long long count_of_digits = std::to_string(numb.base).size() - 1;

	if (numb.sign == Sign::MINUS) out << "-";

	out << numb.details[numb.details[0]];

	for (long long i = numb.details[0] - 1; i >= 1; --i) {
		std::string s = std::to_string(numb.details[i]);

		for (long long j = s.size(); j < count_of_digits; ++j) {
			out << 0;
		}
		out << numb.details[i];
	}

	return out;
}


std::istream& operator >>(std::istream& in, BigInt& numb) {
	std::string number;
	in >> number;

	BigInt tmpNumb(number);
	numb = tmpNumb;

	return in;
}



bool operator ==(const BigInt& numb1, const BigInt& numb2) { 
	return numb1.details == numb2.details && numb1.sign == numb2.sign;
}



bool operator >(const BigInt& numb1, const BigInt& numb2) {
	if (numb1.sign != numb2.sign) return numb1.sign > numb2.sign;
	if (numb1.details[0] != numb2.details[0]) {
		if (numb1.sign == Sign::MINUS) return numb1.details[0] < numb2.details[0];
		else return numb1.details[0] > numb2.details[0];
	}

	long long i = numb1.details[0];
	while (i > 0 && numb1.details[i] == numb2.details[i]) {
		--i;
	}

	if (numb1.sign == Sign::MINUS) return numb1.details[i] < numb2.details[i];
	else return numb1.details[i] > numb2.details[i];
}

bool operator >=(const BigInt& numb1, const BigInt& numb2) {
	return numb1 > numb2 || numb1 == numb2;
}



bool operator <(const BigInt& numb1, const BigInt& numb2) {
	return numb2 > numb1;
}

bool operator <=(const BigInt& numb1, const BigInt& numb2) {
	return numb1 < numb2 || numb1 == numb2;
}


BigInt operator +(const BigInt& numb1, const BigInt& numb2) {
	BigInt tmpNumb1 = numb1, tmpNumb2 = numb2;

	if (numb1.sign == Sign::ZERO) return numb2;
	if (numb2.sign == Sign::ZERO) return numb1;

	BigInt res;

	if (numb1.sign == numb2.sign) {
		res.sign = numb1.sign;

		auto maxi = std::max(numb1.details[0], numb2.details[0]);
		for (long long i = 1; i <= maxi; ++i) {
			if (res.details.size() == static_cast<size_t>(i + 1)) {
				res.details.push_back(0);
			}
			if (res.details.size() == static_cast<size_t>(i + 1)) res.details.push_back(0);
			if (tmpNumb1.details.size() == static_cast<size_t>(i + 1)) tmpNumb1.details.push_back(0);
			if (tmpNumb2.details.size() == static_cast<size_t>(i + 1)) tmpNumb2.details.push_back(0);

			res.details[i + 1] = (res.details[i] + tmpNumb1.details[i] + tmpNumb2.details[i]) / res.base;
			res.details[i] = (res.details[i] + tmpNumb1.details[i] + tmpNumb2.details[i]) % res.base;
		}

		if (res.details[maxi + 1] == 0) res.details[0] = maxi;
		else res.details[0] = maxi + 1;
	}
	else {
		if (numb1.sign == Sign::PLUS) {
			if (Abs(numb1) > Abs(numb2)) return Abs(numb1) - Abs(numb2);
			else if (Abs(numb1) == Abs(numb2)) return BigInt();
			else {
				res = Abs(numb2) - Abs(numb1);
				res.sign = Sign::MINUS;
			}
		}
		else {
			if (Abs(numb1) < Abs(numb2)) return Abs(numb2) - Abs(numb1);
			else if (Abs(numb1) == Abs(numb2)) return BigInt();
			else {
				res = Abs(numb1) - Abs(numb2);
				res.sign = Sign::MINUS;
			}
		}
	}

	res.clearGarbage();

	return res;
}

BigInt operator -(const BigInt& numb1, const BigInt& numb2) {
	if (numb2.sign == Sign::ZERO) return numb1;
	if (numb1.sign == Sign::ZERO) {
		BigInt tmp = numb2;
		changeSign(tmp.sign);
		return tmp;
	}

	BigInt tmp = numb1;

	if (numb1.sign == numb2.sign) {
		if (Abs(numb1) > Abs(numb2)) {
			for (long long i = 1; i <= numb2.details[0]; ++i) {
				tmp.details[i] -= numb2.details[i];
				long long j = i;
				while (tmp.details[j] < 0 && (j <= tmp.details[0])) {
					tmp.details[j] += tmp.base;
					if (tmp.details.size() == static_cast<size_t>(j + 1)) tmp.details.push_back(0);
					tmp.details[j + 1]--;
					j++;
				}
			}

			long long i = tmp.details[0];
			while (i > 1 && tmp.details[i] == 0) --i;
			tmp.details[0] = i;
		}
		else if (Abs(numb1) == Abs(numb2)) tmp = BigInt();
		else {
			tmp = numb2 - numb1;
			changeSign(tmp.sign);
		}
	}
	else {
		if (numb1.sign == Sign::PLUS) return numb1 + Abs(numb2);
		else {
			tmp = numb2;
			changeSign(tmp.sign);
			tmp = numb1 + tmp;
		}
	}

	tmp.clearGarbage();
	return tmp;
}

BigInt operator *(const BigInt& numb1, const BigInt& numb2) {
	if (numb1.sign == Sign::ZERO || numb2.sign == Sign::ZERO) return BigInt();
	
	BigInt res;

	for (long long i = 0; i < numb1.details[0]; ++i) {
		for (long long j = 0; j < numb2.details[0]; ++j) {
			if (res.details.size() == static_cast<size_t>(i + j + 1)) res.details.push_back(0);
			res.details[i + j + 1] += numb1.details[i + 1] * numb2.details[j + 1];
		}
	}

	for (long long i = 0; i < numb1.details[0] + numb2.details[0]; ++i) {
		if (res.details.size() == static_cast<size_t>(i + 1)) res.details.push_back(0);
		if (res.details[i + 1] >= res.base) {
			if (res.details.size() == static_cast<size_t>(i + 2)) res.details.push_back(0);
			res.details[i + 2] += res.details[i + 1] / res.base;
			res.details[i + 1] %= res.base;
		}
	}

	res.details[0] = res.details.size() - 1;
	for (size_t i = res.details.size() - 1; i > 0 && res.details[i] == 0; --i) {
		res.details[0]--;
	}

	if (numb1.sign == numb2.sign) res.sign = Sign::PLUS;
	else res.sign = Sign::MINUS;

	res.clearGarbage();

	return res;
}

BigInt operator /(const BigInt& numb1, const BigInt& numb2) {
	std::tuple<BigInt, BigInt> t = DivMod(numb1, numb2);
	return std::get<0>(t);
}

BigInt operator %(const BigInt& numb1, const BigInt& numb2) {
	std::tuple<BigInt, BigInt> t = DivMod(numb1, numb2);
	return std::get<1>(t);
}



BigInt Abs(const BigInt& numb) {
	BigInt newNumb = numb;

	if (numb.details[0] == 0) newNumb.sign = Sign::ZERO;
	else newNumb.sign = Sign::PLUS;

	return newNumb;
}



void BigInt::operator =(const BigInt& numb) { 
	details = numb.details;
	sign = numb.sign;
}

void BigInt::operator +=(const BigInt& numb) {
	*this = *this + numb;
}

void BigInt::operator -=(const BigInt& numb) {
	*this = *this - numb;
}

void BigInt::operator *=(const BigInt& numb) {
	*this = *this * numb;
}

void BigInt::operator /=(const BigInt& numb) {
	*this = *this / numb;
}

void BigInt::operator %=(const BigInt& numb) {
	*this = *this % numb;
}


std::tuple<BigInt, BigInt> DivMod(const BigInt& numb1, const BigInt& numb2) {
	if (numb2 == BigInt()) throw std::runtime_error("Error: division by zero\n");
	if (numb1 == BigInt()) return std::make_tuple(BigInt(), BigInt());
	if (Abs(numb1) < Abs(numb2)) return std::make_tuple(BigInt(), numb1);
	
	BigInt left, right = Abs(numb1) + BigInt("1"), mid;

	while (right - left > BigInt("1")) {
		mid = DivByTwo(left + right);

		if (Abs(numb2) * mid <= Abs(numb1)) left = mid;
		else right = mid;
	}

	BigInt div = left;
	if (div == BigInt()) div.sign = Sign::ZERO;
	else if (numb1.sign == numb2.sign) div.sign = Sign::PLUS;
	else div.sign = Sign::MINUS;

	BigInt mod = Abs(numb1) - left * Abs(numb2);
	if (mod == BigInt()) mod.sign = Sign::ZERO;
	else if (numb1.sign == Sign::PLUS) mod.sign = Sign::PLUS;
	else mod.sign = Sign::MINUS;

	div.clearGarbage();
	mod.clearGarbage();

	return std::make_tuple(div, mod);
}

BigInt DivByTwo(const BigInt& numb) {
	BigInt res = numb;
	long long carry = 0;
	for (long long i = res.details[0]; i > 0; --i) {
		long long cur = numb.details[i] + carry * numb.base;
		res.details[i] = (long long)cur / 2;
		carry = (long long)cur % 2;
	}
	
	res.details[0] = res.details.size() - 1;
	for (size_t i = res.details.size() - 1; i > 0 && res.details[i] == 0; --i) {
		res.details[0]--;
	}

	if (res.details[0] == 0) res.sign = Sign::ZERO;
	else res.sign = numb.sign;

	res.clearGarbage();
	return res;
}

void BigInt::clearGarbage() {
	if (details[0] > 0) {
		size_t count = details.size() - details[0] - 1;
		for (size_t i = 0; i < count; ++i) {
			details.pop_back();
		}
	}
}