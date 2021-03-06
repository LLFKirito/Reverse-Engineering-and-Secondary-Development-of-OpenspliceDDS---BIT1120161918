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
#ifndef OS_CLASSBASE_H
#define OS_CLASSBASE_H

#if defined (__cplusplus)
extern "C" {
#endif

#ifdef OSPL_BUILD_CORE
#define OS_API OS_API_EXPORT
#else
#define OS_API OS_API_IMPORT
#endif
/* !!!!!!!!NOTE From here no more includes are allowed!!!!!!! */

#define OS_STRUCT(name)  struct name##_s
#define OS_EXTENDS(type) OS_STRUCT(type) _parent
#define OS_CLASS(name)   typedef OS_STRUCT(name) *name
#define OS_SIZEOF(name)  sizeof(OS_STRUCT(name))
#define OS_SUPER(obj)    (&((obj)->_parent))

#undef OS_API

#if defined (__cplusplus)
}
#endif

#endif /* OS_CLASSBASE_H */
