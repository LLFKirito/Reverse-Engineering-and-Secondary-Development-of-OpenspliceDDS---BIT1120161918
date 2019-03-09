
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
  * LOGICAL_NAME:    CheckStatus.h
  * FUNCTION:        Check status of information.
  * DATE:            November 2018.
  *****************************************************************************
  *
  * This file contains the headers for the error handling operations.
  *
  ***/


#ifndef __CHECKSTATUS_H__
  #define __CHECKSTATUS_H__

  #include "ccpp_dds_dcps.h"
  #include <iostream>

  using namespace std;

  /**
   * Returns the name of an error code.
   **/
  string getErrorName(DDS::ReturnCode_t status);

  /**
   * Check the return status for errors. If there is an error, then terminate.
   **/
  void checkStatus(DDS::ReturnCode_t status, const char *info);

  /**
   * Check whether a valid handle has been returned. If not, then terminate.
   **/
  void checkHandle(void *handle, string info);

#endif
