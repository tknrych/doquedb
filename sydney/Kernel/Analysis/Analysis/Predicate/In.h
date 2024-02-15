// -*-Mode: C++; tab-width: 4; c-basic-offset: 4;-*-
// vi:set ts=4 sw=4:
//
// Predicate/In.h --
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

#ifndef __SYDNEY_ANALYSIS_PREDICATE_IN_H
#define __SYDNEY_ANALYSIS_PREDICATE_IN_H

#include "Analysis/Predicate/Base.h"

_SYDNEY_BEGIN
_SYDNEY_ANALYSIS_BEGIN
_SYDNEY_ANALYSIS_PREDICATE_BEGIN

////////////////////////////////////////////////////////////////////////////
// CLASS
//	Predicate::In -- value expression analyzer for in predicate
//
// NOTES
class In
	: public Base
{
public:
	typedef In This;
	typedef Base Super;

	// constuctor
	static const This* create(const Statement::ValueExpression* pStatement_);
	// destructor
	virtual ~In() {}

protected:
	// constructor
	In() {}
private:
};

_SYDNEY_ANALYSIS_PREDICATE_END
_SYDNEY_ANALYSIS_END
_SYDNEY_END

#endif // __SYDNEY_ANALYSIS_PREDICATE_IN_H

//
//	Copyright (c) 2010, 2023 Ricoh Company, Ltd.
//	All rights reserved.
//
