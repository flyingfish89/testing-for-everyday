#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include <list>
#include <deque>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <cstdio>
#include <cstdlib>

using namespace std;

template<class type1, class type2, class type3, class type4>
class Base
{
public:
	//add in 1
	virtual int function(int a, int b) = 0;
	//virtual type1 function1(type2 n) = 0;
	//add in 2
	//virtual type1 function2(type1 s, type2 power, type2 modulo, type2 k, type2 hashValue) = 0;
	//add in 3
	//virtual type2 function3(vector<type2> &staple, vector<type2> &drinks, type2 x) = 0;
	//add in 4
	virtual type1 function4(vector<type2>& iv) = 0;
private:
	int a;
	int b;
};