#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
using namespace std;

#if 0
void ps(bool flag)
{
    if (flag == true)
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }
}
bool isok(vector<int> &iv, int length, int sum)
{
    int getsum = 0;
    int max = 0;
    for (int i = 0; i < iv.size(); i++)
    {
        if (iv.at(i) >= sum)
        {
            getsum++;
        }
        else
        {
            getsum = 0;
        }
        if (max <= getsum)
        {
            max = getsum;
        }
    }
    if (max >= length)
    {
        return true;
    }
    else return false;
}
int main()
{
    int t;
    cin >> t;
    for (int i = 0; i < t; i++)
    {
        int n, m;
        cin >> n;
        cin >> m;
        vector<int> iv;
        int num;
        for (int i = 0; i < n; i++)
        {
            cin >> num;
            iv.push_back(num);
        }
        for (int i = 0; i < m; i++)
        {
            int num1; int num2;
            cin >> num1; cin >> num2;
            ps(isok(iv, num1, num2));
        }
        iv.clear();
    }
    return 0;

}
#endif