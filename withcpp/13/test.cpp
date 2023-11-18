#include "test.hpp"

int B::function1(string n)
{
    vector<bool> num(10, false);
    for (char c : n)
    {
        if (isdigit(c))
        {
            num.at(c - '0') = true;
        }
    }
    bool flag = false;
    for (int it = 9; it >= 0; it--)
    {
        if (num.at(it) == true)
        {
            if (flag == false)
            {
                flag = true;
            }
            else
            {
                return it;
            }
        }
    }
    return -1;
}

