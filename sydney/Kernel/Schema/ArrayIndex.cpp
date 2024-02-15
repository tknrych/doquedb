// -*-Mode: C++; tab-width: 4; c-basic-offset: 4;-*-
// vi:set ts=4 sw=4:
//
// ArrayIndex.cpp -- array索引関連の関数定義
// 
// Copyright (c) 2007, 2015, 2023 Ricoh Company, Ltd.
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
const char moduleName[] = "Schema";
}

#include "SyDefault.h"
#include "SyReinterpretCast.h"

#include "Schema/ArrayIndex.h"
#include "Schema/AreaCategory.h"
#include "Schema/ArrayFile.h"
#include "Schema/Table.h"
#include "Schema/Column.h"
#include "Schema/Key.h"
#include "Schema/Field.h"
#include "Schema/LogData.h"

#include "Statement/IndexDefinition.h"
#include "Common/Assert.h"

_SYDNEY_USING
_SYDNEY_SCHEMA_USING

//	FUNCTION public
//	Schema::ArrayIndex::ArrayIndex -- array索引を表すクラスのデフォルトコンストラクター
//
//	NOTES
//
//	ARGUMENTS
//		なし
//
//	RETURN
//		なし
//
//	EXCEPTIONS
//		なし

ArrayIndex::
ArrayIndex()
	: Index(Category::Array)
{ }

//	FUNCTION public
//	Schema::ArrayIndex::ArrayIndex -- array索引を表すクラスのコンストラクター
//
//	NOTES
//
//	ARGUMENTS
//		const Schema::Database& database
//			索引が属するデータベース
//		Schema::Table& table
//			索引が属する表
//		const Schema::Object::Name& cName_
//			索引の名称
//		Schema::Hint* pHint_
//			索引のヒント
//
//	RETURN
//		なし
//
//	EXCEPTIONS

ArrayIndex::
ArrayIndex(const Database& database, Table& table, const Name& cName_, Hint* pHint_)
	: Index(Category::Array, database, table, cName_, pHint_)
{ }

//	FUNCTION public
//	Schema::ArrayIndex::ArrayIndex -- データベースからの索引を表すクラスのコンストラクター
//
//	NOTES
//
//	ARGUMENTS
//		Schema::Database&	database
//			索引が存在するデータベースを表すクラス
//		const Schema::LogData& cLogData_
//			索引作成のログ
//
//	RETURN
//		なし
//
//	EXCEPTIONS

ArrayIndex::
ArrayIndex(const Database& database, const LogData& cLogData_)
	: Index(Category::Array, database, cLogData_)
{ }

//	FUNCTION protected
//	Schema::ArrayIndex::createFile --
//		索引を構成するファイルのクラスを生成する
//
//	NOTES
//		オブジェクトを作成するだけで実際のファイルはまだ作成されない
//
//	ARGUMENTS
//		Trans::Transaction& cTrans_
//			操作をするトランザクション記述子
//
//	RETURN
//		作成したファイルオブジェクト
//
//	EXCEPTIONS

File::Pointer
ArrayIndex::
createFile(Trans::Transaction& cTrans_)
{
	return ArrayFile::create(cTrans_, *getDatabase(cTrans_),
							  *getTable(cTrans_), *this,
							  getHint(), getAreaHint());
}

//	FUNCTION protected
//	Schema::ArrayIndex::createField --
//		索引を構成するファイルのフィールドクラスを生成する
//
//	NOTES
//		オブジェクトを作成するだけで実際のファイルはまだ作成されない
//
//	ARGUMENTS
//		Trans::Transaction& cTrans_
//			操作をするトランザクション記述子
//		File& cFile_
//			索引を構成するファイルオブジェクト
//		const Common::DataArrayData* pLogData_ /* = 0 */
//
//	RETURN
//		なし
//
//	EXCEPTIONS

void
ArrayIndex::
createField(Trans::Transaction& cTrans_, File& cFile_,
			const Common::DataArrayData* pLogData_ /* = 0 */)
{
	// ファイルの状態は「生成」である
	; _SYDNEY_ASSERT(cFile_.getStatus() == Status::Created
					 || cFile_.getStatus() == Status::Mounted);

	// 索引を構成するキーの値を格納するフィールドをファイルに加えていく
	// ★注意★
	// キーに対応するフィールドとTIDのフィールドはどの索引でも加えられる
	// 索引ごとに固有のフィールドはこの後で設定される

	const ModVector<Key*>& keys = getKey(cTrans_);

	ModSize n = keys.getSize();
	for (ModSize i = 0; i < n; ++i) {
		; _SYDNEY_ASSERT(keys[i]);

		// キーとファイルにフィールドを登録する
		// ★注意★
		// source->addDestinationは永続化後の処理で行う

		// Array索引のキーは常にPutableである
		Field::Permission::Value permission = Field::Permission::Putable;

		(void) keys[i]->setField(*(cFile_.addField(*keys[i], permission, cTrans_,
												   cFile_.getNextFieldID(cTrans_, pLogData_))));
	}

	// 索引で探索した結果得られる
	// ある表のタプル ID の値を格納するフィールドを、
	// ファイルに加える
	{
		; _SYDNEY_ASSERT(getTable(cTrans_));

		Column* column = getTable(cTrans_)->getTupleID(cTrans_);
		; _SYDNEY_ASSERT(column);

		Field* source = column->getField(cTrans_);
		; _SYDNEY_ASSERT(source);

		// ★注意★
		// source->addDestinationは永続化後に行う

		cFile_.addField(Field::Category::Data, Field::Permission::All, *source, *column, cTrans_,
						cFile_.getNextFieldID(cTrans_, pLogData_));
	}
}

//	FUNCTION public
//	Schema::ArrayIndex::getClassID -- このクラスのクラス ID を得る
//
//	NOTES
//
//	ARGUMENTS
//		なし
//
//	RETURN
//		なし
//
//	EXCEPTIONS
//		なし

int
ArrayIndex::
getClassID() const
{
	return Externalizable::Category::ArrayIndex +
		Common::Externalizable::SchemaClasses;
}

//	FUNCTION public
//	Schema::ArrayIndex::getAreaCategory --
//		索引を実現するファイルを格納するエリアの種別を得る
//
//	NOTES
//
//	ARGUMENTS
//		なし
//
//	RETURN
//		Schema::AreaCategory::Value
//			索引を実現するファイルを格納するエリアの種別を表す値
//
//	EXCEPTIONS
//

AreaCategory::Value
ArrayIndex::
getAreaCategory() const
{
	return AreaCategory::Index;
}

//
// Copyright (c) 2007, 2015, 2023 Ricoh Company, Ltd.
// All rights reserved.
//
