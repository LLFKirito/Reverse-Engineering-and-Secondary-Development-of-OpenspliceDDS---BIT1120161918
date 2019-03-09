#ifndef DIGITALSIGNSPLTYPES_H
#define DIGITALSIGNSPLTYPES_H

#include <c_base.h>
#include <c_misc.h>
#include <c_sync.h>
#include <c_collection.h>
#include <c_field.h>
#include <v_copyIn.h>

#include "ccpp_DigitalSign.h"


extern c_metaObject __DigitalSign_DigitalSignData__load (c_base base);

extern const char *DigitalSignData_Digest_metaDescriptor[];
extern const int DigitalSignData_Digest_metaDescriptorArrLength;
extern const int DigitalSignData_Digest_metaDescriptorLength;
extern c_metaObject __DigitalSignData_Digest__load (c_base base);
struct _DigitalSignData_Digest ;
extern  v_copyin_result __DigitalSignData_Digest__copyIn(c_base base, const struct DigitalSignData::Digest *from, struct _DigitalSignData_Digest *to);
extern  void __DigitalSignData_Digest__copyOut(const void *_from, void *_to);
struct _DigitalSignData_Digest {
    c_ulonglong high;
    c_ulonglong low;
};

extern const char *DigitalSignData_Signature_metaDescriptor[];
extern const int DigitalSignData_Signature_metaDescriptorArrLength;
extern const int DigitalSignData_Signature_metaDescriptorLength;
extern c_metaObject __DigitalSignData_Signature__load (c_base base);
struct _DigitalSignData_Signature ;
extern  v_copyin_result __DigitalSignData_Signature__copyIn(c_base base, const struct DigitalSignData::Signature *from, struct _DigitalSignData_Signature *to);
extern  void __DigitalSignData_Signature__copyOut(const void *_from, void *_to);
struct _DigitalSignData_Signature {
    c_ulonglong value[4];
};

extern const char *DigitalSignData_Msg_metaDescriptor[];
extern const int DigitalSignData_Msg_metaDescriptorArrLength;
extern const int DigitalSignData_Msg_metaDescriptorLength;
extern c_metaObject __DigitalSignData_Msg__load (c_base base);
struct _DigitalSignData_Msg ;
extern  v_copyin_result __DigitalSignData_Msg__copyIn(c_base base, const struct DigitalSignData::Msg *from, struct _DigitalSignData_Msg *to);
extern  void __DigitalSignData_Msg__copyOut(const void *_from, void *_to);
struct _DigitalSignData_Msg {
    c_long sendID;
    c_long receiveID;
    c_string message;
    struct _DigitalSignData_Digest digest;
    struct _DigitalSignData_Signature sign;
    c_bool d_invaild;
    c_bool s_invaild;
};

#undef OS_API
#endif
