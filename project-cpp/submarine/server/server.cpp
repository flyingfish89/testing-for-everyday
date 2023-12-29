#include "httplib.h"
#include <iostream>
#include <cstdlib>
#include <map>
#include "userinfo.h"

using namespace std;

// 记录用户名， 上一次退出时的血量  上一次退出时的得分  该用户的最高分
map<string, user::userinfo> mymap;
string scorename; // 记录当前连接的客户端的ID

void Getmaxscore(const httplib::Request& reg, httplib::Response& res)
{
    string s;
    // 容错处理，客户端上传当前的客户端用户ID，服务端更新当前的连接用户
    scorename.clear();
    scorename.append(reg.path, 8, reg.path.size() - 8);

    // 服务端找到存储的用户最高分信息
    if (mymap.find(scorename) != mymap.end())
    {
        s = std::to_string(mymap[scorename].usermaxscore);
    }
    else
    {
        mymap.insert(make_pair(scorename, user::userinfo()));
        s = std::to_string(mymap[scorename].usermaxscore);
    }

    // 服务端回复最高分信息
    res.set_content(s.c_str(), s.size(), "maxscore");
}
void Setmaxscore(const httplib::Request& reg, httplib::Response& res)
{
    string s;
    //cout << "hello" << endl;
    // 取得客户端请求时上传的数据
    s.append(reg.path, 11, reg.path.size() - 11);
    // 更新服务器存储的该用户的最高分信息
    mymap[scorename].usermaxscore = atoi(s.c_str());
    s = scorename;
    // 最高分有更新，则打印信息
    cout << "恭喜" << s << "创下新纪录: " << mymap[scorename].usermaxscore << endl;
    // 回复OK
    res.set_content("ok", 2, "maxscore");
}
void Setuserblood(const httplib::Request& reg, httplib::Response& res)
{
    string s;
    //cout << "hello" << endl;
    // 取得客户端请求时上传的数据
    s.append(reg.path, 8, reg.path.size() - 8);
    // 设置服务端储存的用户血量信息
    mymap[scorename].userblood = atoi(s.c_str());
    //cout << mymap[scorename].userblood << endl;
    // 回复OK
    res.set_content("ok", 2, "blood");
}
void Getuserblood(const httplib::Request& reg, httplib::Response& res)
{
    string s;
    // 容错处理，取得客户端上传的用户ID信息
    scorename.clear();
    scorename.append(reg.path, 5, reg.path.size() - 5);
    // 新用户OR老用户
    if (mymap.find(scorename) != mymap.end())
    {
        // 老用户
        if (mymap[scorename].userblood == 0)
        {
            // 血量为0，初始化当前的分，更新用户血量
            mymap[scorename].setinituserinfo();
        }
        // 存储用户血量信息
        s = std::to_string(mymap[scorename].userblood);
        if (mymap[scorename].username.size() == 0)
            mymap[scorename].username.append(scorename);
    }
    else
    {
        // 新用户，调用userinfo默认构造函数构建一个新用户对象
        mymap.insert(make_pair(scorename, user::userinfo()));
        s = std::to_string(mymap[scorename].userblood);
        // 设置新用户的ID
        if (mymap[scorename].username.size() == 0)
            mymap[scorename].username.append(scorename);
    }

    // 回复血量的信息给客户端
    res.set_content(s.c_str(), s.size(), "blood");
}

// 该函数一定是在getblood之后，在血量为0的时候，服务端当前的得分情况会一起更新
void Getscore(const httplib::Request& reg, httplib::Response& res)
{
    string s;
    // 容错处理，取得客户端上传的用户ID信息
    scorename.clear();
    scorename.append(reg.path, 5, reg.path.size() - 5);
    if (mymap.find(scorename) != mymap.end())
    {
        // 老用户，获取服务端的用户目前的分情况存储到s
        s = std::to_string(mymap[scorename].userscore);
    }
    else
    {
        // 容错处理，新用户，创建一个新的userinfo对象
        mymap.insert(make_pair(scorename, user::userinfo()));
        s = std::to_string(mymap[scorename].userscore);
    }
    //cout << s << endl;
    // 回复给客户端当前的得分情况
    res.set_content(s.c_str(), s.size(), "score");
}
void Setscore(const httplib::Request& reg, httplib::Response& res)
{
    string s;
    //cout << "hello" << endl;
    // 更新服务端当前得分情况
    s.append(reg.path, 8, reg.path.size() - 8);
    mymap[scorename].userscore = atoi(s.c_str());
    // 回复OK
    res.set_content("ok", 2, "blood");
}
void Setuser(const httplib::Request& reg, httplib::Response& res)
{
    // 设置当前的连接对象
    scorename.clear(); 
    scorename.append(reg.path, 7, reg.path.size() - 7);
    // 回复OK
    res.set_content("ok", 2, "user");
}
int main()
{
    // 测试用户，测试与服务端的连接情况，设置一个默认用户lala
    mymap.insert(make_pair("lala", user::userinfo()));
    mymap["lala"].userblood = 1;
    mymap["lala"].userscore = 3;

    // 初始化一个服务端
    httplib::Server server;

    // 服务端绑定IP地址和端口，有客户端请求的时候需要连接该IP地址和该端口
    server.bind_to_port("192.168.1.19", 9090);
    // 客户端获取最高分的响应函数
    server.Get("maxscore(.*)", Getmaxscore);
    // 客户端设置最高分的响应函数
    server.Get("setmaxscore(.*)", Setmaxscore);
    // 客户端设置当前血量的响应函数
    server.Get("setblood(.*)", Setuserblood);
    // 客户端初始化血量时的响应函数
    server.Get("blood(.*)", Getuserblood);
    // 客户端更新目前得分的响应函数
    server.Get("setscore(.*)", Setscore);
    // 客户端获取目前得分的响应函数
    server.Get("score(.*)", Getscore);
    // 客户端设置服务端当前的连接对象，每一次请求都需要提前设置连接对象
    server.Get("setuser", Setuser);

    // 客户端进入监听状态，判断客户端的请求输入
    server.listen_after_bind();
    return 0;
}