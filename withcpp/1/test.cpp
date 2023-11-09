#include <stack>
#include "test.hpp"

static bool getstringok(string s)
{
	stack<char> st;
	for (int i = 0; i < s.size(); i++)
	{
		if (s.at(i) == '(')
		{
			st.push(1);
		}
		else if (s.at(i) == ')')
		{
			if (st.empty())
			{
				return false;
			}
			st.pop();
		}
		else return false;
	}
	if (st.empty()) return true;
	return false;
}
static void addstring(vector<string> &vs, string &s, char c, int n)
{
	s.push_back(c);
	if (s.size() < n)
	{
		addstring(vs, s, '(', n);
		addstring(vs, s, ')', n);
	}
	else if (s.size() == n)
	{
		if (getstringok(s))
		{
			vs.push_back(s);
		}
	}
	s.pop_back();
}
vector<string> B::generateParenthesis(int n)
{
	vector<string> vs;
	string s;
	addstring(vs, s, '(', 2 * n);
	for (int i = 0; i < vs.size(); i++)
	{
		cout << vs.at(i) << endl;
	}
	return vs;
}
int B::getadd(int a, int b)
{
	return a + b;
}