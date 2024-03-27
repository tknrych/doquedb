// -*-Mode: C++; tab-width: 4;-*-
// vi:set ts=4 sw=4:	
//
// ModOsDriver.h -- ModOsDriver のクラス定義
// 
// Copyright (c) 1997, 2011, 2023 Ricoh Company, Ltd.
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//     http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// 

#ifndef	__ModOsDriver_H__
#define __ModOsDriver_H__

#include "ModTypes.h"

// クラス階層構造
//	上
//	MemoryHandle
//	LinkedList, ModOsDriver::Mutex
//	下
// 仮想OSドライバはメモリ管理の対象からはずす。

// OS 依存のドライバをインクルードする
#ifdef  OS_RHLINUX6_0
#include "ModOsDriverLinux.h"
#endif

#endif	// __ModOsDriver_H__

//
// Copyright (c) 1997, 2011, 2023 Ricoh Company, Ltd.
// All rights reserved.
//
