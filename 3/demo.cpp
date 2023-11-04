#include "test.hpp"

int main()
{
	B b1;
	vector<int> staple = { 10, 20, 5 }, drinks = { 5, 5, 2 }; int x = 15;
	cout << b1.breakfastNumber(staple, drinks, x) << endl;
	return 0;
}