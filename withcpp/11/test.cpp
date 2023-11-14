#include "test.hpp"

static bool isdingNumber(int number)
{
	int index = number;
	int getnum = 0;
	while (number != 0)
	{
		if (index == 0) break;
		getnum = index % 10;
		if (getnum == 0) return false;
		index /= 10;
		if (number % getnum != 0) return false;
	}
	return true;
}
vector<int> B::function7(int prev, int end)
{
	vector<int> iv;
	for (; prev <= end; prev++)
	{
		if (isdingNumber(prev))
		{
			iv.push_back(prev);
		}
	}
	return iv;
}

