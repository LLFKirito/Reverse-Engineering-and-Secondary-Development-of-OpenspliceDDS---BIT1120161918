#include "DigitalSignSplDcps.h"
#include "ccpp_DigitalSign.h"

#include <v_copyIn.h>
#include <v_topic.h>
#include <os_stdlib.h>
#include <string.h>
#include <os_report.h>

v_copyin_result
__DigitalSignData_Digest__copyIn(
    c_base base,
    const struct ::DigitalSignData::Digest *from,
    struct _DigitalSignData_Digest *to)
{
    v_copyin_result result = V_COPYIN_RESULT_OK;
    (void) base;

    to->high = (c_ulonglong)from->high;
    to->low = (c_ulonglong)from->low;
    return result;
}

v_copyin_result
__DigitalSignData_Signature__copyIn(
    c_base base,
    const struct ::DigitalSignData::Signature *from,
    struct _DigitalSignData_Signature *to)
{
    v_copyin_result result = V_COPYIN_RESULT_OK;
    (void) base;

    {
        typedef c_ulonglong _DestType[4];
        _DestType *dest = &to->value;
        memcpy (dest, from->value, sizeof (*dest));
    }
    return result;
}

v_copyin_result
__DigitalSignData_Msg__copyIn(
    c_base base,
    const struct ::DigitalSignData::Msg *from,
    struct _DigitalSignData_Msg *to)
{
    v_copyin_result result = V_COPYIN_RESULT_OK;
    (void) base;

    to->sendID = (c_long)from->sendID;
    to->receiveID = (c_long)from->receiveID;
#ifdef OSPL_BOUNDS_CHECK
    if(from->message){
        to->message = c_stringNew_s(base, from->message);
        if(to->message == NULL) {
            result = V_COPYIN_RESULT_OUT_OF_MEMORY;
        }
    } else {
        OS_REPORT (OS_ERROR, "copyIn", 0,"Member 'DigitalSignData::Msg.message' of type 'c_string' is NULL.");
        result = V_COPYIN_RESULT_INVALID;
    }
#else
    to->message = c_stringNew_s(base, from->message);
    if(to->message == NULL) {
        result = V_COPYIN_RESULT_OUT_OF_MEMORY;
    }
#endif
    if(V_COPYIN_RESULT_IS_OK(result)){
        extern v_copyin_result __DigitalSignData_Digest__copyIn(c_base, const ::DigitalSignData::Digest *, _DigitalSignData_Digest *);
        result = __DigitalSignData_Digest__copyIn(base, &from->digest, &to->digest);
    }
    if(V_COPYIN_RESULT_IS_OK(result)){
        extern v_copyin_result __DigitalSignData_Signature__copyIn(c_base, const ::DigitalSignData::Signature *, _DigitalSignData_Signature *);
        result = __DigitalSignData_Signature__copyIn(base, &from->sign, &to->sign);
    }
    to->d_invaild = (c_bool)from->d_invaild;
    to->s_invaild = (c_bool)from->s_invaild;
    return result;
}

void
__DigitalSignData_Digest__copyOut(
    const void *_from,
    void *_to)
{
    const struct _DigitalSignData_Digest *from = (const struct _DigitalSignData_Digest *)_from;
    struct ::DigitalSignData::Digest *to = (struct ::DigitalSignData::Digest *)_to;
    to->high = (::DDS::ULongLong)from->high;
    to->low = (::DDS::ULongLong)from->low;
}

void
__DigitalSignData_Signature__copyOut(
    const void *_from,
    void *_to)
{
    const struct _DigitalSignData_Signature *from = (const struct _DigitalSignData_Signature *)_from;
    struct ::DigitalSignData::Signature *to = (struct ::DigitalSignData::Signature *)_to;
    {
        typedef c_ulonglong _DestType[4];
        const _DestType *src = &from->value;

        memcpy ((void *)to->value, src, sizeof (*src));
    }
}

void
__DigitalSignData_Msg__copyOut(
    const void *_from,
    void *_to)
{
    const struct _DigitalSignData_Msg *from = (const struct _DigitalSignData_Msg *)_from;
    struct ::DigitalSignData::Msg *to = (struct ::DigitalSignData::Msg *)_to;
    to->sendID = (::DDS::Long)from->sendID;
    to->receiveID = (::DDS::Long)from->receiveID;
    to->message = DDS::string_dup(from->message ? from->message : "");
    {
        extern void __DigitalSignData_Digest__copyOut(const void *, void *);
        __DigitalSignData_Digest__copyOut((const void *)&from->digest, (void *)&to->digest);
    }
    {
        extern void __DigitalSignData_Signature__copyOut(const void *, void *);
        __DigitalSignData_Signature__copyOut((const void *)&from->sign, (void *)&to->sign);
    }
    to->d_invaild = (::DDS::Boolean)(from->d_invaild != 0);
    to->s_invaild = (::DDS::Boolean)(from->s_invaild != 0);
}

