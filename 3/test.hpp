#pragma once
#include "base.hpp"

class B :public Base<string,int,int,int>
{
public:
	int getadd(int a, int b);
	string generateParenthesis(int n);
	string subStrHash(string s, int power, int modulo, int k, int hashValue);
	int breakfastNumber(vector<int> &staple, vector<int> &drinks, int x);
};