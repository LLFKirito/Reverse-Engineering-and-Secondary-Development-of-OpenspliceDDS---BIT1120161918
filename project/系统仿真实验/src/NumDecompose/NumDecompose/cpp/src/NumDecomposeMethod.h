
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
  * LOGICAL_NAME:    NumDecomposeMethod.h
  * DATE:            November 2018.
  *****************************************************************************/


#ifndef __NUMDECOMPOSEMETHOD_H__
#define __NUMDECOMPOSEMETHOD_H__

#include <cstdint>
#include <cstring>
#include "..\standalone\ccpp_NumDecomposeData.h"

using namespace NumDecomposeData;


class Decompose
{
public:
	Decompose();
	Decompose(uint64_t);

	void setValue(uint64_t);
	void decomposeNum();

	virtual ~Decompose();

public:
	uint64_t value;
	uint64_t factor[2];
	bool exception_flag;
};

std::string makeDataTable(NumSent);

#endif
