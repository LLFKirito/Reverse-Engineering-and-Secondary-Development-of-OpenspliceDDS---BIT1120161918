#ifndef DDS_NAMEDQOSTYPESSPLTYPES_H
#define DDS_NAMEDQOSTYPESSPLTYPES_H

#include <c_base.h>
#include <c_misc.h>
#include <c_sync.h>
#include <c_collection.h>
#include <c_field.h>
#include <v_copyIn.h>

#include "dds_namedQosTypesDcps.h"
#include "dds_dcps_builtintopicsSplDcps.h"

#include "dds_sac_if.h"

extern c_metaObject __dds_namedQosTypes_DDS__load (c_base base);

extern const char *DDS_NamedDomainParticipantQos_metaDescriptor[];
extern const int DDS_NamedDomainParticipantQos_metaDescriptorArrLength;
extern const int DDS_NamedDomainParticipantQos_metaDescriptorLength;
extern c_metaObject __DDS_NamedDomainParticipantQos__load (c_base base);
struct _DDS_NamedDomainParticipantQos ;
extern SAC_BUILTIN v_copyin_result __DDS_NamedDomainParticipantQos__copyIn(c_base base, const void *from, void *to);
extern SAC_BUILTIN void __DDS_NamedDomainParticipantQos__copyOut(const void *_from, void *_to);
struct _DDS_NamedDomainParticipantQos {
    c_string name;
    struct _DDS_DomainParticipantQos domainparticipant_qos;
};

extern const char *DDS_NamedPublisherQos_metaDescriptor[];
extern const int DDS_NamedPublisherQos_metaDescriptorArrLength;
extern const int DDS_NamedPublisherQos_metaDescriptorLength;
extern c_metaObject __DDS_NamedPublisherQos__load (c_base base);
struct _DDS_NamedPublisherQos ;
extern SAC_BUILTIN v_copyin_result __DDS_NamedPublisherQos__copyIn(c_base base, const void *from, void *to);
extern SAC_BUILTIN void __DDS_NamedPublisherQos__copyOut(const void *_from, void *_to);
struct _DDS_NamedPublisherQos {
    c_string name;
    struct _DDS_PublisherQos publisher_qos;
};

extern const char *DDS_NamedSubscriberQos_metaDescriptor[];
extern const int DDS_NamedSubscriberQos_metaDescriptorArrLength;
extern const int DDS_NamedSubscriberQos_metaDescriptorLength;
extern c_metaObject __DDS_NamedSubscriberQos__load (c_base base);
struct _DDS_NamedSubscriberQos ;
extern SAC_BUILTIN v_copyin_result __DDS_NamedSubscriberQos__copyIn(c_base base, const void *from, void *to);
extern SAC_BUILTIN void __DDS_NamedSubscriberQos__copyOut(const void *_from, void *_to);
struct _DDS_NamedSubscriberQos {
    c_string name;
    struct _DDS_SubscriberQos subscriber_qos;
};

extern const char *DDS_NamedTopicQos_metaDescriptor[];
extern const int DDS_NamedTopicQos_metaDescriptorArrLength;
extern const int DDS_NamedTopicQos_metaDescriptorLength;
extern c_metaObject __DDS_NamedTopicQos__load (c_base base);
struct _DDS_NamedTopicQos ;
extern SAC_BUILTIN v_copyin_result __DDS_NamedTopicQos__copyIn(c_base base, const void *from, void *to);
extern SAC_BUILTIN void __DDS_NamedTopicQos__copyOut(const void *_from, void *_to);
struct _DDS_NamedTopicQos {
    c_string name;
    struct _DDS_TopicQos topic_qos;
};

extern const char *DDS_NamedDataWriterQos_metaDescriptor[];
extern const int DDS_NamedDataWriterQos_metaDescriptorArrLength;
extern const int DDS_NamedDataWriterQos_metaDescriptorLength;
extern c_metaObject __DDS_NamedDataWriterQos__load (c_base base);
struct _DDS_NamedDataWriterQos ;
extern SAC_BUILTIN v_copyin_result __DDS_NamedDataWriterQos__copyIn(c_base base, const void *from, void *to);
extern SAC_BUILTIN void __DDS_NamedDataWriterQos__copyOut(const void *_from, void *_to);
struct _DDS_NamedDataWriterQos {
    c_string name;
    struct _DDS_DataWriterQos datawriter_qos;
};

extern const char *DDS_NamedDataReaderQos_metaDescriptor[];
extern const int DDS_NamedDataReaderQos_metaDescriptorArrLength;
extern const int DDS_NamedDataReaderQos_metaDescriptorLength;
extern c_metaObject __DDS_NamedDataReaderQos__load (c_base base);
struct _DDS_NamedDataReaderQos ;
extern SAC_BUILTIN v_copyin_result __DDS_NamedDataReaderQos__copyIn(c_base base, const void *from, void *to);
extern SAC_BUILTIN void __DDS_NamedDataReaderQos__copyOut(const void *_from, void *_to);
struct _DDS_NamedDataReaderQos {
    c_string name;
    struct _DDS_DataReaderQos datareader_qos;
};

#undef OS_API
#endif
