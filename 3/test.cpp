#include "test.hpp"

int B::getadd(int a, int b)
{
	return 0;
}
string B::generateParenthesis(int n)
{
	return "123";
}
string B::subStrHash(string s, int power, int modulo, int k, int hashValue)
{
	return "123";
}
int B::breakfastNumber(vector<int> &staple, vector<int> &drinks, int x)
{
	int money = 0;
	for (int i = 0; i < staple.size(); i++)
	{
		for (int j = 0; j < drinks.size(); j++)
		{
			if (staple.at(i) + drinks.at(j) <= x)
			{
				money++;
			}
		}
	}
	return money;
}