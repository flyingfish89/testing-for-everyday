#include "test.hpp"

vector<vector<int>> B::function9(vector<int> num1, vector<int> num2, int k)
{
    vector<vector<int>> iv;
    if (k == 0)
    {
        return { {0} };
    }
    sort(num1.begin(), num1.end());
    sort(num2.begin(), num2.end());
    multimap<int,vector<int>> mymap1;
    for (int i = 0; i < num1.size(); i++)
    {
        for (int j = 0; j < num2.size(); j++)
        {
            mymap1.insert(make_pair<int, vector<int>>(num1.at(i) + num2.at(j), { num1.at(i),num2.at(j) }));
        }
    }
    auto it = mymap1.begin();
    while (k > 0 && it != mymap1.end())
    {
        iv.push_back(it->second);
        it++;
        k--;
    }
    return iv;
}

