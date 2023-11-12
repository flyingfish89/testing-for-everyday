#include "test.hpp"

static bool isPalinumber(multimap<string, string>::iterator str)
{
	int begin;
	int end;
	if (str->first.size() % 2 == 0 || str->second.size() % 2 == 0)
		return false;
	for (begin = 0, end = str->first.size() - 1; begin < end; begin++, end--)
	{
		if (str->first.at(begin) != str->first.at(end))
			return false;
	}
	for (; begin < end; begin++, end--)
	{
		if (str->first.at(begin) != str->first.at(end))
			return false;
	}
	for (begin = 0, end = str->second.size() - 1; begin < end; begin++, end--)
	{
		if (str->second.at(begin) != str->second.at(end))
			return false;
	}
	for (; begin < end; begin++, end--)
	{
		if (str->second.at(begin) != str->second.at(end))
			return false;
	}
	return true;
}
long long B::function1(string s)
{
	multimap<string, string> mystrmap;
	long long getnum = 0;
	for (int i = 1; i < s.size(); i++)
	{
		mystrmap.insert(make_pair(s.substr(0, i), s.substr(i)));
	}
	multimap<string, string>::iterator it = mystrmap.begin();
	while (it!=mystrmap.end())
	{
		if (!isPalinumber(it))
		{
			it = mystrmap.erase(it);
		}
		else
		{
			it++;
		}
	}
	for (pair<string, string> it : mystrmap)
	{
		if (it.first.size() * it.second.size() > getnum)
		{
			getnum = it.first.size() * it.second.size();
		}
	}
	return getnum;
}
