// -*-Mode: C++; tab-width: 4; c-basic-offset: 4;-*-
// vi:set ts=4 sw=4:
//
// Execution/Operator/Limit.h --
// 
// Copyright (c) 2009, 2011, 2023 Ricoh Company, Ltd.
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

#ifndef __SYDNEY_EXECUTION_OPERATOR_LIMIT_H
#define __SYDNEY_EXECUTION_OPERATOR_LIMIT_H

#include "Execution/Operator/Module.h"
#include "Execution/Declaration.h"

#include "Execution/Interface/IAction.h"

#include "Opt/Algorithm.h"

#include "Common/Object.h"

_SYDNEY_BEGIN
_SYDNEY_EXECUTION_BEGIN
_SYDNEY_EXECUTION_OPERATOR_BEGIN

////////////////////////////////////////////////////////////////////////////////
//	CLASS
//	Execution::Operator::Limit -- operator class for limit to collection
//
//	NOTES
//		This class is not constructed directly
class Limit
	: public Interface::IAction
{
public:
	typedef Interface::IAction Super;
	typedef Limit This;

	// constructor
	static This* create(Interface::IProgram& cProgram_,
						Interface::IIterator* pIterator_,
						int iIteratorID_,
						const PAIR<int, int>& cLimit_,
						bool bIntermediate_ = false);
	// for partial sorting
	struct Partial
	{
		static This* create(Interface::IProgram& cProgram_,
							Interface::IIterator* pIterator_,
							int iIteratorID_,
							const PAIR<int, int>& cLimit_,
							int iKeyID_);
	};

	// destructor
	virtual ~Limit() {}

	// for serialize
	static This* getInstance(int iCategory_);

protected:
	// constructor
	Limit() : Super() {}

private:
};

_SYDNEY_EXECUTION_OPERATOR_END
_SYDNEY_EXECUTION_END
_SYDNEY_END

#endif // __SYDNEY_EXECUTION_OPERATOR_LIMIT_H

//
//	Copyright (c) 2009, 2011, 2023 Ricoh Company, Ltd.
//	All rights reserved.
//
