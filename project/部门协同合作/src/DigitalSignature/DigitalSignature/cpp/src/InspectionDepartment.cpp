
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
  * LOGICAL_NAME:    InspectionDepartment.cpp
  * DATE:            November 2018.
  *****************************************************************************/


#include <string>
#include <sstream>
#include <iostream>
#include "vortex_os.h"
#include "DDSEntityManager.h"
#include "ListenerDataListener.h"


using namespace DDS;
using namespace DigitalSignData;

#define NODEID        4
#define NEXTDEP       5
#define MAX_FIL_LEN   256
#define MAX_MSG_LEN   100000
#define FILTER        true
#define NO_FILTER     false

int InspectionDepartment(int argc, char *argv[])
{
	DDSEntityManager mgr;

	mgr.createParticipant("DigitalSign");
	MsgTypeSupport_var type = new MsgTypeSupport();
	mgr.registerType(type.in());
	mgr.createTopic("DigitalSign");
	char buf[MAX_MSG_LEN];
	snprintf(buf, MAX_MSG_LEN, "receiveID = %llu", NODEID);
	mgr.createSubscriptionFilter(buf, "DigitalSignTopic");
	mgr.createPublisher();
	mgr.createSubscriber();
	mgr.createWriter();
	mgr.createReader(FILTER);

	DataWriter_var dwriter = mgr.getWriter();
	MsgDataWriter_var MsgWriter = MsgDataWriter::_narrow(dwriter.in());
	checkHandle(MsgWriter.in(), "MsgWriter::_narrow");
	DataReader_var dreader = mgr.getReader();
	MsgDataReader_var MsgReader = MsgDataReader::_narrow(dreader.in());
	checkHandle(MsgReader.in(), "MsgReader::_narrow");

	ListenerDataListener *myListener = new ListenerDataListener();
	myListener->m_MsgWriter = MsgDataWriter::_narrow(dwriter.in());
	checkHandle(myListener->m_MsgWriter.in(), "MsgDataWriter::_narrow");
	myListener->m_MsgReader = MsgDataReader::_narrow(dreader.in());
	checkHandle(myListener->m_MsgReader.in(), "MsgDataReader::_narrow");
	DDS::StatusMask mask = DDS::DATA_AVAILABLE_STATUS;
	myListener->m_MsgReader->set_listener(myListener, mask);
	myListener->m_closed = false;

	cout << "Inspection department ready." << endl;

	DDS::WaitSet_var ws = new DDS::WaitSet();
	ws->attach_condition(myListener->m_guardCond);
	DDS::ConditionSeq condSeq;
	while (!myListener->m_closed) {
		ws->wait(condSeq, DDS::DURATION_INFINITE);
	}

	delete myListener;
	mgr.deleteWriter(MsgWriter.in());
	mgr.deleteReader(MsgReader.in());
	mgr.deleteFilteredTopic();
	mgr.deleteTopic();
	mgr.deletePublisher();
	mgr.deleteSubscriber();
	mgr.deleteParticipant();

	cout << "Inspection department shutdown." << endl;

	return 0;
}

int main(int argc, char *argv[])
{
	return InspectionDepartment(argc, argv);
}
