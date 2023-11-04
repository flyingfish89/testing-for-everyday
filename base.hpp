#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

template<class type1, class type2, class type3, class type4>
class Base
{
public:
	virtual int getadd(int a, int b) = 0;
	virtual type1 generateParenthesis(type2 n) = 0;
	//add in 2
	virtual type1 subStrHash(type1 s, type2 power, type2 modulo, type2 k, type2 hashValue) = 0;
	//add in 3
	virtual type2 breakfastNumber(vector<type2> &staple, vector<type2> &drinks, type2 x) = 0;
private:
	int a;
	int b;
};