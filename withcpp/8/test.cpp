#include "test.hpp"

bool B::function1(int n)
{
	vector<bool> iswin{0,1};
	for (int i = 2; i <= n; i++)
	{
		bool flag = 0;
		for (int j = 1; j * j <= i; j++)
		{
			if (iswin.at(i - j * j) == false)
			{
				flag = 1;
				iswin.push_back(1);
				break;
			}
		}
		if (flag == 0)
		{
			iswin.push_back(0);
		}
	}
	return iswin.at(n);
}
