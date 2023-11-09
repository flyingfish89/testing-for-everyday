#pragma once
#include "base.hpp"

class B :public Base<int,int,int,int>
{
public:
	int function4(vector<int>& iv);
};