//******************************************************************
// 
//  Generated by IDL to C++ Translator
//  
//  File name: NumDecomposeData.h
//  Source: NumDecomposeData.idl
//  Generated: Wed Nov  7 16:38:27 2018
//  OpenSplice 6.7.180404OSS
//  
//******************************************************************
#ifndef _NUMDECOMPOSEDATA_H_
#define _NUMDECOMPOSEDATA_H_

#include "sacpp_mapping.h"


namespace NumDecomposeData
{
   struct NumDec;
   struct NumSent;

   struct NumDec
   {
         typedef DDS::ULongLong _factor_slice;
         typedef DDS::ULongLong _factor[2];
         typedef _factor _factor_out;
         static _factor_slice * _factor_alloc ();
         static void _factor_free (_factor_slice *);
         static void _factor_copy (_factor_slice* to, const _factor_slice* from);
         static _factor_slice *_factor_dup (const _factor_slice* from);

         struct _factor_uniq_ {};
         typedef DDS_DCPS_FArray_var< _factor, _factor_slice, struct _factor_uniq_> _factor_var;
         typedef DDS_DCPS_Array_forany< _factor, _factor_slice, struct _factor_uniq_> _factor_forany;
         DDS::ULongLong large_num;
         _factor factor;
         DDS::Boolean valid_data;
         DDS::Boolean exception_flag;
   };

   typedef DDS_DCPSStruct_var < NumDec> NumDec_var;
   typedef NumDec&NumDec_out;

   struct NumSent
   {
         typedef NumDecomposeData::NumDec _num_slice;
         typedef NumDecomposeData::NumDec _num[50];
         typedef _num _num_out;
         static _num_slice * _num_alloc ();
         static void _num_free (_num_slice *);
         static void _num_copy (_num_slice* to, const _num_slice* from);
         static _num_slice *_num_dup (const _num_slice* from);

         struct _num_uniq_ {};
         typedef DDS_DCPS_FArray_var< _num, _num_slice, struct _num_uniq_> _num_var;
         typedef DDS_DCPS_Array_forany< _num, _num_slice, struct _num_uniq_> _num_forany;
         DDS::ULongLong addressesID;
         DDS::ULongLong senderID;
         DDS::Long mode;
         _num num;
         DDS::String_mgr message;
   };

   typedef DDS_DCPSStruct_var < NumSent> NumSent_var;
   typedef DDS_DCPSStruct_out < NumSent> NumSent_out;
}
template <>
NumDecomposeData::NumDec::_factor_slice* DDS_DCPS_ArrayHelper < NumDecomposeData::NumDec::_factor, NumDecomposeData::NumDec::_factor_slice, NumDecomposeData::NumDec::_factor_uniq_>::alloc ();
template <>
void DDS_DCPS_ArrayHelper < NumDecomposeData::NumDec::_factor, NumDecomposeData::NumDec::_factor_slice, NumDecomposeData::NumDec::_factor_uniq_>::copy (NumDecomposeData::NumDec::_factor_slice *to, const NumDecomposeData::NumDec::_factor_slice* from);
template <>
void DDS_DCPS_ArrayHelper < NumDecomposeData::NumDec::_factor, NumDecomposeData::NumDec::_factor_slice, NumDecomposeData::NumDec::_factor_uniq_>::free (NumDecomposeData::NumDec::_factor_slice *ptr);
template <>
NumDecomposeData::NumSent::_num_slice* DDS_DCPS_ArrayHelper < NumDecomposeData::NumSent::_num, NumDecomposeData::NumSent::_num_slice, NumDecomposeData::NumSent::_num_uniq_>::alloc ();
template <>
void DDS_DCPS_ArrayHelper < NumDecomposeData::NumSent::_num, NumDecomposeData::NumSent::_num_slice, NumDecomposeData::NumSent::_num_uniq_>::copy (NumDecomposeData::NumSent::_num_slice *to, const NumDecomposeData::NumSent::_num_slice* from);
template <>
void DDS_DCPS_ArrayHelper < NumDecomposeData::NumSent::_num, NumDecomposeData::NumSent::_num_slice, NumDecomposeData::NumSent::_num_uniq_>::free (NumDecomposeData::NumSent::_num_slice *ptr);




#endif
