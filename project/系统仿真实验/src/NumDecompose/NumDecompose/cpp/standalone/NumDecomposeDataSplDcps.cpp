#include "NumDecomposeDataSplDcps.h"
#include "ccpp_NumDecomposeData.h"

#include <v_copyIn.h>
#include <v_topic.h>
#include <os_stdlib.h>
#include <string.h>
#include <os_report.h>

v_copyin_result
__NumDecomposeData_NumDec__copyIn(
    c_base base,
    const struct ::NumDecomposeData::NumDec *from,
    struct _NumDecomposeData_NumDec *to)
{
    v_copyin_result result = V_COPYIN_RESULT_OK;
    (void) base;

    to->large_num = (c_ulonglong)from->large_num;
    {
        typedef c_ulonglong _DestType[2];
        _DestType *dest = &to->factor;
        memcpy (dest, from->factor, sizeof (*dest));
    }
    to->valid_data = (c_bool)from->valid_data;
    to->exception_flag = (c_bool)from->exception_flag;
    return result;
}

v_copyin_result
__NumDecomposeData_NumSent__copyIn(
    c_base base,
    const struct ::NumDecomposeData::NumSent *from,
    struct _NumDecomposeData_NumSent *to)
{
    v_copyin_result result = V_COPYIN_RESULT_OK;
    (void) base;

    to->addressesID = (c_ulonglong)from->addressesID;
    to->senderID = (c_ulonglong)from->senderID;
    to->mode = (c_long)from->mode;
    {
        typedef struct _NumDecomposeData_NumDec _DestType[50];
        _DestType *dest = &to->num;
        int i1;

        for (i1 = 0; (i1 < 50) && V_COPYIN_RESULT_IS_OK(result); i1++) {
            extern v_copyin_result __NumDecomposeData_NumDec__copyIn(c_base base,
    const NumDecomposeData::NumDec *From,
    struct _NumDecomposeData_NumDec *To);

if(V_COPYIN_RESULT_IS_OK(result)){
                result = __NumDecomposeData_NumDec__copyIn(base, (::NumDecomposeData::NumDec *)&(from->num)[i1], (struct _NumDecomposeData_NumDec *)&(*dest)[i1]);
            }
        }
    }
#ifdef OSPL_BOUNDS_CHECK
    if(from->message){
        to->message = c_stringNew_s(base, from->message);
        if(to->message == NULL) {
            result = V_COPYIN_RESULT_OUT_OF_MEMORY;
        }
    } else {
        OS_REPORT (OS_ERROR, "copyIn", 0,"Member 'NumDecomposeData::NumSent.message' of type 'c_string' is NULL.");
        result = V_COPYIN_RESULT_INVALID;
    }
#else
    to->message = c_stringNew_s(base, from->message);
    if(to->message == NULL) {
        result = V_COPYIN_RESULT_OUT_OF_MEMORY;
    }
#endif
    return result;
}

void
__NumDecomposeData_NumDec__copyOut(
    const void *_from,
    void *_to)
{
    const struct _NumDecomposeData_NumDec *from = (const struct _NumDecomposeData_NumDec *)_from;
    struct ::NumDecomposeData::NumDec *to = (struct ::NumDecomposeData::NumDec *)_to;
    to->large_num = (::DDS::ULongLong)from->large_num;
    {
        typedef c_ulonglong _DestType[2];
        const _DestType *src = &from->factor;

        memcpy ((void *)to->factor, src, sizeof (*src));
    }
    to->valid_data = (::DDS::Boolean)(from->valid_data != 0);
    to->exception_flag = (::DDS::Boolean)(from->exception_flag != 0);
}

void
__NumDecomposeData_NumSent__copyOut(
    const void *_from,
    void *_to)
{
    const struct _NumDecomposeData_NumSent *from = (const struct _NumDecomposeData_NumSent *)_from;
    struct ::NumDecomposeData::NumSent *to = (struct ::NumDecomposeData::NumSent *)_to;
    to->addressesID = (::DDS::ULongLong)from->addressesID;
    to->senderID = (::DDS::ULongLong)from->senderID;
    to->mode = (::DDS::Long)from->mode;
    {
        typedef struct _NumDecomposeData_NumDec _DestType[50];
        const _DestType *src = &from->num;

        int i1;

        for (i1 = 0; (i1 < 50); i1++) {
            extern void __NumDecomposeData_NumDec__copyOut(const void *, void *);
            __NumDecomposeData_NumDec__copyOut((const void *)&(*src)[i1], (void *)&(to->num)[i1]);
        }
    }
    to->message = DDS::string_dup(from->message ? from->message : "");
}

