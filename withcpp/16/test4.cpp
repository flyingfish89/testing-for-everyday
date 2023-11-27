#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
using namespace std;

#if 0
int calculateNotSam(int a, int b)
{
	int num = 0;
	int count = 0;
	num = a ^ b;
	while (num)
	{
		count++;
		num = num & (num - 1);
	}
	return count;
}
int main()
{
	int n;
	cin >> n;
	int arr[2];
	int sum = 0;
	for (int i = 0; i < n; i++)
	{
		cin >> arr[0];  //m
		cin >> arr[1];  //k
		for (int j = 0; j < arr[0]; j++)
		{
			for (int k = j+1; k <= arr[0]; k++)
			{
				if (calculateNotSam(j, k) <= arr[1])
				{
					sum++;
				}
			}
		}
		cout << sum<<endl;
		sum = 0;
	}
	return 0;
}
#endif