/*
 *                         OpenSplice DDS
 *
 *   This software and documentation are Copyright 2006 to  PrismTech
 *   Limited, its affiliated companies and licensors. All rights reserved.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 *
 */
/*
 * The contents of this file is private to SPLICE-DDS and not meant for use by
 * any application other then application code generated by SPLICE-DDS tooling.
 */

#ifndef DDS_DCPS_PRIVATE_H
#define DDS_DCPS_PRIVATE_H

#include "u_entity.h"
#include "dds_dcps.h"
#include "os_if.h"


#ifdef OSPL_BUILD_DCPSSAC
#define OS_API OS_API_EXPORT
#else
#define OS_API OS_API_IMPORT
#endif
/* !!!!!!!!NOTE From here no more includes are allowed!!!!!!! */

/* ReturnCode which indicates if an instance handle has expired.
 * This ReturnCode is only to be used internally and is converted
 * to a ReturnCode BAD_PARAMETER when returning to the user.
 */
#define DDS_RETCODE_HANDLE_EXPIRED (13)

/*
 * This function prototype is an abstract specification of the
 * deallocation operation required for all objects that can be
 * free via the DDS_free operation.
 * All classes need to implement their specific implementation
 * of this operation, if not implemented the DDS_free operation
 * will use a default implementation that only frees memory in
 * a shallow manner, if more is required the class must implement
 * its own deallocation operation. This dealloc operation is
 * passed to the object constructor and assigned to the constructed
 * object, the DDS_free operation will call the deallocator
 * operation.
 */
typedef DDS_ReturnCode_t
(*DDS_deallocatorType)(
    DDS_Object object);

/* Generic DDS object allocation interface */

typedef void *
(*bufferAllocatorType)(
    DDS_unsigned_long len);

OS_API void *
DDS__malloc (
    DDS_deallocatorType deallocator,
    DDS_unsigned_long hl,
    DDS_unsigned_long len);

OS_API void *
DDS__header (
    void *object);

OS_API void *
DDS_alloc (
    DDS_unsigned_long l,
    DDS_deallocatorType deallocator);


/* Generic DDS_string interface */

OS_API DDS_char *
DDS_string_alloc (
    DDS_unsigned_long len);

OS_API DDS_char *
DDS_string_dup (
    const DDS_char *src);

OS_API void
DDS_string_clean (
    DDS_char **string);

OS_API void
DDS_string_replace (
    const DDS_char *src,
    DDS_char **dst);


/* Generic DDS_sequence interface */

OS_API _DDS_sequence
DDS_sequence_malloc (
    void);

OS_API void *
DDS_sequence_allocbuf (
    DDS_deallocatorType deallocator,
    DDS_unsigned_long len,
    DDS_unsigned_long count);

OS_API DDS_ReturnCode_t
DDS_sequence_free (
    _DDS_sequence sequence);

OS_API void
DDS_sequence_clean (
    _DDS_sequence sequence);

OS_API void
DDS_sequence_replacebuf (
    _DDS_sequence sequence,
    bufferAllocatorType allocbuf,
    DDS_unsigned_long count);

/**
 * Functions required by some internal tests.
 */
OS_API u_entity
DDS_Entity_get_user_entity_for_test (
    DDS_Entity _this);

OS_API u_object
DDS_Condition_get_user_object_for_test (
    DDS_Condition _this);

OS_API const DDS_char *
DDS_ReturnCode_image(
    DDS_ReturnCode_t code);


typedef void * (*DDS_allocBuffer)(DDS_unsigned_long len);
typedef void * (*DDS_registerType)(void *);
typedef v_copyin_result (*DDS_copyIn)(void *, void *, void *);
typedef void   (*DDS_copyOut)(void *, void *);

OS_API DDS_TypeSupport
DDS_TypeSupportNew (
    const DDS_char *type_name,
    const DDS_char *internal_type_name,
    const DDS_char *type_keys,
    const DDS_char **type_desc,
    int type_descArrSize,
    int type_descLength,
    const DDS_copyIn copy_in,
    const DDS_copyOut copy_out,
    const DDS_unsigned_long alloc_size,
    const DDS_allocBuffer alloc_buffer);


