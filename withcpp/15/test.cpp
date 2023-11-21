#include "test.hpp"

static bool isbig(int num1, int num2, int num3)
{
    return (num2 > num1 && num2 > num3);
}
int B::function10(std::vector<int> nums)
{
    if (nums.size() < 3)
        return -1;
    for (int i = 1; i < nums.size()-1; i++)
    {
        if (isbig(nums.at(i - 1), nums.at(i), nums.at(i + 1)))
        {
            return i;
        }
    }
    return -1;
}

