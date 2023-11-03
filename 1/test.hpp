#pragma once
#include "base.hpp"

class B :public Base<vector<string>,int,int,int>
{
public:
	int getadd(int a, int b);
	vector<string> generateParenthesis(int n);
};