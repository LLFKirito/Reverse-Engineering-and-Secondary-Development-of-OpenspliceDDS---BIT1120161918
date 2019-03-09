
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


#include <sstream>
#include <Windows.h>
#include "ListenerDataListener.h"

using namespace DDS;
using namespace DigitalSignData;

#define NODEID  5
#define INVAILD true
#define VAILD   false

void ListenerDataListener::on_data_available(DDS::DataReader_ptr reader)
THROW_ORB_EXCEPTIONS
{
	DDS::ReturnCode_t status;
	MsgSeq msgList;
	SampleInfoSeq infoSeq;
	Msg msgInstance;

	status = m_MsgReader->take(msgList, infoSeq, LENGTH_UNLIMITED,
		ANY_SAMPLE_STATE, ANY_VIEW_STATE, ANY_INSTANCE_STATE);
	checkStatus(status, "MsgDataReader::read");
	for (DDS::ULong j = 0; j < msgList.length(); j++) {
		if (msgList[j].receiveID == 2) {
			if (msgList[j].sendID == 1) {
				cout << "The Digest department has received the message from Message department." << endl;
				cout << "MESSAGE: " << msgList[j].message << endl;
			}
			else if (msgList[j].sendID == 3) {
				cout << "The Digest department has received the message from Signature department." << endl;
				cout << "Signature department found error!" << endl;
				cout << "MESSAGE: " << msgList[j].message << endl;
				cout << "Recalculating message-digest......" << endl;
			}
		}
		else if (msgList[j].receiveID == 3) {
			if (msgList[j].sendID == 2) {
				cout << "The Signature department has received the message from Digest department." << endl;
				cout << "MESSAGE: " << msgList[j].message << endl;
				cout << "MESSAGE-DIGEST: " << msgList[j].digest.high << msgList[j].digest.low << endl;
			}
			else if (msgList[j].sendID == 4) {
				cout << "The Signature department has received the message from Inspection department." << endl;
				cout << "Inspection department found error!" << endl;
				cout << "MESSAGE: " << msgList[j].message << endl;
				cout << "MESSAGE-DIGEST: " << msgList[j].digest.high << msgList[j].digest.low << endl;
				cout << "Recalculating digital signature......" << endl;
			}
		}
		else if (msgList[j].receiveID == 4) {
			cout << "The Inspection department has received the message from Signature department." << endl;
			cout << "MESSAGE: " << msgList[j].message << endl;
			cout << "MESSAGE-DIGEST: " << msgList[j].digest.high << msgList[j].digest.low << endl;
			cout << "DIGITAL SIGNATURE: " << msgList[j].sign.value[0] << msgList[j].sign.value[1] << msgList[j].sign.value[2] << msgList[j].sign.value[3] << endl;
			cout << "Inspecting digital signature......" << endl;
		}
		else if (msgList[j].receiveID == 5) {
			cout << "EVERYTHING HAS DONE" << endl;
		}
		cout << "------------------------------------------------------------------------------------------------------" << endl;
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
