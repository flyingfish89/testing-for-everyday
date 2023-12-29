#include "userinfo.h"

// 用户信息的默认构造函数，血量为5，目前的分，最高得分均初始化为0
user::userinfo::userinfo()
{
    userblood = 5; // 用户血量
    userscore = 0; // 用户目前得分
    usermaxscore = 0; // 用户最高得分
}

// 用户血量掉为0时的恢复默认函数
void user::userinfo::setinituserinfo()
{
    userblood = 5;  // 更新用户血量
    userscore = 0;  // 更新用户当前的得分
}