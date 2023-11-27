#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
using namespace std;

vector<string> C4 =
{
    "###",
    "###",
    "###",
    "###",
    "---",
    "###",
    "---",
    "###",
    "---",
    "###",
    "---",
    "###",
    "---",
    "###",
    "-*-",
};
vector<string> D4 =
{
    "###",
    "###",
    "###",
    "###",
    "---",
    "###",
    "---",
    "###",
    "---",
    "###",
    "---",
    "###",
    "---",
    "#*#",
    "###",
};
vector<string> E4 =
{
    "###",
    "###",
    "###",
    "###",
    "---",
    "###",
    "---",
    "###",
    "---",
    "###",
    "---",
    "###",
    "-*-",
    "###",
    "###",
};

vector<string> F4 =
{
    "###",
    "###",
    "###",
    "###",
    "---",
    "###",
    "---",
    "###",
    "---",
    "###",
    "---",
    "#*#",
    "---",
    "###",
    "###",
};
vector<string> G4 =
{
    "###",
    "###",
    "###",
    "###",
    "---",
    "###",
    "---",
    "###",
    "---",
    "###",
    "-*-",
    "###",
    "---",
    "###",
    "###",
};
vector<string> A4 =
{
    "###",
    "###",
    "###",
    "###",
    "---",
    "###",
    "---",
    "###",
    "---",
    "#*#",
    "---",
    "###",
    "---",
    "###",
    "###",
};
vector<string> B4 =
{
    "###",
    "###",
    "###",
    "###",
    "---",
    "###",
    "---",
    "###",
    "-*-",
    "###",
    "---",
    "###",
    "---",
    "###",
    "###",
};
vector<string> C5 =
{
    "###",
    "###",
    "###",
    "###",
    "---",
    "###",
    "---",
    "#*#",
    "---",
    "###",
    "---",
    "###",
    "---",
    "###",
    "###",
};
vector<string> D5 =
{
    "###",
    "###",
    "###",
    "###",
    "---",
    "###",
    "-*-",
    "###",
    "---",
    "###",
    "---",
    "###",
    "---",
    "###",
    "###",
};
vector<string> E5 =
{
    "###",
    "###",
    "###",
    "###",
    "---",
    "#*#",
    "---",
    "###",
    "---",
    "###",
    "---",
    "###",
    "---",
    "###",
    "###",
};
vector<string> F5 =
{
    "###",
    "###",
    "###",
    "###",
    "-*-",
    "###",
    "---",
    "###",
    "---",
    "###",
    "---",
    "###",
    "---",
    "###",
    "###",
};
vector<string> G5 =
{
    "###",
    "###",
    "###",
    "#*#",
    "---",
    "###",
    "---",
    "###",
    "---",
    "###",
    "---",
    "###",
    "---",
    "###",
    "###",
};
vector<string> A5 =
{
    "###",
    "###",
    "-*-",
    "###",
    "---",
    "###",
    "---",
    "###",
    "---",
    "###",
    "---",
    "###",
    "---",
    "###",
    "###",
};
vector<string> B5 =
{
    "###",
    "#*#",
    "---",
    "###",
    "---",
    "###",
    "---",
    "###",
    "---",
    "###",
    "---",
    "###",
    "---",
    "###",
    "###",
};
vector<string> C6 =
{
    "-*-",
    "###",
    "---",
    "###",
    "---",
    "###",
    "---",
    "###",
    "---",
    "###",
    "---",
    "###",
    "---",
    "###",
    "###",
};

int main()
{
    map<string, vector<string>> mymap;
    mymap.insert(make_pair("C4", C4));
    mymap.insert(make_pair("D4", D4));
    mymap.insert(make_pair("E4", E4));
    mymap.insert(make_pair("F4", F4));
    mymap.insert(make_pair("G4", G4));
    mymap.insert(make_pair("A4", A4));
    mymap.insert(make_pair("B4", B4));
    mymap.insert(make_pair("C5", C5));
    mymap.insert(make_pair("D5", D5));
    mymap.insert(make_pair("E5", E5));
    mymap.insert(make_pair("F5", F5));
    mymap.insert(make_pair("G5", G5));
    mymap.insert(make_pair("A5", A5));
    mymap.insert(make_pair("B5", B5));
    mymap.insert(make_pair("C6", C6));
    string s1 = "C4D4E4F4G4A4B4C5D5E5F5G5A5B5C6";
    int n;
    cin >> n;
    char c;
    vector<string> sv;
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> c;
        s.push_back(c);
        cin >> c;
        s.push_back(c);
        sv.push_back(s);
        s.clear();
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < sv.size(); j++)
        {
            cout << mymap.find(sv.at(j))->second.at(i);
        }
        cout << endl;
    }
    return 0;
}