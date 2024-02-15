// -*-Mode: C++; tab-width: 4; c-basic-offset: 4;-*-
// vi:set ts=4 sw=4:
//
// MergeDaemon.h --
// 
// Copyright (c) 2010, 2023 Ricoh Company, Ltd.
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

#ifndef __SYDNEY_FULLTEXT2_MERGEDAEMON_H
#define __SYDNEY_FULLTEXT2_MERGEDAEMON_H

#include "FullText2/Module.h"
#include "Common/Thread.h"
#include "Lock/Name.h"
#include "Trans/Transaction.h"
#include "Schema/Database.h"

_SYDNEY_BEGIN
_SYDNEY_FULLTEXT2_BEGIN

//
//	CLASS
//	FullText2::MergeDaemon --
//
//	NOTES
//
class MergeDaemon : public Common::Thread
{
public:
	// コンストラクタ
	MergeDaemon();
	// デストラクタ
	virtual ~MergeDaemon();

	// 実行スレッド
	void runnable();

private:
	// マージを実行する
	void merge(const Lock::FileName& cFileName_, int iElement_);
	
	// FileIDを得る
	const LogicalFile::FileID& getFileID(
		Schema::Database* pDatabase_,
		Trans::Transaction& cTransaction_,
		const Lock::FileName& cFileName_);

};

_SYDNEY_FULLTEXT2_END
_SYDNEY_END

#endif //__SYDNEY_FULLTEXT2_MERGEDAEMON_H

//
//	Copyright (c) 2010, 2023 Ricoh Company, Ltd.
//	All rights reserved.
//
