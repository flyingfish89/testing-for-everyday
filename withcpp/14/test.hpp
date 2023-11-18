#pragma once
#include "base.hpp"

class B :public myspace::Base<int,int,int,int>
{
public:
	friend istream& operator >> (istream& is, B& b1);
	friend ostream& operator << (ostream& os, B& b1);

	vector<vector<int>> function9(vector<int> num1, vector<int> num2, int k);
};

// set io
inline istream& operator >> (istream& is, B& b1)
{
	is >> b1.a;
	b1.b = b1.a + 10;
	return is;
}
inline ostream& operator << (ostream& os, B& b1)
{
	os << b1.a << endl;
	os << b1.b << endl;
	return os;
}