// -*-Mode: C++; tab-width: 4; c-basic-offset: 4;-*-
// vi:set ts=4 sw=4:
//
// IDVectorFile.cpp -- ROWID <-> 文書IDの変換を行うベクターファイル
// 
// Copyright (c) 2010, 2011, 2012, 2023 Ricoh Company, Ltd.
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
#include "FullText2/IDVectorFile.h"

#include "FullText2/FakeError.h"
#include "FullText2/MessageAll_Class.h"

#include "Version/File.h"

#include "Os/File.h"
#include "Os/Limits.h"
#include "Os/Memory.h"

#include "Schema/File.h"

_SYDNEY_USING
_SYDNEY_FULLTEXT2_USING

namespace
{
}

//
//	FUNCTION public
//	FullText2::IDVectorFile::IDVectorFile -- コンストラクタ
//
//	NOTES
//
//	ARGUMENTS
//	const FullText2::FileID& cFileID_
//		ファイルID
//	const Os::Path& cPath_
//		このファイルを格納するパス
//	bool bBatch_
//		バッチモードか否か
//
//	RETURN
//	なし
//
//	EXCEPTIONS
//
IDVectorFile::IDVectorFile(const FullText2::FileID& cFileID_,
						   const Os::Path& cPath_, bool bBatch_)
	: VectorFile(cFileID_, cPath_, bBatch_)
{
}

//
//	FUNCTION public
//	FullText2::IDVectorFile::~IDVectorFile -- デストラクタ
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
IDVectorFile::~IDVectorFile()
{
}

//
//	FUNCTION public
//	FullText2::OtherInformationFile::verify -- 整合性検査を行う
//
//	NOTES
//
//	ARGUMENTS
//	const Trans::Transaction& cTransaction_
//		トランザクション
//	const Admin::Verification::Treatment::Value eTreatment_
//		動作
//	Admin::Verification::Progress& cProgress_
//		経過
//
//	RETURN
//	なし
//
//	EXCEPTIONS
//
void
IDVectorFile::verify(const Trans::Transaction& cTransaction_,
					 const Admin::Verification::Treatment::Value eTreatment_,
					 Admin::Verification::Progress& cProgress_)
{
	if (isMounted(cTransaction_))
	{
		// すべてのデータが読み出せるか確認する

		// 整合性検査の開始を通知
		startVerification(cTransaction_, eTreatment_, cProgress_);

		try
		{
			// ファイルに格納されている最大のキー
			ModUInt32 uiMaxKey = getMaxKey();

			ModSize count = 0;
			uiMaxKey += 1;

			for (ModUInt32 id = 0; id < uiMaxKey; ++id)
			{
				// ファイルを読み込む
				ModUInt32 uiValue;
				if (get(id, uiValue) == true)

					// 登録件数
					++count;

			}

			// 登録件数を確認する
			if (count != getCount())
			{
				_SYDNEY_VERIFY_INCONSISTENT(
					cProgress_, m_cPath,
					Message::IllegalEntryCount(getCount(), count));
			}

			flushAllPages();
			
			// 整合性検査の終了を通知
			endVerification();
		}
#ifdef NO_CATCH_ALL
		catch (Exception::Object&)
#else
		catch (...)
#endif
		{
			recoverAllPages();
			
			// 整合性検査の終了を通知
			endVerification();

			_SYDNEY_RETHROW;
		}
	}
}

//
//	FUNCTION public
//	FullText2::IDVectorFile::insert -- 挿入する
//
//	NOTES
//
//	ARGUMENTS
//	ModUInt32 uiKey_
//		キー
//	ModUInt32 uiValue_
//	   	バリュー
//
//	RETURN
//	なし
//
//	EXCEPTIONS
//
void
IDVectorFile::insert(ModUInt32 uiKey_, ModUInt32 uiValue_)
{
	// 書き込む位置を得る
	char* buf = getBuffer(uiKey_);

	// 書き込む
	Os::Memory::copy(buf, &uiValue_, sizeof(ModUInt32));

	// 読み込まれていなければ、ヘッダーを読み込む
	readHeader();
	
	// 登録件数を更新する
	++m_cHeader.m_uiCount;
	
	if (m_cHeader.m_uiMaxKey < uiKey_)
		// 最大のキーを更新する
		m_cHeader.m_uiMaxKey = uiKey_;
	
	// ヘッダーを更新したのでダーティにする
	m_bDirtyHeaderPage = true;

	; _FULLTEXT2_FAKE_ERROR(IDVectorFile::insert);
}

