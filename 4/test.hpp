#pragma once
#include "base.hpp"

class B :public Base<void,char,int,int>
{
public:
	int function(int a, int b);
	void function4(vector<char> &iv);
	//string function2(string s, int power, int modulo, int k, int hashValue);
	//int function3(vector<int> &staple, vector<int> &drinks, int x);
};