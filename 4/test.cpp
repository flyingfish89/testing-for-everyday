#include "test.hpp"

int B::function(int a, int b)
{
	return 0;
}
void B::function4(vector<char> &iv)
{
	int prev = 0;
	int end = iv.size() - 1;
	char s;
	while (end > prev)
	{
		s = iv.at(prev);
		iv.at(prev) = iv.at(end);
		iv.at(end) = s;
		prev++;
		end--;
	}
}