#include "test.hpp"

int main()
{
	B b1;
	vector<char> iv = { '4','4','5','6'};
	b1.function4(iv);
	for (auto it = iv.begin(); it != iv.end(); it++)
	{
		cout << *it << endl;
	}
	return 0;
}