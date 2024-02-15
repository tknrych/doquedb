// -*-Mode: C++; tab-width: 4; c-basic-offset: 4;-*-
// vi:set ts=4 sw=4:
//
// Manager.cpp -- 
// 
// Copyright (c) 2011, 2012, 2023 Ricoh Company, Ltd.
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

namespace
{
const char srcFile[] = __FILE__;
const char moduleName[] = "Utility";
}

#include "SyDefault.h"
#include "SyReinterpretCast.h"
#include "SyInclude.h"

#include "Utility/Manager.h"
#include "Utility/OpenMP.h"
#include "Utility/TermResourceManager.h"

_TRMEISTER_USING
_TRMEISTER_UTILITY_USING

namespace 
{
}

//
//	FUNCTION
//	Utility::Manager::initialize -- ユーティリティモジュールの初期化を行う
//
//	NOTES
//
//	ARGUMENTS
//	なし
//
//	RETURN
//	なし
//
//	EXCEPTIONS
//
void
Manager::initialize()
{
	// OpenMP の初期化を行う
	Manager::OpenMP::initialize();

	// UNAの初期化を行う
	Manager::Una::initialize();
}

//
//	FUNCTION
//	Buffer::Manager::terminate -- ユーティリティモジュールの後処理を行う
//
//	NOTES
//
//	ARGUMENTS
//	なし
//
//	RETURN
//	なし
//
//	EXCEPTIONS
//
void
Manager::terminate()
{
	// ModTermの後処理を行う
	TermResourceManager::terminate();
	// UNAの後処理を行う
	Manager::Una::terminate();
	
	// OpenMP の後処理を行う
	Manager::OpenMP::terminate();
}

//
// Copyright (c) 2011, 2012, 2023 Ricoh Company, Ltd.
// All rights reserved.
//
