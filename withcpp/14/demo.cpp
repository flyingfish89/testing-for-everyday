#include "test.hpp"

int main(int argc, char *argv[])
{
	vector<vector<int>> iv;
	B b1;
	iv = b1.function9({ 1,3,2,4,5,6 }, { 1,5,3,4,6 }, 10);
	for (int i = 0; i < iv.size(); i++)
	{
		std::cout << iv.at(i).at(0);
		std::cout << "---" << iv.at(i).at(1) << std::endl;
	}
	return 0;
}