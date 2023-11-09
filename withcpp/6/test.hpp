#pragma once
#include "base.hpp"

class B :public Base<int,string,int,int>
{
public:
	int function6(string sequence, string word);
};