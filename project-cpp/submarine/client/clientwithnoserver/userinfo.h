#include <iostream>
#include <string>
#include <fstream>
#include <map>
using namespace std;

class User
{
public:
    User();
    User(std::string name1);
public:
    std::string name;
    int blood;
    int nowscore;
    int maxscore;
};

User::User()
{
    name.append(" ");
    blood = 5;
    nowscore = 0;
    maxscore = 0;
}
User::User(std::string name1)
{
    name = name1;
    blood = 5;
    nowscore = 0;
    maxscore = 0;
}
void saveinfo(std::string path, std::map<std::string, User> user)
{
    ofstream ofs1(path, std::ios::binary);
    for (auto it = user.begin(); it != user.end(); it++)
    {
        if (it->second.blood == 0)
        {
            it->second.blood = 5;
            it->second.nowscore = 0;
        }
        ofs1 << it->second.name << endl;
        ofs1 << it->second.blood << endl;
        ofs1 << it->second.nowscore << endl;
        ofs1 << it->second.maxscore << endl;
    }
    ofs1.close();
}
void inituserinfo(std::string path, std::map<std::string, User>& user)
{
    ifstream ofs1(path, std::ios::binary);
    while (!ofs1.eof())
    {
        string s;

        ofs1 >> s;
        if (s.size() == 0)
        {
            continue;
        }
        if (user.find(s) != user.end())
        {
            ofs1 >> user[s].blood;
            ofs1 >> user[s].nowscore;
            ofs1 >> user[s].maxscore;
        }
        else
        {
            user.insert(make_pair(s, User(s)));
            ofs1 >> user[s].blood;
            ofs1 >> user[s].nowscore;
            ofs1 >> user[s].maxscore;
        }
    }
    ofs1.close();
}
