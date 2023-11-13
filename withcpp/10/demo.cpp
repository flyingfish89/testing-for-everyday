#include "test.hpp"

int main(int argc, char *argv[])
{
	B b1;
	B& b = b1;
	vector<int> iv = b1.function7(21, 23);
	for (auto it : iv)
	{
		cout << it << endl;
	}
	
	return 0;
}