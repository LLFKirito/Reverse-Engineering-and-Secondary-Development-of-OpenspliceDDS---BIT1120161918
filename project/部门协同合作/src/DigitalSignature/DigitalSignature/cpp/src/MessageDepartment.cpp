
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
  * LOGICAL_NAME:    MessageDepartment.cpp
  * DATE:            November 2018.
  *****************************************************************************/


#include <string>
#include <sstream>
#include <iostream>
#include "vortex_os.h"
#include "..\standalone\ccpp_DigitalSign.h"
#include "DDSEntityManager.h"

using namespace DDS;
using namespace DigitalSignData;

#define NODEID        1
#define NEXTDEP       2
#define MAX_FIL_LEN   256
#define MAX_MSG_LEN   100000
#define FILTER        true
#define NO_FILTER     false

int MessageDepartment(int argc, char *argv[])
{
	DDSEntityManager mgr;

	mgr.createParticipant("DigitalSign");
	MsgTypeSupport_var type = new MsgTypeSupport();
	mgr.registerType(type.in());
	mgr.createTopic("DigitalSign");
	mgr.createPublisher();
	mgr.createWriter();

	DataWriter_var dwriter = mgr.getWriter();
	MsgDataWriter_var MsgWriter = MsgDataWriter::_narrow(dwriter.in());
	checkHandle(MsgWriter.in(), "MsgWriter::_narrow");

	cout << "Message department ready." << endl;

	Msg msgInstance;
	msgInstance.sendID = NODEID;
	msgInstance.receiveID = NEXTDEP;

	bool closed = false;
	while (!closed) {
		char buffer[MAX_MSG_LEN] = { 0 };
		cin.getline(buffer,MAX_MSG_LEN);
		if (strcmp(buffer, "close") == 0) 
			break;
		msgInstance.message = DDS::string_dup(buffer);
		ReturnCode_t status = MsgWriter->write(msgInstance, NULL);
		checkStatus(status, "MsgDataWriter::write");
		cout << "Send to Digest department." << endl;
	}

	mgr.deleteWriter(MsgWriter.in());
	mgr.deleteTopic();
	mgr.deletePublisher();
	mgr.deleteParticipant();
	
	cout << "Message department shutdown." << endl;

	return 0;
}

int main(int argc, char *argv[])
{
	return MessageDepartment(argc, argv);
}
