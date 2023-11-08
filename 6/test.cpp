#include "test.hpp"

int B::function6(string sequence, string word)
{
	int sum = 0;
	string s = word;
	while (sequence.find(s) != string::npos)
	{
		s.append(word);
		sum++;
	}
	return sum;
}
