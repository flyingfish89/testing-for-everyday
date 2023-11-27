#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <string.h>
#include <algorithm>
using namespace std;

#if 0
int main()
{
    int n;
    int num1;
    int num2;
    cin >> n;
    bool a[6];
    memset(a, 0, sizeof(a));
    for (int i = 0; i < n; i++)
    {
        cin >> num1;
        for (int j = 0; j < num1; j++)
        {
            cin >> num2;
            a[num2] = true;
        }
        for (int j = 1; j < 5; j++)
        {
            if (a[j] == false)
            {
                cout << j << " ";
            }
        }
        if (a[5] == false) cout << 5;
        cout << endl;
        memset(a, 0, sizeof(a));
    }
    
    return 0;
}
#endif