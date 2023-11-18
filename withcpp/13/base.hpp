#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <stack>
#include <list>
#include <deque>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cctype>


using namespace std;
namespace myspace
{
	template<class type1, class type2, class type3, class type4>
	class Base
	{
	public:
		Base();
		~Base();

		//add in 1
		//virtual int function(int a, int b) = 0;
		virtual type1 function1(type2 n) = 0;
		//add in 2
		//virtual type1 function2(type1 s, type2 power, type2 modulo, type2 k, type2 hashValue) = 0;
		//add in 3
		//virtual type2 function3(vector<type2> &staple, vector<type2> &drinks, type2 x) = 0;
		//add in 4
		//virtual type1 function4(vector<type2>& iv) = 0;
		//add in 5
		//virtual type1 function5(vector<type2>& iv, type2 k) = 0;
		//add in 6
		//virtual type1 function6(type2 sequence, type2 word) = 0;
		//add in 10
		//virtual vector<type1> function7(type1 prev, type1 end) = 0;
		//add in 12
		//virtual type1 function8(type1 number) = 0;
	public:
		int a;
		int b;
		list<type3> mylist;			 //flag 0
		vector<type3> myvector;      //flag 1
		multimap<type3, type4> mymap;//flag 2
	};

	template<class type1, class type2, class type3, class type4>
	inline myspace::Base<type1, type2, type3, type4>::Base()
	{
		this->a = 0;
		this->b = 0;
		this->myvector.clear();
		this->myvector.reserve(10);
		mymap.clear();
	}
	template<class type1, class type2, class type3, class type4>
	inline myspace::Base<type1, type2, type3, type4>::~Base()
	{
		this->myvector.clear();
		mymap.clear();
	}
}

