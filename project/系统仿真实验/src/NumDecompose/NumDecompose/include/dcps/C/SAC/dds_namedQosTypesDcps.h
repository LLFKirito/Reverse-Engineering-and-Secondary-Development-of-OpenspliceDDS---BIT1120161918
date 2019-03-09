#ifndef DDS_NAMEDQOSTYPESDCPS_H
#define DDS_NAMEDQOSTYPESDCPS_H

#include <dds_primitive_types.h>

#include "dds_dcps_builtintopicsDcps.h"

#include "dds_sac_if.h"
#ifndef _DDS_NamedDomainParticipantQos_defined
#define _DDS_NamedDomainParticipantQos_defined
#ifdef __cplusplus
struct DDS_NamedDomainParticipantQos;
#else /* __cplusplus */
typedef struct DDS_NamedDomainParticipantQos DDS_NamedDomainParticipantQos;
#endif /* __cplusplus */
#endif /* _DDS_NamedDomainParticipantQos_defined */
SAC_BUILTIN DDS_NamedDomainParticipantQos *DDS_NamedDomainParticipantQos__alloc (void);

struct DDS_NamedDomainParticipantQos {
    DDS_string name;
    DDS_DomainParticipantQos domainparticipant_qos;
};

#ifndef _DDS_NamedPublisherQos_defined
#define _DDS_NamedPublisherQos_defined
#ifdef __cplusplus
struct DDS_NamedPublisherQos;
#else /* __cplusplus */
typedef struct DDS_NamedPublisherQos DDS_NamedPublisherQos;
#endif /* __cplusplus */
#endif /* _DDS_NamedPublisherQos_defined */
SAC_BUILTIN DDS_NamedPublisherQos *DDS_NamedPublisherQos__alloc (void);

struct DDS_NamedPublisherQos {
    DDS_string name;
    DDS_PublisherQos publisher_qos;
};

#ifndef _DDS_NamedSubscriberQos_defined
#define _DDS_NamedSubscriberQos_defined
#ifdef __cplusplus
struct DDS_NamedSubscriberQos;
#else /* __cplusplus */
typedef struct DDS_NamedSubscriberQos DDS_NamedSubscriberQos;
#endif /* __cplusplus */
#endif /* _DDS_NamedSubscriberQos_defined */
SAC_BUILTIN DDS_NamedSubscriberQos *DDS_NamedSubscriberQos__alloc (void);

struct DDS_NamedSubscriberQos {
    DDS_string name;
    DDS_SubscriberQos subscriber_qos;
};

#ifndef _DDS_NamedTopicQos_defined
#define _DDS_NamedTopicQos_defined
#ifdef __cplusplus
struct DDS_NamedTopicQos;
#else /* __cplusplus */
typedef struct DDS_NamedTopicQos DDS_NamedTopicQos;
#endif /* __cplusplus */
#endif /* _DDS_NamedTopicQos_defined */
SAC_BUILTIN DDS_NamedTopicQos *DDS_NamedTopicQos__alloc (void);

struct DDS_NamedTopicQos {
    DDS_string name;
    DDS_TopicQos topic_qos;
};

#ifndef _DDS_NamedDataWriterQos_defined
#define _DDS_NamedDataWriterQos_defined
#ifdef __cplusplus
struct DDS_NamedDataWriterQos;
#else /* __cplusplus */
typedef struct DDS_NamedDataWriterQos DDS_NamedDataWriterQos;
#endif /* __cplusplus */
#endif /* _DDS_NamedDataWriterQos_defined */
SAC_BUILTIN DDS_NamedDataWriterQos *DDS_NamedDataWriterQos__alloc (void);

struct DDS_NamedDataWriterQos {
    DDS_string name;
    DDS_DataWriterQos datawriter_qos;
};

#ifndef _DDS_NamedDataReaderQos_defined
#define _DDS_NamedDataReaderQos_defined
#ifdef __cplusplus
struct DDS_NamedDataReaderQos;
#else /* __cplusplus */
typedef struct DDS_NamedDataReaderQos DDS_NamedDataReaderQos;
#endif /* __cplusplus */
#endif /* _DDS_NamedDataReaderQos_defined */
SAC_BUILTIN DDS_NamedDataReaderQos *DDS_NamedDataReaderQos__alloc (void);

struct DDS_NamedDataReaderQos {
    DDS_string name;
    DDS_DataReaderQos datareader_qos;
};

#endif
