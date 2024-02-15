// -*-Mode: C++; tab-width: 4; c-basic-offset: 4;-*-
// vi:set ts=4 sw=4:
//
// StartExplainStatement.h --
// 
// Copyright (c) 2007, 2012, 2023 Ricoh Company, Ltd.
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

#ifndef __SYDNEY_STATEMENT_STARTEXPLAINSTATEMENT_H
#define __SYDNEY_STATEMENT_STARTEXPLAINSTATEMENT_H

#include "Statement/Object.h"

_SYDNEY_BEGIN
_SYDNEY_STATEMENT_BEGIN

class ExplainOption;

//
//	CLASS
//	Statement::StartExplainStatement --
//
//	NOTES
//
//
class SYD_STATEMENT_FUNCTION StartExplainStatement
	: public Object
{
public:
	//constructor
	StartExplainStatement()
		: Object(ObjectType::StartExplainStatement)
	{}
	//constructors
	StartExplainStatement(ExplainOption* pOption_);

	//destructor
	virtual ~StartExplainStatement();

	// accessor
	ExplainOption* getOption() const;

	void setOption(ExplainOption* pOption_);
    
	//copy
	Object* copy() const;

protected:
private:
	// assignment operator is not used
	StartExplainStatement& operator=(const StartExplainStatement& cOther_);
};

_SYDNEY_STATEMENT_END
_SYDNEY_END

#endif //__SYDNEY_STATEMENT_STARTEXPLAINSTATEMENT_H

//
//	Copyright (c) 2007, 2012, 2023 Ricoh Company, Ltd.
//	All rights reserved.
//
