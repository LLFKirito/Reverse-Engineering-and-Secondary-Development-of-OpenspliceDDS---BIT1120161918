#ifndef NUMDECOMPOSEDATASPLTYPES_H
#define NUMDECOMPOSEDATASPLTYPES_H

#include <c_base.h>
#include <c_misc.h>
#include <c_sync.h>
#include <c_collection.h>
#include <c_field.h>
#include <v_copyIn.h>

#include "ccpp_NumDecomposeData.h"


extern c_metaObject __NumDecomposeData_NumDecomposeData__load (c_base base);

extern const char *NumDecomposeData_NumDec_metaDescriptor[];
extern const int NumDecomposeData_NumDec_metaDescriptorArrLength;
extern const int NumDecomposeData_NumDec_metaDescriptorLength;
extern c_metaObject __NumDecomposeData_NumDec__load (c_base base);
struct _NumDecomposeData_NumDec ;
extern  v_copyin_result __NumDecomposeData_NumDec__copyIn(c_base base, const struct NumDecomposeData::NumDec *from, struct _NumDecomposeData_NumDec *to);
extern  void __NumDecomposeData_NumDec__copyOut(const void *_from, void *_to);
struct _NumDecomposeData_NumDec {
    c_ulonglong large_num;
    c_ulonglong factor[2];
    c_bool valid_data;
    c_bool exception_flag;
};

extern const char *NumDecomposeData_NumSent_metaDescriptor[];
extern const int NumDecomposeData_NumSent_metaDescriptorArrLength;
extern const int NumDecomposeData_NumSent_metaDescriptorLength;
extern c_metaObject __NumDecomposeData_NumSent__load (c_base base);
struct _NumDecomposeData_NumSent ;
extern  v_copyin_result __NumDecomposeData_NumSent__copyIn(c_base base, const struct NumDecomposeData::NumSent *from, struct _NumDecomposeData_NumSent *to);
extern  void __NumDecomposeData_NumSent__copyOut(const void *_from, void *_to);
struct _NumDecomposeData_NumSent {
    c_ulonglong addressesID;
    c_ulonglong senderID;
    c_long mode;
    struct _NumDecomposeData_NumDec num[50];
    c_string message;
};

#undef OS_API
#endif