OS_API os_int32
DDS_Object_get_domain_id(
    DDS_Object object);

typedef enum {
    DDS_ENTITY_KIND_UNDEFINED,
    DDS_ENTITY_KIND_DOMAINPARTICIPANT,
    DDS_ENTITY_KIND_TOPIC,
    DDS_ENTITY_KIND_PUBLISHER,
    DDS_ENTITY_KIND_SUBSCRIBER,
    DDS_ENTITY_KIND_DATAWRITER,
    DDS_ENTITY_KIND_DATAREADER
} DDS_EntityKind_t;

OS_API DDS_EntityKind_t
DDS_Entity_get_kind(
    DDS_Entity _this);

typedef struct DDS_EntityUserData_s *DDS_EntityUserData;

typedef void (*DDS_Entity_user_data_destructor)(DDS_EntityUserData data);

struct DDS_EntityUserData_s {
	pa_uint32_t refCount;
	DDS_Entity_user_data_destructor destructor;
};

OS_API void
DDS_Entity_user_data_init(
   DDS_EntityUserData usedData,
   DDS_Entity_user_data_destructor destructor);

OS_API DDS_ReturnCode_t
DDS_Entity_set_user_data(
    DDS_Entity _this,
    DDS_EntityUserData usedData);

OS_API DDS_ReturnCode_t
DDS_Entity_claim_user_data(
    DDS_Entity _this,
    DDS_EntityUserData *userData);

OS_API void
DDS_Entity_release_user_data(
    DDS_EntityUserData userData);

OS_API DDS_ReturnCode_t
DDS_Entity_set_listener_mask(
    DDS_Entity _this,
    const DDS_StatusMask mask);

OS_API DDS_ReturnCode_t
DDS_Entity_read_status(
    DDS_Entity _this,
    DDS_StatusMask *status,
    DDS_StatusMask mask,
    DDS_boolean clear);

OS_API DDS_ReturnCode_t
DDS_ReadCondition_get_settings(
     DDS_ReadCondition _this,
     DDS_Entity source,
     u_object *obj,
     os_uint32 *mask);

OS_API  DDS_ReturnCode_t
DDS_Topic_get_typeSupport(
    DDS_Topic _this,
    DDS_TypeSupport *ts);


typedef struct DDS_TypeSupportCopyInfo_s *DDS_TypeSupportCopyInfo;

OS_API DDS_TypeSupportCopyInfo
DDS_TypeSupportCopyInfo_new (
   DDS_TypeSupport typeSupport);

OS_API void
DDS_TypeSupportCopyInfo_free(
   DDS_TypeSupportCopyInfo _this);

OS_API DDS_unsigned_long
DDS_TypeSupportCopyInfo_alloc_size (
    DDS_TypeSupportCopyInfo _this);

OS_API void *
DDS_TypeSupportCopyInfo_alloc_buffer (
    DDS_TypeSupportCopyInfo _this,
    DDS_long length);

OS_API void
DDS_TypeSupportCopyInfo_copy_out (
	DDS_TypeSupportCopyInfo _this,
	void *buffer,
	void *dst,
	void *src);

typedef enum {
    DDS_CONDITION_KIND_UNDEFINED,
    DDS_CONDITION_KIND_STATUS,
    DDS_CONDITION_KIND_GUARD,
    DDS_CONDITION_KIND_READ,
    DDS_CONDITION_KIND_QUERY
} DDS_ConditionKind_t;

OS_API DDS_ConditionKind_t
DDS_Condition_get_kind(
    DDS_Condition _this);


/*
 * Normally, DDS_WaitSet_wait returns a DDS_ConditionSeq that
 * contains triggered DDS_Conditions.
 * However, when the condition was attached to the WaitSet with
 * this function, the alternative pointer (can be NULL) will be
 * inserted into the DDS_ConditionSeq iso the condition itself.
 */
OS_API DDS_ReturnCode_t
DDS_WaitSet_attach_condition_alternative (
    DDS_WaitSet _this,
    const DDS_Condition cond,
    void *alternative);

#undef OS_API
#endif /* DDS_DCPS_PRIVATE_H */
