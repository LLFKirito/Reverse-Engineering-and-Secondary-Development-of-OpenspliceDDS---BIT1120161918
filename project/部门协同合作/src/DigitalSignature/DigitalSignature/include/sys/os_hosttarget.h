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
#ifndef OS_HOSTTARGET_H
#define OS_HOSTTARGET_H
#include "os_macrostringify.h"

#ifdef OSPL_HOST
#define OSPL_HOST_STR OSPL_STRINGIFY(OSPL_HOST)
#else
#define OSPL_HOST_STR ""
#endif

#ifdef OSPL_TARGET
#define OSPL_TARGET_STR OSPL_STRINGIFY(OSPL_TARGET)
#else
#define OSPL_TARGET_STR ""
#endif

#endif
