#pragma once
#include "base.hpp"

class B :public Base<bool,int,int,int>
{
public:
	bool function1(int n);
};