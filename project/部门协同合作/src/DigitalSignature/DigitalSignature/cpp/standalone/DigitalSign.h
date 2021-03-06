//******************************************************************
// 
//  Generated by IDL to C++ Translator
//  
//  File name: DigitalSign.h
//  Source: DigitalSign.idl
//  Generated: Thu Nov  1 16:32:03 2018
//  OpenSplice 6.7.180404OSS
//  
//******************************************************************
#ifndef _DIGITALSIGN_H_
#define _DIGITALSIGN_H_

#include "sacpp_mapping.h"


namespace DigitalSignData
{
   struct Digest;
   struct Signature;
   struct Msg;

   struct Digest
   {
         DDS::ULongLong high;
         DDS::ULongLong low;
   };

   typedef DDS_DCPSStruct_var < Digest> Digest_var;
   typedef Digest&Digest_out;

   struct Signature
   {
         typedef DDS::ULongLong _value_slice;
         typedef DDS::ULongLong _value[4];
         typedef _value _value_out;
         static _value_slice * _value_alloc ();
         static void _value_free (_value_slice *);
         static void _value_copy (_value_slice* to, const _value_slice* from);
         static _value_slice *_value_dup (const _value_slice* from);

         struct _value_uniq_ {};
         typedef DDS_DCPS_FArray_var< _value, _value_slice, struct _value_uniq_> _value_var;
         typedef DDS_DCPS_Array_forany< _value, _value_slice, struct _value_uniq_> _value_forany;
         _value value;
   };

   typedef DDS_DCPSStruct_var < Signature> Signature_var;
   typedef Signature&Signature_out;

   struct Msg
   {
         DDS::Long sendID;
         DDS::Long receiveID;
         DDS::String_mgr message;
         Digest digest;
         Signature sign;
         DDS::Boolean d_invaild;
         DDS::Boolean s_invaild;
   };

   typedef DDS_DCPSStruct_var < Msg> Msg_var;
   typedef DDS_DCPSStruct_out < Msg> Msg_out;
}
template <>
DigitalSignData::Signature::_value_slice* DDS_DCPS_ArrayHelper < DigitalSignData::Signature::_value, DigitalSignData::Signature::_value_slice, DigitalSignData::Signature::_value_uniq_>::alloc ();
template <>
void DDS_DCPS_ArrayHelper < DigitalSignData::Signature::_value, DigitalSignData::Signature::_value_slice, DigitalSignData::Signature::_value_uniq_>::copy (DigitalSignData::Signature::_value_slice *to, const DigitalSignData::Signature::_value_slice* from);
template <>
void DDS_DCPS_ArrayHelper < DigitalSignData::Signature::_value, DigitalSignData::Signature::_value_slice, DigitalSignData::Signature::_value_uniq_>::free (DigitalSignData::Signature::_value_slice *ptr);




#endif
