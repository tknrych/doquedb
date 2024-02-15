// -*-Mode: C++; tab-width: 4; c-basic-offset: 4;-*-
// vi:set ts=4 sw=4:
//
// UnaAnalyzerManager.h --
// 
// Copyright (c) 2002, 2006, 2023 Ricoh Company, Ltd.
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

#ifndef __SYDNEY_INVERTED_UNAANALYZERMANAGER_H
#define __SYDNEY_INVERTED_UNAANALYZERMANAGER_H

#include "Inverted/Module.h"

#include "ModTypes.h"
#include "ModLanguageSet.h"

#ifdef SYD_USE_UNA_V10
namespace UNA {
#endif
class ModNlpAnalyzer;
#ifdef SYD_USE_UNA_V10
}
#endif

_SYDNEY_BEGIN
_SYDNEY_INVERTED_BEGIN

//
//	CLASS
//	Inverted::UnaAnalyzerManager --
//
//	NOTES
//
//
class UnaAnalyzerManager
{
public:
	// コンストラクタ
	UnaAnalyzerManager();
	// デストラクタ
	~UnaAnalyzerManager();

	// UNA解析器を得る
#ifdef SYD_USE_UNA_V10
	static UNA::ModNlpAnalyzer* get(const ModUInt32 unaRscId_);
#else
	static ModNlpAnalyzer* get(const ModUInt32 unaRscId_);
#endif

	// デフォルトの言語情報を得る
	static const ModLanguageSet& getDefaultLanguageSet();
	static const ModUnicodeString& getDefaultLanguageSetName();
};

_SYDNEY_INVERTED_END
_SYDNEY_END

#endif //__SYDNEY_INVERTED_UNAANALYZERMANAGER_H

//
//	Copyright (c) 2002, 2006, 2023 Ricoh Company, Ltd.
//	All rights reserved.
//
