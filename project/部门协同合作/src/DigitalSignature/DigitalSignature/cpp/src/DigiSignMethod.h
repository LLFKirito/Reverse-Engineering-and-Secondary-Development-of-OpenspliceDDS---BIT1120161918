
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
  * LOGICAL_NAME:    DigiSignMethod.h
  * DATE:            November 2018.
  *****************************************************************************/


#include <string>
#include <cstdint>


class Sign;

class Hash
{
public:
	Hash() {}
	Hash(uint64_t high, uint64_t low) : high(high), low(low) {}
	Hash(const char* s) { set(s); }
	Hash(std::string s) { set(s.data()); }

	void set(const char *s);
	void set(std::string s);
	void getMD5(std::string source);
	void RSAdecode(Sign sign);

public:
	uint64_t high, low;
};


class Sign {
public:
	Sign() {}
	Sign(uint64_t a, uint64_t b, uint64_t c, uint64_t d)
	{
		value[0] = a, value[1] = b, value[2] = c, value[3] = d;
	}

	void RSAcode(Hash digest);

public:
	uint64_t value[4];
};
