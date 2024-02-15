// -*-Mode: C++; tab-width: 4; c-basic-offset: 4;-*-
// vi:set ts=4 sw=4:
//
// DExecution/Iterator/Class.h --
// 
// Copyright (c) 2012, 2013, 2023 Ricoh Company, Ltd.
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

#ifndef __SYDNEY_DEXECUTION_ITERATOR_CLASS_H
#define __SYDNEY_DEXECUTION_ITERATOR_CLASS_H

#include "DExecution/Iterator/Module.h"

_SYDNEY_BEGIN

namespace Common
{
	class Externalizable;
}

_SYDNEY_DEXECUTION_BEGIN
_SYDNEY_DEXECUTION_ITERATOR_BEGIN

// CLASS
//	DExecution::Iterator::Class -- static class for serialize-related functions
//
// NOTES
class Class
{
public:
	// ENUM
	//	DExecution::Iterator::Class::Category::Value --
	//
	// NOTES
	//	The value must be less than 100.
	struct Category
	{
		enum Value
		{
			Unknown		=   0,
			Expand,
			PreparedQuery,
			ServerQuery,
			ServerExecute,
			ValueNum
		};
	};

	// get instance from classid
	static Common::Externalizable* getClassInstance(int iClassID_);

	// get classid
	static int getClassID(Category::Value eCategory_);

protected:
private:
};

_SYDNEY_DEXECUTION_ITERATOR_END
_SYDNEY_DEXECUTION_END
_SYDNEY_END

#endif //__SYDNEY_DEXECUTION_ITERATOR_CLASS_H

//
//	Copyright (c) 2012, 2013, 2023 Ricoh Company, Ltd.
//	All rights reserved.
//
