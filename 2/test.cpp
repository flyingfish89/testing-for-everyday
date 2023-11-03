#include "test.hpp"

int B::getadd(int a, int b)
{
	return 0;
}
string B::generateParenthesis(int n)
{
	return "123";
}
static long long getpower(int num, int power)
{
	long long ret = 1;
	for (int i = 0; i < power; i++)
	{
		ret *= num;
	}
	return ret;
}
bool IsHashNum(string s, int power, int modulo, int hashValue)
{
	long long num = 0;
	for (int i = 0; i < s.size(); i++)
	{
		num += (s.at(i)-'a' + 1) * getpower(power, i);
	}
	if (num % modulo == hashValue)
	{
		return true;
	}
	return false;
}
string B::subStrHash(string s, int power, int modulo, int k, int hashValue)
{
	string ret;
	ret = s.substr(0, k);
	for (int i = k - 1; i < s.size(); i++)
	{
		if (IsHashNum(ret, power, modulo, hashValue))
		{
			break;
		}
		ret.erase(0,1);
		ret.push_back(s[i]);
	}
	if (!ret.empty())
		return ret;
	else return s;
}