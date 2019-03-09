
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
  * LOGICAL_NAME:    DDSEntityManager.h
  * DATE:            November 2018.
  *****************************************************************************
  *
  * This file contains the headers for entity management.
  *
  ***/

#ifndef _DDSENTITYMGR_
#define _DDSENTITYMGR_

#include "ccpp_dds_dcps.h"
#include "CheckStatus.h"

using namespace DDS;

class DDSEntityManager
{

private:
	/* Generic DDS entities */
	DomainParticipantFactory_var dpf;
	DomainParticipant_var participant;
	Topic_var topic;
	ContentFilteredTopic_var filteredTopic;
public:
	/* Publish and Subscriber Events */
	Publisher_var publisher;
	Subscriber_var subscriber;
	DataWriter_var writer;
	DataReader_var reader;
private:
	/* QosPolicy holders */
	TopicQos reliable_topic_qos;
	TopicQos setting_topic_qos;
	PublisherQos pub_qos;
	SubscriberQos sub_qos;

	DomainId_t domain;
	InstanceHandle_t userHandle;
	ReturnCode_t status;

	DDS::String_var partition;
	DDS::String_var typeName;
public:
	void createParticipant(const char *partitiontName);
	void registerType(TypeSupport *ts);
	void createPublisher();
	void createSubscriber();
	void createTopic(const char *topicName);
	void createContentFilteredTopic(const char *topicName, const char *filter,
		const StringSeq &expr);
	void createSubscriptionFilter(char *buffer, const char*topicName);
	void createWriter();
	void createReader(bool filtered);

	void deleteWriter(DDS::DataWriter_ptr dataWriter);
	void deleteReader(DDS::DataReader_ptr dataReader);
	void deleteFilteredTopic();
	void deleteTopic();
	void deletePublisher();
	void deleteSubscriber();
	void deleteParticipant();

	DataReader_ptr getReader();
	DataWriter_ptr getWriter();
	Publisher_ptr getPublisher();
	Subscriber_ptr getSubscriber();
	Topic_ptr getTopic();
	DomainParticipant_ptr getParticipant();

	~DDSEntityManager();

};

#endif
