#pragma once
#include "base.hpp"

class B :public myspace::Base<int,int,int,int>
{
public:
	friend std::istream& operator >> (std::istream& is, B& b1);
	friend std::ostream& operator << (std::ostream& os, B& b1);

	int function10(std::vector<int> nums);
};

// set io
inline std::istream& operator >> (std::istream& is, B& b1)
{
	is >> b1.a;
	b1.b = b1.a + 10;
	return is;
}
inline std::ostream& operator << (std::ostream& os, B& b1)
{
	os << b1.a << std::endl;
	os << b1.b << std::endl;
	return os;
}