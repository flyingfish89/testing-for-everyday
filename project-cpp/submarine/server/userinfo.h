#include <iostream>
#include <string>

// 用户信息类对象
namespace user
{
    class userinfo
    {
    public:
        userinfo();
        void setinituserinfo();
    public:
        std::string username; //用户ID
        int userblood; // 用户血量
        int userscore; // 用户目前的分
        int usermaxscore; // 用户最高得分
    };
}

