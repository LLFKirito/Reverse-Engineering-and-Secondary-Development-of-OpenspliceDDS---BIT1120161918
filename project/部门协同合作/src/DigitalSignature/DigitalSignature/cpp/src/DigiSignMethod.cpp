
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
  * LOGICAL_NAME:    DigiSignMethod.cpp
  * DATE:            November 2018.
  *****************************************************************************/


#include <iostream>
#include <cassert>
#include "DigiSignMethod.h"


template<typename T>
inline T shift(T x, int n)
{
	return (((x) << (n)) | ((x) >> (32 - (n))));
}

template<typename T>
inline T F(T x, T y, T z)
{
	return (((x) & (y)) | ((~x) & (z)));
}

template<typename T>
inline T G(T x, T y, T z)
{
	return (((x) & (z)) | ((y) & (~z)));
}

template<typename T>
inline T H(T x, T y, T z)
{
	return ((x) ^ (y) ^ (z));
}

template<typename T>
inline T I(T x, T y, T z)
{
	return ((y) ^ ((x) | (~z)));
}

//  常量ki unsigned int(abs(sin(i+1))*(2pow32))
const unsigned int k[] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

//  向左位移数
const unsigned int s[] = {
	 7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
	 5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
	 4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
	 6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21
};

const char str16[] = "0123456789abcdef";

//  strBaye的长度
unsigned int strlength;

//  A,B,C,D的临时变量
unsigned int atemp;
unsigned int btemp;
unsigned int ctemp;
unsigned int dtemp;

void mainLoop(unsigned int M[])
{
	unsigned int f, g;
	unsigned int a = atemp;
	unsigned int b = btemp;
	unsigned int c = ctemp;
	unsigned int d = dtemp;
	for (unsigned int i = 0; i < 64; i++)
	{
		if (i < 16) {
			f = F(b, c, d);
			g = i;
		}
		else if (i < 32)
		{
			f = G(b, c, d);
			g = (5 * i + 1) % 16;
		}
		else if (i < 48) {
			f = H(b, c, d);
			g = (3 * i + 5) % 16;
		}
		else {
			f = I(b, c, d);
			g = (7 * i) % 16;
		}
		unsigned int tmp = d;
		d = c;
		c = b;
		b = b + shift((a + f + k[i] + M[g]), s[i]);
		a = tmp;
	}
	atemp = a + atemp;
	btemp = b + btemp;
	ctemp = c + ctemp;
	dtemp = d + dtemp;
}

unsigned int* add(std::string str)
{
	unsigned int num = ((str.length() + 8) / 64) + 1;
	unsigned int *strByte = new unsigned int[num * 16];
	strlength = num * 16;
	for (unsigned int i = 0; i < num * 16; i++)
		strByte[i] = 0;
	for (unsigned int i = 0; i < str.length(); i++)
	{
		strByte[i >> 2] |= (str[i]) << ((i % 4) * 8);
	}
	strByte[str.length() >> 2] |= 0x80 << (((str.length() % 4)) * 8);
	strByte[num * 16 - 2] = str.length() * 8;
	return strByte;
}

inline unsigned encode(char c)
{
	if (isdigit(c)) return c - '0';
	else return c - 'a' + 10;
}

std::string changeHex(int a)
{
	int b;
	std::string str1;
	std::string str = "";
	for (int i = 0; i < 4; i++)
	{
		str1 = "";
		b = ((a >> i * 8) % (1 << 8)) & 0xff;
		for (int j = 0; j < 2; j++)
		{
			str1.insert(0, 1, str16[b % 16]);
			b = b / 16;
		}
		str += str1;
	}
	return str;
}

uint64_t qmul(uint64_t x, uint64_t y, uint64_t mod)
{
	uint64_t ret = 0;
	while (y)
	{
		if (y & 1) ret = (ret + x) % mod;
		x = (x + x) % mod;
		y >>= 1;
	}
	return ret;
}

uint64_t qpow(uint64_t base, uint64_t index, uint64_t mod)
{
	uint64_t ret = 1;
	while (index)
	{
		if (index & 1) ret = qmul(ret, base, mod);
		base = qmul(base, base, mod);
		index >>= 1;
	}
	return ret;
}


void Hash::set(const char *s)
{
	assert(strlen(s) == 32);
	high = low = 0;
	for (int i = 0; i < 16; i++)
		high = high << 4 | encode(s[i]);
	for (int i = 16; i < 32; i++)
		low = low << 4 | encode(s[i]);
}

void Hash::set(std::string s) {
	set(s.data());
}

void Hash::getMD5(std::string source)
{
	atemp = 0x67452301;
	btemp = 0xefcdab89;
	ctemp = 0x98badcfe;
	dtemp = 0x10325476;
	unsigned int *strByte = add(source);
	for (unsigned int i = 0; i < strlength / 16; i++)
	{
		unsigned int num[16];
		for (unsigned int j = 0; j < 16; j++)
			num[j] = strByte[i * 16 + j];
		mainLoop(num);
	}
	set(changeHex(atemp).append(changeHex(btemp)).append(changeHex(ctemp)).append(changeHex(dtemp)));
}

void Hash::RSAdecode(Sign sign) {
	uint64_t e = 19980227;
	uint64_t mod = 23548457663347;
	uint64_t aa = qpow(sign.value[0], e, mod);
	uint64_t bb = qpow(sign.value[1], e, mod);
	uint64_t cc = qpow(sign.value[2], e, mod);
	uint64_t dd = qpow(sign.value[3], e, mod);
	high = (aa << 32) | bb;
	low = (cc << 32) | dd;
}


void Sign::RSAcode(Hash digest) {
	uint64_t e = 17216552165547;
	uint64_t mod = 23548457663347;
	value[0] = qpow(digest.high >> 32, e, mod);
	value[1] = qpow(digest.high & 0xffffffffull, e, mod);
	value[2] = qpow(digest.low >> 32, e, mod);
	value[3] = qpow(digest.low & 0xffffffffull, e, mod);
}

