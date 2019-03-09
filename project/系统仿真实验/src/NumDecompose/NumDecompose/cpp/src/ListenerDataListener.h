
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
  * LOGICAL_NAME:    ListenerDataListener.h
  * DATE:            November 2018.
  *****************************************************************************/


#ifndef __LISTENER_H__
#define __LISTENER_H__

#include <string>
#include <sstream>
#include <iostream>
#include "ccpp_dds_dcps.h" 
#include "CheckStatus.h"
#include "..\standalone\ccpp_NumDecomposeData.h"
#include "NumDecomposeMethod.h"

using namespace NumDecomposeData;

// ------------------------------ Listeners ------------------------------
class ListenerDataListener : public virtual DDS::DataReaderListener
{

public:

	bool m_closed;
	NumSentDataReader_var m_MsgReader;
	NumSentDataWriter_var m_MsgWriter;
	DDS::GuardCondition_var m_guardCond;

	ListenerDataListener() {
		m_guardCond = new DDS::GuardCondition();
		m_closed = false;
	}

	/* Callback method implementation. */
	virtual void on_data_available(DDS::DataReader_ptr reader)
		THROW_ORB_EXCEPTIONS;

	virtual void on_requested_deadline_missed(DDS::DataReader_ptr reader,
		const DDS::RequestedDeadlineMissedStatus &status)THROW_ORB_EXCEPTIONS;

	virtual void on_requested_incompatible_qos(DDS::DataReader_ptr reader,
		const DDS::RequestedIncompatibleQosStatus &status)THROW_ORB_EXCEPTIONS;

	virtual void on_sample_rejected(DDS::DataReader_ptr reader, const DDS
		::SampleRejectedStatus &status)THROW_ORB_EXCEPTIONS;

	virtual void on_liveliness_changed(DDS::DataReader_ptr reader, const DDS
		::LivelinessChangedStatus &status)THROW_ORB_EXCEPTIONS;

	virtual void on_subscription_matched(DDS::DataReader_ptr reader, const
		DDS::SubscriptionMatchedStatus &status)THROW_ORB_EXCEPTIONS;

	virtual void on_sample_lost(DDS::DataReader_ptr reader, const DDS
		::SampleLostStatus &status)THROW_ORB_EXCEPTIONS;
};


#endif
