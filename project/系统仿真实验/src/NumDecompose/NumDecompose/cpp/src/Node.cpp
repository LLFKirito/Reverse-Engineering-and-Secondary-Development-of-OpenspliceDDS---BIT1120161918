
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
  * LOGICAL_NAME:    Node.cpp
  * DATE:            November 2018.
  *****************************************************************************/


#include <string>
#include <sstream>
#include <iostream>
#include <ctime>
#include <sys/timeb.h>
#include "NumDecomposeMethod.h"
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

uint64_t createID()
{
	uint64_t id_num = 0;
	time_t cur_t_s = time(NULL);
	struct timeb cur_t_m;
	ftime(&cur_t_m);
	id_num = (((uint64_t)cur_t_s) << 10) | (cur_t_m.millitm);
	return id_num;
}

int Node(int argc, char *argv[])
{
	DDSEntityManager mgr;
	const DDS::ULongLong NODEID = createID();

	mgr.createParticipant("NumDecompose");
	NumSentTypeSupport_var type = new NumSentTypeSupport();
	mgr.registerType(type.in());
	mgr.createTopic("NumberDecompose");
	char buf[MAX_MSG_LEN];
	snprintf(buf, MAX_MSG_LEN, "addressesID = %llu", NODEID);
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

	cout << "Node ID = " << NODEID << " started successfully." << endl;

	NumSent reqInstance;
	reqInstance.addressesID = HOSTID;
	reqInstance.senderID = NODEID;
	reqInstance.mode = OTHER_MSG;
	reqInstance.message = JOIN;
	ReturnCode_t status = NumSentWriter->write(reqInstance, DDS::HANDLE_NIL);
	checkStatus(status, "NumSentDataWriter::write");
	cout << "Connecting to the Host...." << endl;

	NumSentSeq numSentList;
	SampleInfoSeq infoSeq;
	os_time delay_100ms = { 0, 100000000 };
	os_time delay_200ms = { 0, 200000000 };
	DDS::Boolean endNode = false;
	while (!endNode) {
		status = NumSentReader->take(numSentList, infoSeq, LENGTH_UNLIMITED,
			ANY_SAMPLE_STATE, ANY_VIEW_STATE, ANY_INSTANCE_STATE);
		checkStatus(status, "NumSentReader::take");
		for (DDS::ULong j = 0; j < numSentList.length(); j++) {
			NumSent numSentInstance;
			cout << "Receive tasks from Host." << endl;
			if (numSentList[j].mode == OTHER_MSG) {
				endNode = true;
				break;
			}
			numSentInstance.addressesID = HOSTID;
			numSentInstance.senderID = NODEID;
			numSentInstance.mode = DATA_MSG;
			for (DDS::ULong k = 0; k < NODE_LOAD; k++) {
				if (numSentList[j].num[k].valid_data == false) {
					numSentInstance.num[k].valid_data = false;
					numSentInstance.num[k].exception_flag = true;
					continue;
				}
				else
					numSentInstance.num[k].valid_data = true;
				Decompose decompose;
				decompose.setValue(numSentList[j].num[k].large_num);
				decompose.decomposeNum();
				if (decompose.exception_flag)
					numSentInstance.num[k].exception_flag = true;
				else {
					numSentInstance.num[k].exception_flag = false;
					numSentInstance.num[k].large_num = numSentList[j].num[k].large_num;
					numSentInstance.num[k].factor[0] = decompose.factor[0];
					numSentInstance.num[k].factor[1] = decompose.factor[1];
				}
			}
			ReturnCode_t status = NumSentWriter->write(numSentInstance, DDS::HANDLE_NIL);
			checkStatus(status, "NumSentDataWriter::write");
			cout << "Send results to Host." << endl;
			os_nanoSleep(delay_100ms);
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

	cout << "End of calculation, Node ID = " << NODEID << " shutdown." << endl;

	return 0;
}

int main(int argc, char *argv[])
{
	return Node(argc, argv);
}
