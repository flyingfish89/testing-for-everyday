#pragma once
#include "base.hpp"

class B :public myspace::Base<int,int,int,string>
{
public:
	friend istream& operator >> (istream& is, B& b1);
	friend ostream& operator << (ostream& os, B& b1);

	vector<int> function7(int prev, int end);
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