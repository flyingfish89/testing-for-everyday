#include "test.hpp"

int B::function4(vector<int>& iv)
{
	int index = 0;
	for (; index < iv.size(); index++)
	{
		if (index % 10 == iv.at(index))
		{
			break;
		}
		if (index == iv.size() - 1)
		{
			index = -1;
			break;
		}
	}
	return index;
}
