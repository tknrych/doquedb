// -*-Mode: C++; tab-width: 4; c-basic-offset: 4;-*-
// vi:set ts=4 sw=4:
//
// ExpungeMP.cpp --
// 
// Copyright (c) 2011, 2023 Ricoh Company, Ltd.
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
const char moduleName[] = "FullText2";
}

#include "SyDefault.h"
#include "SyReinterpretCast.h"
#include "FullText2/ExpungeMP.h"
#include "FullText2/FullTextFile.h"
#include "FullText2/InvertedSection.h"
#include "FullText2/MergeReserve.h"

_SYDNEY_USING
_SYDNEY_FULLTEXT2_USING

namespace {
}

//
//	FUNCTION public
//	FullText2::ExpungeMP::ExpungeMP -- コンストラクタ
//
//	NOTES
//
//	ARGUMENTS
//	FullText2::FullTextFile& cFile_
//		全文ファイル
//	const Common::DataArrayData& cTuple_
//		タプルデータ
//	ModUInt32 uiDocID_
//		文書ID
//
//	RETURN
//	なし
//
//	EXCEPTIONS
//
ExpungeMP::ExpungeMP(FullTextFile& cFile_,
					 const Common::DataArrayData& cTuple_,
					 ModUInt32 uiDocID_)
	: m_cFile(cFile_), m_cTuple(cTuple_), m_uiDocID(uiDocID_)
{
}

//
//	FUNCTION public
//	FullText2::ExpungeMP::~ExpungeMP -- デストラクタ
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
ExpungeMP::~ExpungeMP()
{
}

//
//	FUNCTION public
//	FullText2::ExpungeMP::parallel
//		-- マルチスレッドで挿入を処理する
//
//	NOTES
//
//	ARUGMENTS
//	なし
//
//	EXCEPTIONS
//
void
ExpungeMP::parallel()
{
	// 複合索引の場合、キーごとにスレッドで処理し、高速化をはかる

	for (;;)
	{
		int key = m_cFile.getKeyNumber();
		if (key == -1)
			// もう処理すべきキーは存在しないので、終了
			break;

		// タプルデータを削除できる形に整える
		ModVector<ModUnicodeString> vecDocument;
		ModVector<ModLanguageSet> vecLanguage;
		double dblScore;

		m_cFile.convertData(key, m_cTuple,
							vecDocument, vecLanguage, dblScore);

		// このキーの該当するInvertedSectionを得る
		InvertedSection* pSection = m_cFile.getInvertedSection(key);

		// 削除する
		pSection->expunge(vecDocument,
						  vecLanguage,
						  m_uiDocID);

		// 削除が成功したので、全文ファイルに通知する
		m_cFile.pushSuccessKeyNumber(key);
	}
}

//
//	Copyright (c) 2011, 2023 Ricoh Company, Ltd.
//	All rights reserved.
//
