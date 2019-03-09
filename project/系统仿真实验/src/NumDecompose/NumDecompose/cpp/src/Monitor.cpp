
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
  * LOGICAL_NAME:    Monitor.cpp
  * DATE:            November 2018.
  *****************************************************************************/


#include <string>
#include <sstream>
#include <iostream>
#include "DDSEntityManager.h"
#include "..\standalone\ccpp_NumDecomposeData.h"
#include "ListenerDataListener.h"
#include "vortex_os.h"

using namespace DDS;
using namespace NumDecomposeData;

#define MONID        0
#define MAX_FIL_LEN  256
#define FILTER       true
#define NO_FILTER    false

int Monitor(int argc, char *argv[])
{
	DDSEntityManager mgr;

	mgr.createParticipant("NumDecompose");
	NumSentTypeSupport_var type = new NumSentTypeSupport();
	mgr.registerType(type.in());
	mgr.createTopic("NumberDecompose");
	mgr.createSubscriber();
	mgr.createReader(NO_FILTER);

	DataReader_var dreader = mgr.getReader();
	NumSentDataReader_var NumSentReader = NumSentDataReader::_narrow(dreader.in());
	checkHandle(NumSentReader.in(), "NumSentReader::_narrow");

	//set listener
	ListenerDataListener *myListener = new ListenerDataListener();
	myListener->m_MsgReader = NumSentDataReader::_narrow(dreader.in());
	checkHandle(myListener->m_MsgReader.in(), "MsgDataReader::_narrow");
	DDS::StatusMask mask = DDS::DATA_AVAILABLE_STATUS;
	myListener->m_MsgReader->set_listener(myListener, mask);
	myListener->m_closed = false;

	DDS::WaitSet_var ws = new DDS::WaitSet();
	ws->attach_condition(myListener->m_guardCond);
	DDS::ConditionSeq condSeq;
	while (!myListener->m_closed) {
		ws->wait(condSeq, DDS::DURATION_INFINITE);
	}

	delete myListener;
	mgr.deleteReader(NumSentReader.in());
	mgr.deleteTopic();
	mgr.deleteSubscriber();
	mgr.deleteParticipant();

	return 0;
}

int main(int argc, char *argv[])
{
	return Monitor(argc, argv);
}
