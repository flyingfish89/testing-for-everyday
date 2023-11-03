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
private:
	int a;
	int b;
};