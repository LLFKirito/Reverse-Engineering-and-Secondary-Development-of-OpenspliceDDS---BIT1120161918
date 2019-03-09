
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
  * LOGICAL_NAME:    MonitorListener.cpp
  * DATE:            November 2018.
  *****************************************************************************/


#pragma warning(disable:4996)
#include "ListenerDataListener.h"
#include <sstream>
#include <Windows.h>

using namespace DDS;
using namespace NumDecomposeData;

#define HOSTID       1
#define NODE_LOAD    50
#define INVAILD      true
#define VAILD        false
#define DATA_MSG     0
#define OTHER_MSG    1
#define JOIN         "join"
#define END          "end"

void ListenerDataListener::on_data_available(DDS::DataReader_ptr reader)
THROW_ORB_EXCEPTIONS
{
	static DDS::ULong linkNode = 0;
	static DDS::ULong dealMessage = 0;
	DDS::ReturnCode_t status;
	NumSentSeq msgList;
	SampleInfoSeq infoSeq;
	NumSent msgInstance;
	string output;
	char buffer[1 << 6];

	status = m_MsgReader->take(msgList, infoSeq, LENGTH_UNLIMITED,
		ANY_SAMPLE_STATE, ANY_VIEW_STATE, ANY_INSTANCE_STATE);
	checkStatus(status, "MsgDataReader::read");
	for (DDS::ULong j = 0; j < msgList.length(); j++) {
		if (msgList[j].senderID == 0)
			continue;
		if (msgList[j].mode == OTHER_MSG) {
			if (strcmp(msgList[j].message.in(), JOIN) == 0)
				linkNode++;
			else if (strcmp(msgList[j].message.in(), END) == 0)
				linkNode--;
			sprintf(buffer, "  No. of Online Node: %d\n", linkNode);
			cout << buffer << endl;
		}
		else if (msgList[j].mode == DATA_MSG) {
			if(msgList[j].addressesID==HOSTID)
				for (DDS::ULong k = 0; k < NODE_LOAD; k++) {
					if (msgList[j].num[k].valid_data == true && msgList[j].num[k].exception_flag == false)
						dealMessage++;
				}
			sprintf(buffer, "  Amount of Processed Data: %d\n", dealMessage);
			cout << buffer << endl;
			cout << "  Details of Nodes:\n" << endl;
			output = makeDataTable(msgList[j]);
			cout << output << endl;
		}
	}
	status = m_MsgReader->return_loan(msgList, infoSeq);
	checkStatus(status, "MsgDataReader::return_loan");
};

void ListenerDataListener::on_requested_deadline_missed(DDS::DataReader_ptr
	reader, const DDS::RequestedDeadlineMissedStatus &status)THROW_ORB_EXCEPTIONS
{
	printf("\n=== [ListenerDataListener::on_requested_deadline_missed] : triggered\n");
	printf("\n=== [ListenerDataListener::on_requested_deadline_missed] : stopping\n");
	m_closed = true;
	// unblock the waitset in Subscriber main loop
	m_guardCond->set_trigger_value(true);
};

void ListenerDataListener::on_requested_incompatible_qos(DDS::DataReader_ptr
	reader, const DDS::RequestedIncompatibleQosStatus &status)
	THROW_ORB_EXCEPTIONS
{
	printf("\n=== [ListenerDataListener::on_requested_incompatible_qos] : triggered\n");
};

void ListenerDataListener::on_sample_rejected(DDS::DataReader_ptr reader, const
	DDS::SampleRejectedStatus &status)THROW_ORB_EXCEPTIONS
{
	printf("\n=== [ListenerDataListener::on_sample_rejected] : triggered\n");
};

void ListenerDataListener::on_liveliness_changed(DDS::DataReader_ptr reader,
	const DDS::LivelinessChangedStatus &status)THROW_ORB_EXCEPTIONS
{
	printf("\n=== [ListenerDataListener::on_liveliness_changed] : triggered\n");
};

void ListenerDataListener::on_subscription_matched(DDS::DataReader_ptr reader,
	const DDS::SubscriptionMatchedStatus &status)THROW_ORB_EXCEPTIONS
{
	printf("\n=== [ListenerDataListener::on_subscription_matched] : triggered\n");
};

void ListenerDataListener::on_sample_lost(DDS::DataReader_ptr reader, const DDS
	::SampleLostStatus &status)THROW_ORB_EXCEPTIONS
{
	printf("\n=== [ListenerDataListener::on_sample_lost] : triggered\n");
};
