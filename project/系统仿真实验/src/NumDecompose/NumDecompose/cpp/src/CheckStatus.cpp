
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
  * LOGICAL_NAME:    CheckStatus.cpp
  * FUNCTION:        Check status of information.
  * DATE:            November 2018.
  *****************************************************************************
  *
  * This file contains the implementation for the error handling operations.
  *
  ***/


#include "CheckStatus.h"

  /* Array to hold the names for all ReturnCodes. */
string RetCodeName[13] =
{
	"DDS_RETCODE_OK",
	"DDS_RETCODE_ERROR",
	"DDS_RETCODE_UNSUPPORTED",
	"DDS_RETCODE_BAD_PARAMETER",
	"DDS_RETCODE_PRECONDITION_NOT_MET",
	"DDS_RETCODE_OUT_OF_RESOURCES",
	"DDS_RETCODE_NOT_ENABLED",
	"DDS_RETCODE_IMMUTABLE_POLICY",
	"DDS_RETCODE_INCONSISTENT_POLICY",
	"DDS_RETCODE_ALREADY_DELETED",
	"DDS_RETCODE_TIMEOUT",
	"DDS_RETCODE_NO_DATA",
	"DDS_RETCODE_ILLEGAL_OPERATION"
};

/**
 * Returns the name of an error code.
 **/
string getErrorName(DDS::ReturnCode_t status)
{
	return RetCodeName[status];
}

/**
 * Check the return status for errors. If there is an error, then terminate.
 **/
void checkStatus(DDS::ReturnCode_t status, const char *info)
{
	if (status != DDS::RETCODE_OK && status != DDS::RETCODE_NO_DATA)
	{
		cerr << "Error in " << info << ": " << getErrorName(status).c_str() << endl;
		exit(1);
	}
}

/**
 * Check whether a valid handle has been returned. If not, then terminate.
 **/
void checkHandle(void *handle, string info)
{
	if (!handle)
	{
		cerr << "Error in " << info.c_str() << ": Creation failed: invalid handle" << endl;
		exit(1);
	}
}
