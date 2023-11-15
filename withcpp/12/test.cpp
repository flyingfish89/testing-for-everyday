#include "test.hpp"

int B::function8(int number)
{
    int getnum = 0;
    if (number % 10 >= 5)
    {
        getnum = 10 - (number % 10);
    }
    else
    {
        getnum -= number % 10;
    }
    getnum = number + (getnum);
    return 100 - getnum;
}

