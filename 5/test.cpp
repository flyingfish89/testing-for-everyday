#include "test.hpp"

static bool mysort(string s1, string s2)
{
	return s1.compare(s2);
}

string B::function5(vector<int> &iv, int k)
{
	k -= 2;
	string s(iv[1],'H');
	char c;
	s.append(iv[0],'V');
	int vindex = iv[1];
	int index = vindex - 1;
	while (1)
	{
		if (k < 0)
		{
			break;
		}

		c = s[vindex - 1];
		s[vindex - 1] = s[vindex];
		s[vindex] = c;
		k--;
		vindex++;
		if (vindex >= s.size())
		{
			vindex = index;
			index--;
			if (vindex <= 0)
			{
				break;
			}
		}
	}
	return s;
}