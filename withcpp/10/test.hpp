#pragma once
#include "base.hpp"

class B :public Base<int,int,int,int>
{
public:
	B& getvalue();
	bool setvalue(int x, int y);
	friend istream& operator >> (istream& is, B& b1);
	friend ostream& operator << (ostream& os, B& b1);

	vector<int> function7(int prev, int end);
};

// set number value read and set function
inline B& B::getvalue()
{
	return *this;
}
inline bool B::setvalue(int x, int y)
{
	this->a = x;
	this->b = y;
	if (this->a != x || this->b != y)
	{
		return false;
	}
	return true;
}

// set io
inline istream& operator >> (istream& is, B& b1)
{
	is >> b1.getvalue().a;
	b1.getvalue().b = b1.getvalue().a + 10;
	return is;
}
inline ostream& operator << (ostream& os, B& b1)
{
	os << b1.a << endl;
	os << b1.b << endl;
	return os;
}