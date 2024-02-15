// -*-Mode: C++; tab-width: 4; c-basic-offset: 4;-*-
// vi:set ts=4 sw=4:
//
// CommitStatement.cpp --
// 
// Copyright (c) 2000, 2002, 2023 Ricoh Company, Ltd.
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

namespace {
const char srcFile[] = __FILE__;
const char moduleName[] = "Statement";
}

#include "SyDefault.h"
#include "SyReinterpretCast.h"
#include "SyDynamicCast.h"

#include "Statement/Type.h"
#include "Statement/CommitStatement.h"
#if 0
#include "Analysis/CommitStatement.h"
#endif

_SYDNEY_USING
using namespace Statement;

namespace {
	// メンバのm_vecpElements内でのindex
	enum {
		f__end_index
	};
}

//
//	FUNCTION public
//	Statement::CommitStatement::CommitStatement -- コンストラクタ
//
//	NOTES
//	コンストラクタ。
//
//	ARGUMENTS
//	なし
//
//	RETURN
//	なし
//
//	EXCEPTIONS
//	なし
//
CommitStatement::CommitStatement()
	: Object(ObjectType::CommitStatement, f__end_index, Object::Undefine, true)
{
}

//
//	FUNCTION public
//	Statement::CommitStatement::~CommitStatement -- デストラクタ
//
//	NOTES
//	デストラクタ。
//
//	ARGUMENTS
//	なし
//
//	RETURN
//	なし
//
//	EXCEPTIONS
//	なし
//
CommitStatement::~CommitStatement()
{
}

//
//	FUNCTION public
//	Statement::CommitStatement::copy -- 自身をコピーする
//
//	NOTES
//
//	ARGUMENTS
//	なし
//
//	RETURN
//	Statement::Object*
//
//	EXCEPTIONS
//	なし
//
Object*
CommitStatement::copy() const
{
	return new CommitStatement(*this);
}

#if 0
namespace
{
	Analysis::CommitStatement _analyzer;
}

// Analyzerを得る
//virtual
const Analysis::Analyzer*
CommitStatement::
getAnalyzer() const
{
	return &_analyzer;
}
#endif

//
//	Copyright (c) 2000, 2002, 2023 Ricoh Company, Ltd.
//	All rights reserved.
//
