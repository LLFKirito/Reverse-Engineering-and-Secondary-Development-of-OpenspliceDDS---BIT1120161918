
/*
 *                             Digital Signature
 *
 *    This software and documentation are Copyright 2018 to Fengfeng Software
 *    Studio Limited, its affiliated companies and licensors. All rights
 *    reserved. You may not use this file except in compliance with the License.
 *
 *    Team Members: Linfeng Li, Bole Ma, Yunhan Shen, Nan Shang, Xiaohu Chen
 *
 */

 /*****************************************************************************
  * LOGICAL_NAME:    NumDecomposeMethod.cpp
  * DATE:            November 2018.
  *****************************************************************************/


#pragma warning(disable:4996)
#include <ctime>
#include <vector>
#include <sys/timeb.h>
#include "NumDecomposeMethod.h"


inline uint64_t fastMul(uint64_t x, uint64_t y, uint64_t mod)
{
	uint64_t ret = 0;
	while (y) {
		if (y & 1)
			ret = (ret + x) % mod;
		x = x * 2 % mod;
		y >>= 1;
	}
	return ret;
}

uint64_t fastPower(uint64_t a, uint64_t n, uint64_t mod)
{
	uint64_t ret = 1;
	while (n)
	{
		if (n & 1)
			ret = fastMul(ret, a, mod);
		a = fastMul(a, a, mod);
		n >>= 1;
	}
	return ret;
}

bool primeMillerRabbin(uint64_t x)
{
	if (x == 1) return false;
	if (x == 2) return true;
	for (int i = 1; i <= 20; i++)
	{
		uint64_t a = rand() % (x - 2) + 2;
		if (fastPower(a, x - 1, x) != 1)
			return false;
	}
	return true;
}

uint64_t gcd(uint64_t a, uint64_t b)
{
	return b ? gcd(b, a % b) : a;
}

uint64_t pollardRho(uint64_t x, uint64_t c)
{
	uint64_t i = 1, k = 2, x0 = rand() % x, y = x0;
	while (true)
	{
		i++;
		x0 = (fastMul(x0, x0, x) + c) % x;
		uint64_t d = gcd(y - x0, x);
		if (d != 1 && d != x) return d;
		if (y == x0) return x;
		if (i == k) y = x0, k *= 2;
	}
	return 0;
}

void getFactor(uint64_t n, std::vector<uint64_t>& fac)
{
	if (n == 1) return;
	if (primeMillerRabbin(n))
	{
		fac.push_back(n);
		return;
	}
	uint64_t p = n;
	while (p >= n)
		p = pollardRho(p, rand() % (n - 1) + 1);
	getFactor(n / p, fac);
	getFactor(p, fac);
}


Decompose::Decompose() :
	value(0), exception_flag(false)
{
	memset(factor, 0, sizeof factor);
}

Decompose::Decompose(uint64_t value) :
	value(value), exception_flag(false)
{
	memset(factor, 0, sizeof factor);
}

Decompose::~Decompose()
{

}

void Decompose::setValue(uint64_t value)
{
	this->value = value;
	factor[0] = factor[1] = 0;
	exception_flag = false;
}

void Decompose::decomposeNum()
{
	std::vector<uint64_t> fac;
	getFactor(value, fac);
	if (fac.size() < 2)
	{
		exception_flag = true;
		return;
	}
	factor[0] = fac[0];
	factor[1] = value / fac[0];
}


std::string getTime()
{
	time_t t;
	time(&t);
	static char buffer[1 << 6];
	strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&t));
	return buffer;
}

std::string makeDataTable(NumSent numSent)
{
	static char buffer[1 << 6];
	std::string ret;

	ret += "©°¡ª¡ª¡ª¡ª¡ª¡ª©Ð¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª©´\n";
	sprintf(buffer, "£ü   Sender  £ü      %-20llu           £ü\n", numSent.senderID);
	ret += buffer;
	ret += "©À¡ª¡ª¡ª¡ª¡ª¡ª©à¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª©È\n";
	sprintf(buffer, "£ü  Receiver £ü      %-20llu           £ü\n", numSent.addressesID);
	ret += buffer;
	ret += "©À¡ª¡ª¡ª¡ª¡ª¡ª©à¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª©È\n";
	std::string t = getTime();
	sprintf(buffer, "£ü    Time   £ü      %-20s           £ü\n", t.data());
	ret += buffer;
	ret += "©À¡ª¡ª¡ª¡ª¡ª¡ª©Ø¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª©È\n";
	sprintf(buffer, "£ü                     Content                      £ü\n");
	ret += buffer;
	ret += "©À¡ª¡ª¡ª¡ª¡ª¡ª¡ª-¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª©È\n";
	for (int i = 0; i < 50; i++)
	{
		auto& dec = numSent.num[i];
		if (numSent.senderID == 1) {
			if (dec.valid_data == false)
				break;
			else
				sprintf(buffer, "£ü               %-20llu               £ü\n", dec.large_num);
		}
		else {
			if (dec.valid_data == false)
				break;
			else if (dec.exception_flag == true)
				sprintf(buffer, "£ü     %20d th number is invaild!     £ü\n", i + 1);
			else
				sprintf(buffer, "£ü  %20llu = %10llu * %-10llu  £ü\n", dec.large_num, dec.factor[0], dec.factor[1]);
		}
		ret += buffer;
	}
	ret += "©¸¡ª¡ª¡ª¡ª¡ª¡ª¡ª-¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª©¼\n";

	return ret;
}

