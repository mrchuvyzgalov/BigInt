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

		for (int i = details[0]; i > 0; --i) {
			if (details.size() == i + 1) {
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


BigInt::BigInt(const BigInt& numb) : details(numb.details), sign(numb.sign) { }



std::ostream& operator <<(std::ostream& out, const BigInt& numb) {
	int count_of_digits = std::to_string(numb.base).size() - 1;

	if (numb.sign == Sign::MINUS) out << "-";

	out << numb.details[numb.details[0]];

	for (int i = numb.details[0] - 1; i >= 1; --i) {
		std::string s = std::to_string(numb.details[i]);

		for (int j = s.size(); j < count_of_digits; ++j) {
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

	int i = numb1.details[0];
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
	if (numb1.sign == Sign::ZERO) return numb2;
	if (numb2.sign == Sign::ZERO) return numb1;

	BigInt res;

	if (numb1.sign == numb2.sign) {
		res.sign = numb1.sign;

		int maxi = std::max(numb1.details[0], numb2.details[0]);
		for (int i = 1; i <= maxi; ++i) {
			if (res.details.size() == i + 1) {
				res.details.push_back(0);
			}
			if (res.details.size() == i + 1) res.details.push_back(0);

			res.details[i + 1] = (res.details[i] + numb1.details[i] + numb2.details[i]) / res.base;
			res.details[i] = (res.details[i] + numb1.details[i] + numb2.details[i]) % res.base;
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
			for (int i = 1; i <= numb2.details[0]; ++i) {
				tmp.details[i] -= numb2.details[i];
				int j = i;
				while (tmp.details[j] < 0 && (j <= tmp.details[0])) {
					tmp.details[j] += tmp.base;
					if (tmp.details.size() == j + 1) tmp.details.push_back(0);
					tmp.details[j + 1]--;
					j++;
				}
			}

			int i = tmp.details[0];
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

	for (int i = 0; i < numb1.details[0]; ++i) {
		for (int j = 0; j < numb2.details[0]; ++j) {
			if (res.details.size() == i + j + 1) res.details.push_back(0);
			res.details[i + j + 1] += numb1.details[i + 1] * numb2.details[j + 1];
		}
	}

	for (int i = 0; i < numb1.details[0] + numb2.details[0]; ++i) {
		if (res.details.size() == i + 1) res.details.push_back(0);
		if (res.details[i + 1] >= res.base) {
			if (res.details.size() == i + 2) res.details.push_back(0);
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

void BigInt::clearGarbage() {
	if (details[0] > 0) {
		size_t count = details.size() - details[0] - 1;
		for (size_t i = 0; i < count; ++i) {
			details.pop_back();
		}
	}
}