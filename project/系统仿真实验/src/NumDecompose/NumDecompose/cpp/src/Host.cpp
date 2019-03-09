
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
  * LOGICAL_NAME:    Host.cpp
  * DATE:            November 2018.
  *****************************************************************************
  *
  * This file contains the implementation for host processing flow.
  *
  ***/

#pragma warning(disable:4996)
#include <string>
#include <sstream>
#include <iostream>
#include "DDSEntityManager.h"
#include "..\standalone\ccpp_NumDecomposeData.h"
#include "vortex_os.h"

using namespace DDS;
using namespace NumDecomposeData;

#define HOSTID       1
#define NODE_LOAD    50
#define MAX_MSG_LEN  256
#define DATA_MSG     0
#define OTHER_MSG    1
#define JOIN         "join"
#define END          "end"
#define FILTER       true
#define NO_FILTER    false

void distributeTask(NumSentDataWriter_var &NumSentDataWriter, DDS::ULongLong userID, DDS::ULong &total, DDS::Boolean &eof)
{
	DDS::ULong j = 0;
	NumSent numSentInstance;
	numSentInstance.addressesID = userID;
	numSentInstance.senderID = HOSTID;
	numSentInstance.mode = DATA_MSG;
	while (~scanf("%llu", &numSentInstance.num[j].large_num)) {
		numSentInstance.num[j].valid_data = true;
		total++;
		j++;
		if (j == NODE_LOAD)
			break;
	}
	for (; j < NODE_LOAD; j++) {
		numSentInstance.num[j].valid_data = false;
		eof = true;
	}
	ReturnCode_t status = NumSentDataWriter->write(numSentInstance, DDS::HANDLE_NIL);
	checkStatus(status, "NumSentDataWriter::write");
}

void disConnect(NumSentDataWriter_var &NumSentDataWriter, DDS::ULongLong userID)
{
	NumSent numSentInstance;
	numSentInstance.addressesID = userID;
	numSentInstance.senderID = HOSTID;
	numSentInstance.mode = OTHER_MSG;
	numSentInstance.message = END;
	ReturnCode_t status = NumSentDataWriter->write(numSentInstance, DDS::HANDLE_NIL);
	checkStatus(status, "NumSentDataWriter::write");
}

int Host(int argc, char *argv[])
{
	DDSEntityManager mgr;

	mgr.createParticipant("NumDecompose");
	NumSentTypeSupport_var type = new NumSentTypeSupport();
	mgr.registerType(type.in());
	mgr.createTopic("NumberDecompose");
	char buf[MAX_MSG_LEN];
	snprintf(buf, MAX_MSG_LEN, "addressesID = %llu", HOSTID);
	mgr.createSubscriptionFilter(buf, "NumberTopic");
	mgr.createPublisher();
	mgr.createSubscriber();
	mgr.createWriter();
	mgr.createReader(FILTER);

	DataWriter_var dwriter = mgr.getWriter();
	NumSentDataWriter_var NumSentWriter = NumSentDataWriter::_narrow(dwriter.in());
	checkHandle(NumSentWriter.in(), "NumSentWriter::_narrow");
	DataReader_var dreader = mgr.getReader();
	NumSentDataReader_var NumSentReader = NumSentDataReader::_narrow(dreader.in());
	checkHandle(NumSentReader.in(), "NumSentReader::_narrow");

	cout << "Host started successfully, waiting for the node to connect." << endl;

	NumSentSeq numSentList;
	SampleInfoSeq infoSeq;
	ReturnCode_t status = -1;
	os_time delay_100ms = { 0, 100000000 };
	os_time delay_200ms = { 0, 200000000 };
	DDS::ULong total = 0, reTotal = 0;
	DDS::Boolean eof = false;
	while (!eof || reTotal < total) {
		status = NumSentReader->take(numSentList, infoSeq, LENGTH_UNLIMITED,
			ANY_SAMPLE_STATE, ANY_VIEW_STATE, ANY_INSTANCE_STATE);
		checkStatus(status, "NumSentReader::take");
		for (DDS::ULong j = 0; j < numSentList.length(); j++) {
			if (numSentList[j].mode == OTHER_MSG) {
				if (strcmp(numSentList[j].message.in(), JOIN) == 0) {
					cout << "Register for Node ID = " << numSentList[j].senderID << endl;
					if (!eof) {
						distributeTask(NumSentWriter, numSentList[j].senderID, total, eof);
						cout << "Distribute task to Node ID = " << numSentList[j].senderID << endl;
						os_nanoSleep(delay_100ms);
					}
				}
			}
			else if (numSentList[j].mode == DATA_MSG) {
				cout << "Receive results from Node ID = " << numSentList[j].senderID << endl;
				for (DDS::ULong k = 0; k < NODE_LOAD; k++) {
					if (numSentList[j].num[k].valid_data == false)
						break;
					if (numSentList[j].num[k].exception_flag == false)
						cout << numSentList[j].num[k].factor[0] << " " << numSentList[j].num[k].factor[1] << endl;
					else if (numSentList[j].num[k].exception_flag == true)
						cout << k << "th number is error!" << endl;
					reTotal++;
				}
				if (!eof) {
					distributeTask(NumSentWriter, numSentList[j].senderID, total, eof);
					cout << "Distribute task to Node ID = " << numSentList[j].senderID << endl;
					os_nanoSleep(delay_100ms);
				}
				else {
					disConnect(NumSentWriter, numSentList[j].senderID);
					cout << "Disconnect from Node ID = " << numSentList[j].senderID << endl;
					os_nanoSleep(delay_100ms);
				}
			}
		}
		status = NumSentReader->return_loan(numSentList, infoSeq);
		checkStatus(status, "NumSentReader::return_loan");
		os_nanoSleep(delay_200ms);
	}

	mgr.deleteWriter(NumSentWriter.in());
	mgr.deleteReader(NumSentReader.in());
	mgr.deleteFilteredTopic();
	mgr.deleteTopic();
	mgr.deletePublisher();
	mgr.deleteSubscriber();
	mgr.deleteParticipant();

	cout << "End of calculation, Host shutdown." << endl;

	system("pause");
	return 0;
}

int main(int argc, char *argv[])
{
	freopen("InputData.txt", "r", stdin);
	return Host(argc, argv);
}
