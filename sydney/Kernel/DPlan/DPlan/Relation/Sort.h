// -*-Mode: C++; tab-width: 4; c-basic-offset: 4;-*-
// vi:set ts=4 sw=4:
//
// Relation/Sort.h --
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

#ifndef __SYDNEY_DPLAN_RELATION_SORT_H
#define __SYDNEY_DPLAN_RELATION_SORT_H

#include "DPlan/Relation/Module.h"

#include "Plan/Interface/IRelation.h"

_SYDNEY_BEGIN
_SYDNEY_DPLAN_BEGIN
_SYDNEY_DPLAN_RELATION_BEGIN

////////////////////////////////////
//	CLASS
//	DPlan::Relation::Sort -- Interface implementation for sort
//
//	NOTES
class Sort
	: public Plan::Interface::IRelation
{
public:
	typedef Plan::Interface::IRelation Super;
	typedef Sort This;

	// costructor
	static This* create(Opt::Environment& cEnvironment_,
						Plan::Order::Specification* pOrder_,
						Plan::Interface::IRelation* pOperand_);
	// destructor
	virtual ~Sort() {}

protected:
	// costructor
	Sort();

private:
};

_SYDNEY_DPLAN_RELATION_END
_SYDNEY_DPLAN_END
_SYDNEY_END

#endif // __SYDNEY_DPLAN_RELATION_SORT_H

//
//	Copyright (c) 2012, 2023 Ricoh Company, Ltd.
//	All rights reserved.
//