//
//	FUNCTION public
//	FullText2::IDVectorFile::expunge -- 削除する
//
//	NOTES
//
//	ARUGMENTS
//	ModUInt32 uiKey_
//		キー
//
//	RETURN
//	なし
//
//	EXCEPTIONS
//
void
IDVectorFile::expunge(ModUInt32 uiKey_)
{
	if (isMounted(*m_pTransaction))
	{
		// 書き込む位置を得る
		char* buf = getBuffer(uiKey_);

		// 0xffffffff を書き込む
		ModUInt32 v = Os::Limits<ModUInt32>::getMax();
		Os::Memory::copy(buf, &v, sizeof(ModUInt32));
		
		// 読み込まれていなければ、ヘッダーを読み込む
		readHeader();
		
		// 登録件数を更新する
		--m_cHeader.m_uiCount;

		// ヘッダーを更新したのでダーティにする
		m_bDirtyHeaderPage = true;
		
		; _FULLTEXT2_FAKE_ERROR(IDVectorFile::expunge);
	}
}

//
//	FUNCTION public
//	FullText2::IDVectorFile::get -- 取得する
//
//	NOTES
//
//	ARGUMENTS
//	ModUInt32 uiKey_
//		キー
//	ModUInt32& uiValue_
//		バリュー
//
//	RETURN
//	bool
//		バリューが存在する場合はtrue、存在しない場合はfalse
//
//	EXCEPTIONS
//
bool
IDVectorFile::get(ModUInt32 uiKey_, ModUInt32& uiValue_)
{
	bool result = false;
	
	// バリューの位置を得る
	const char* buf = getConstBuffer(uiKey_);
	if (buf)
	{
		// そのキーのページが存在している

		Os::Memory::copy(&uiValue_, buf, sizeof(ModUInt32));

		if (uiValue_ != Os::Limits<ModUInt32>::getMax())
		{
			// データが格納されている

			result = true;
		}
	}

	return result;
}

//
//	FUNCTION public
//	FullText2::IDVectorFile::getAll -- すべての値を取得する
//
//	NOTES
//
//	ARGUMENTS
//	Common::LargeVector<ModUInt32>& vecValue_
//		バリュー
//
//	RETURN
//	なし
//
//	EXCEPTIONS
//
void
IDVectorFile::getAll(Common::LargeVector<ModUInt32>& vecValue_)
{
	if (isMounted(*m_pTransaction) == false || getCount() == 0)
		return;
	
	vecValue_.reserve(vecValue_.getSize() + getCount());
		
	Version::Page::ID pageID = 0;	// 0 はヘッダーなので問題ない
	ModUInt32 maxKey = getMaxKey();
	const ModUInt32* p = 0;
	maxKey += 1;
		
	for (ModUInt32 i = 0; i < maxKey; ++i)
	{
		int offset;
		Version::Page::ID current = convertToPageID(i, offset);
		if (current != pageID)
		{
			// ページが変わったので、このキー値がページの先頭
			// ページの先頭領域を得る
				
			p = syd_reinterpret_cast<const ModUInt32*>(getConstBuffer(i));
			pageID = current;
		}

		if (*p != Os::Limits<ModUInt32>::getMax())
		{
			// データが格納されている

			vecValue_.pushBack(*p);
		}

		// 次へ
		++p;
	}
}

//
//	FUNCTION private
//	FullText2::IDVectorFile::getConstBuffer -- IDから格納領域を得る
//	FullText2::IDVectorFile::getBuffer
//
//	NOTES
//
//	ARGUMENTS
//	ModUInt32 uiKey_
//		キー値
//
//	RETURN
//	const char*
//	char*
//		格納領域へのポインタ
//
//	EXCEPTIONS
//
const char*
IDVectorFile::getConstBuffer(ModUInt32 uiKey_)
{
	// キー -> ページID+オフセットへ変換
	int offset = 0;
	Version::Page::ID id = convertToPageID(uiKey_, offset);
	if (id > getMaxPageID())
		return 0;

	// ページを得る
	fixPage(id);

	// メモリーを得る
	const char* buf = m_pCurrentPage->getConstBuffer();

	return buf + offset;
}
char*
IDVectorFile::getBuffer(ModUInt32 uiKey_)
{
	// キー -> ページID+オフセットへ変換
	int offset = 0;
	Version::Page::ID id = convertToPageID(uiKey_, offset);
	if (id > getMaxPageID())
	{
		// 最大ページIDより大きい -> 必要なところまでallocateする
		allocatePage(id);
	}

	// ページを得る
	fixPage(id);

	// メモリーを得る
	char* buf = m_pCurrentPage->getBuffer();
	// 更新するために取得しているので dirty にする
	m_pCurrentPage->dirty();

	return buf + offset;
}

//
//	Copyright (c) 2010, 2011, 2012, 2023 Ricoh Company, Ltd.
//	All rights reserved.
//
