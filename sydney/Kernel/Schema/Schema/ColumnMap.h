// -*-Mode: C++; tab-width: 4; c-basic-offmap: 4;-*-
// vi:map ts=4 sw=4:
//
// ColumnMap.h -- スキーマオブジェクトのマップを表すクラス定義、関数宣言
// 
// Copyright (c) 2002, 2023 Ricoh Company, Ltd.
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

#ifndef	__SYDNEY_SCHEMA_COLUMN_MAP_H
#define	__SYDNEY_SCHEMA_COLUMN_MAP_H

#include "Schema/ObjectMap.h"
#include "Schema/Column.h"

_SYDNEY_BEGIN
_SYDNEY_SCHEMA_BEGIN

//	CLASS public
//	Schema::ColumnMap --
//
//	NOTES

class ColumnMap
	: public ObjectMap<Column, ColumnPointer>
{
public:
	ColumnMap();

	// ColumnMapからオブジェクトを得るのに使用する比較関数
	static bool findByCategory(Column* pColumn_, Column::Category::Value eCategory_);
	static bool findByPosition(Column* pColumn_, Column::Position iPosition_);
};

//	FUNCTION public
//	Schema::ColumnMap::findByCategory -- カテゴリーでオブジェクトを探すための比較関数
//
//	NOTES
//
//	ARGUMENTS
//		Schema::Column* pColumn_
//			比較対象のオブジェクト
//		Column::Category::Value eCategory_
//			条件となる値
//
//	RETURN
//		なし
//
//	EXCEPTIONS

// static
inline bool
ColumnMap::
findByCategory(Column* pColumn_, Column::Category::Value eCategory_)
{
	return (pColumn_->getCategory() == eCategory_);
}

//	FUNCTION public
//	Schema::ColumnMap::findByPosition -- 位置でオブジェクトを探すための比較関数
//
//	NOTES
//
//	ARGUMENTS
//		Schema::Column* pColumn_
//			比較対象のオブジェクト
//		Column::Position iPosition_
//			条件となる値
//
//	RETURN
//		なし
//
//	EXCEPTIONS

// static
inline bool
ColumnMap::
findByPosition(Column* pColumn_, Column::Position iPosition_)
{
	return (pColumn_->getPosition() == iPosition_);
}

_SYDNEY_SCHEMA_END
_SYDNEY_END

#endif // __SYDNEY_SCHEMA_COLUMN_MAP_H

//
// Copyright (c) 2002, 2023 Ricoh Company, Ltd.
// All rights reserved.
//
