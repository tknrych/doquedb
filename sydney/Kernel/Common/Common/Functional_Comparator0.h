// -*-Mode: C++; tab-width: 4; c-basic-offset: 4;-*-
// vi:set ts=4 sw=4:
//
// Functional_Comparator0.h --
//		Included by Functional_Comparator.h
//		Don't include directly
// 
// Copyright (c) 2007, 2023 Ricoh Company, Ltd.
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

template <class _R_, class _T_>
class _CLASSNAME(Comparator)
{
	typedef _R_ (_T_::* Function)() _CONST;
public:
	_CLASSNAME(Comparator)(Function func) : m_func(func) {}
	bool operator()(_T_* obj1, _T_* obj2)
	{
		return (obj1->*m_func)() < (obj2->*m_func)();
	}
	bool operator()(_T_& obj1, _T_& obj2)
	{
		return (obj1.*m_func)() < (obj2.*m_func)();
	}
	template <class _X_>
	bool operator()(const ObjectPointer<_X_>& obj1, const ObjectPointer<_X_>& obj2)
	{
		return (obj1.get()->*m_func)() < (obj2.get()->*m_func)();
	}
	bool operator()(_T_* obj1, _R_ val)
	{
		return (obj1->*m_func)() < val;
	}
	bool operator()(_R_ val, _T_* obj2)
	{
		return val < (obj2->*m_func)();
	}
	bool operator()(_T_& obj1, _R_ val)
	{
		return (obj1.*m_func)() < val;
	}
	bool operator()(_R_ val, _T_& obj2)
	{
		return val < (obj2.*m_func)();
	}
	template <class _X_>
	bool operator()(const ObjectPointer<_X_>& obj1, _R_ val)
	{
		return (obj1.get()->*m_func)() < val;
	}
	template <class _X_>
	bool operator()(_R_ val, const ObjectPointer<_X_>& obj2)
	{
		return val < (obj2.get()->*m_func)();
	}
private:
	Function m_func;
};

template <class _R_, class _T_>
_CLASSNAME(Comparator)<_R_, _T_>
Comparator(_R_ (_T_::* func)() _CONST)
{
	return _CLASSNAME(Comparator)<_R_, _T_>(func);
}

//
//	Copyright (c) 2007, 2023 Ricoh Company, Ltd.
//	All rights reserved.
//
