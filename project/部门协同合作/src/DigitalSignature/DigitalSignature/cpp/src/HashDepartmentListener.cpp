
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
  * LOGICAL_NAME:    HashDepartmentListener.cpp
  * DATE:            November 2018.
  *****************************************************************************/


#include "ListenerDataListener.h"
#include <sstream>
#include <Windows.h>

using namespace DDS;
using namespace DigitalSignData;

#define PASTDEP       1
#define NODEID        2
#define NEXTDEP       3
#define INVAILD       true
#define VAILD         false

void ListenerDataListener::on_data_available(DDS::DataReader_ptr reader)
THROW_ORB_EXCEPTIONS
{
	DDS::ReturnCode_t status;
	MsgSeq msgList;
	SampleInfoSeq infoSeq;
	Msg msgInstance;
	srand(time(NULL));
	DDS::Boolean error = rand() % 2;

	Sleep(1000);
	status = m_MsgReader->take(msgList, infoSeq, LENGTH_UNLIMITED,
		ANY_SAMPLE_STATE, ANY_VIEW_STATE, ANY_INSTANCE_STATE);
	checkStatus(status, "MsgDataReader::read");
	for (DDS::ULong j = 0; j < msgList.length(); j++){
		if (msgList[j].sendID == PASTDEP) {
			cout << "The Digest department has received the message from Message department." << endl;
			cout << "MESSAGE: " << msgList[j].message << endl;
		}
		else if (msgList[j].sendID == NEXTDEP) {
			cout << "The Digest department has received the message from Signature department." << endl;
			cout << "Signature department found error!" << endl;
			cout << "MESSAGE: " << msgList[j].message << endl;
			cout << "Recalculating message-digest......" << endl;
		}
		Hash hash;
		hash.getMD5(msgList[j].message.m_ptr);
		msgInstance.sendID = NODEID;
		msgInstance.receiveID = NEXTDEP;
		msgInstance.message = msgList[j].message;
		if (error == true) {
			msgInstance.digest.high = 0;
			msgInstance.digest.low = 0;
		}
		else {
			msgInstance.digest.high = hash.high;
			msgInstance.digest.low = hash.low;
		}
		ReturnCode_t status = m_MsgWriter->write(msgInstance, NULL);
		checkStatus(status, "MsgDataWriter::write");
		cout << "Send to Signature department." << endl;
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
