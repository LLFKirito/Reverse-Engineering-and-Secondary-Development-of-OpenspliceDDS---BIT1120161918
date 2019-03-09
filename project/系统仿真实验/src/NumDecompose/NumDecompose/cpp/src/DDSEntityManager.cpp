
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
  * LOGICAL_NAME:    DDSEntityManager.cpp
  * DATE:            November 2018.
  *****************************************************************************
  *
  * This file contains the implementation for entity management.
  *
  ***/

#include "DDSEntityManager.h"


void DDSEntityManager::createParticipant(const char *partitiontName)
{
	domain = DOMAIN_ID_DEFAULT;
	dpf = DomainParticipantFactory::get_instance();
	checkHandle(dpf.in(), "DDS::DomainParticipantFactory::get_instance");
	participant = dpf->create_participant(domain, PARTICIPANT_QOS_DEFAULT, NULL,
		STATUS_MASK_NONE);
	checkHandle(participant.in(),
		"DDS::DomainParticipantFactory::create_participant");
	partition = partitiontName;
}

void DDSEntityManager::registerType(TypeSupport *ts)
{
	typeName = ts->get_type_name();
	status = ts->register_type(participant.in(), typeName);
	checkStatus(status, "register_type");
}

void DDSEntityManager::createPublisher()
{
	status = participant->get_default_publisher_qos(pub_qos);
	checkStatus(status, "DDS::DomainParticipant::get_default_publisher_qos");
	pub_qos.partition.name.length(1);
	pub_qos.partition.name[0] = partition;

	publisher = participant->create_publisher(pub_qos, NULL, STATUS_MASK_NONE);
	checkHandle(publisher.in(), "DDS::DomainParticipant::create_publisher");
}

void DDSEntityManager::createSubscriber()
{
	int status = participant->get_default_subscriber_qos(sub_qos);
	checkStatus(status, "DDS::DomainParticipant::get_default_subscriber_qos");
	sub_qos.partition.name.length(1);
	sub_qos.partition.name[0] = partition;

	subscriber = participant->create_subscriber(sub_qos, NULL, STATUS_MASK_NONE);
	checkHandle(subscriber.in(), "DDS::DomainParticipant::create_subscriber");
}

void DDSEntityManager::createTopic(const char *topicName)
{
	status = participant->get_default_topic_qos(reliable_topic_qos);
	checkStatus(status, "DDS::DomainParticipant::get_default_topic_qos");
	reliable_topic_qos.reliability.kind = RELIABLE_RELIABILITY_QOS;
	reliable_topic_qos.durability.kind = TRANSIENT_DURABILITY_QOS;

	/* Make the tailored QoS the new default. */
	status = participant->set_default_topic_qos(reliable_topic_qos);
	checkStatus(status, "DDS::DomainParticipant::set_default_topic_qos");

	topic = participant->create_topic(topicName, typeName, reliable_topic_qos,
		NULL, STATUS_MASK_NONE);
	checkHandle(topic.in(), "DDS::DomainParticipant::create_topic ()");
}

void DDSEntityManager::createContentFilteredTopic(const char *topicName, const
	char *filter, const StringSeq &expr)
{
	filteredTopic = participant->create_contentfilteredtopic(topicName, topic,
		filter, expr);
	checkHandle(filteredTopic.in(),
		"DomainParticipant::create_contentfilteredtopic");
}

void DDSEntityManager::createSubscriptionFilter(char *buffer, const char *topicName)
{
	// create subscription filter
	DDS::String_var sFilter = DDS::string_dup(buffer);

	// Filter expr
	StringSeq sSeqExpr;
	sSeqExpr.length(0);

	// create Filtered topic
	createContentFilteredTopic(topicName, sFilter.in(), sSeqExpr);
}

void DDSEntityManager::createWriter()
{
	DataWriterQos dw_qos;
	status = publisher->get_default_datawriter_qos(dw_qos);
	checkStatus(status, "DDS::DomainParticipant::get_default_publisher_qos");
	status = publisher->copy_from_topic_qos(dw_qos, reliable_topic_qos);
	checkStatus(status, "DDS::Publisher::copy_from_topic_qos");
	dw_qos.writer_data_lifecycle.autodispose_unregistered_instances = true;
	writer = publisher->create_datawriter(topic.in(),
		dw_qos, NULL, STATUS_MASK_NONE);
	checkHandle(writer, "DDS::Publisher::create_datawriter");
}

void DDSEntityManager::createReader(bool filtered)
{
	if (!filtered)
	{
		reader = subscriber->create_datareader(topic.in(),
			DATAREADER_QOS_USE_TOPIC_QOS, NULL, STATUS_MASK_NONE);
		checkHandle(reader, "DDS::Subscriber::create_datareader ()");
	}
	else
	{
		reader = subscriber->create_datareader(filteredTopic.in(),
			DATAREADER_QOS_USE_TOPIC_QOS, NULL, STATUS_MASK_NONE);
		checkHandle(reader, "DDS::Subscriber::create_datareader ()");
	}
}

void DDSEntityManager::deleteWriter(DDS::DataWriter_ptr dataWriter)
{
	status = publisher->delete_datawriter(dataWriter);
	checkStatus(status, "DDS::Publisher::delete_datawriter ");
}

void DDSEntityManager::deleteReader(DDS::DataReader_ptr dataReader)
{
	status = subscriber->delete_datareader(dataReader);
	checkStatus(status, "DDS::Subscriber::delete_datareader ");
}

void DDSEntityManager::deleteFilteredTopic()
{
	status = participant->delete_contentfilteredtopic(filteredTopic);
	checkStatus(status, "DDS.DomainParticipant.delete_topic");
}

void DDSEntityManager::deleteTopic()
{
	status = participant->delete_topic(topic);
	checkStatus(status, "DDS.DomainParticipant.delete_topic");
}

void DDSEntityManager::deletePublisher()
{
	status = participant->delete_publisher(publisher);
	checkStatus(status, "DDS::DomainParticipant::delete_publisher");
}

void DDSEntityManager::deleteSubscriber()
{
	status = participant->delete_subscriber(subscriber.in());
	checkStatus(status, "DDS.DomainParticipant.delete_subscriber");
}

void DDSEntityManager::deleteParticipant()
{
	status = dpf->delete_participant(participant.in());
	checkStatus(status, "DDS::DomainParticipant::delete_participant");
}

DataReader_ptr DDSEntityManager::getReader()
{
	return DataReader::_duplicate(reader.in());
}

DataWriter_ptr DDSEntityManager::getWriter()
{
	return DataWriter::_duplicate(writer.in());
}

Publisher_ptr DDSEntityManager::getPublisher()
{
	return Publisher::_duplicate(publisher.in());
}

Subscriber_ptr DDSEntityManager::getSubscriber()
{
	return Subscriber::_duplicate(subscriber.in());
}

Topic_ptr DDSEntityManager::getTopic()
{
	return Topic::_duplicate(topic.in());
}

DomainParticipant_ptr DDSEntityManager::getParticipant()
{
	return DomainParticipant::_duplicate(participant.in());
}

DDSEntityManager::~DDSEntityManager() {

}
