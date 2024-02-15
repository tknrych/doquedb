// -*-Mode: C++; tab-width: 4; c-basic-offset: 4;-*-
// vi:set ts=4 sw=4:
//
// Candidate/Procedure.h --
// 
// Copyright (c) 2012, 2023 Ricoh Company, Ltd.
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

#ifndef __SYDNEY_PLAN_CANDIDATE_PROCEDURE_H
#define __SYDNEY_PLAN_CANDIDATE_PROCEDURE_H

#include "Plan/Candidate/Base.h"

_SYDNEY_BEGIN
_SYDNEY_PLAN_BEGIN
_SYDNEY_PLAN_CANDIDATE_BEGIN

////////////////////////////////////////////////////
// CLASS
//	Plan::Candidate::Procedure -- implementation class of Interface::ICandidate for procedure
//
// NOTES
class Procedure
	: public Base
{
public:
	typedef Procedure This;
	typedef Base Super;

	// constructor
	static This* create(Opt::Environment& cEnvironment_,
						Relation::Procedure* pRelation_);

	// destructor
	virtual ~Procedure() {}

protected:
	// constructor
	Procedure()
		: Super()
	{}

private:
};

_SYDNEY_PLAN_CANDIDATE_END
_SYDNEY_PLAN_END
_SYDNEY_END

#endif // __SYDNEY_PLAN_CANDIDATE_PROCEDURE_H

//
//	Copyright (c) 2012, 2023 Ricoh Company, Ltd.
//	All rights reserved.
//
