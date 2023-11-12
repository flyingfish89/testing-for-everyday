#pragma once
#include "base.hpp"

class B :public Base<long long,string,int,int>
{
public:
	long long function1(string s);
};