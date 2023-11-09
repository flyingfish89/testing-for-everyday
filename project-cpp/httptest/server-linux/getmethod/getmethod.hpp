#pragma once
#include <iostream>
#include <sys/types.h>
#include <string>
#include <dirent.h>
#include "../manage/photomanage.hpp"
#include "../httplib/httplib.h"
#include "../fileutil.h"
#include "../cJSON/cJSON.h"
#include "../play/play1/play1.hpp"

using namespace httplib;
using namespace std;
int num = 0;

void photo(const httplib::Request &reg, httplib::Response &res);     //获取单个照片
void photomenu(const httplib::Request &reg, httplib::Response &res); //获取照片菜单
void play1(const httplib::Request &reg, httplib::Response &res);      //playone
void updateplay1(const httplib::Request &reg, httplib::Response &res); //获取更新后的状态
void setpos(const httplib::Request &reg, httplib::Response &res);     //设置位置
void clear(const httplib::Request &reg, httplib::Response &res);       //清空表格



void photo(const httplib::Request &reg, httplib::Response &res)
{
    cout<<"enter photo"<<endl;
    num++;
    cout<<num<<endl;

    string s = reg.path;
    if(photo1::getphotomanage()->getonefile(s))
    {
        FileUtil feil(s);
        feil.Read(&s);
    }
    else
    {
        s = "no";
    }
    
    res.set_content(s.c_str(), s.size(), "photo");
}
void photomenu(const httplib::Request &reg, httplib::Response &res)
{
    string s;
    photo1::getphotomanage()->getallfile(s);
    res.set_content(s.c_str(),s.size(),"photo");
}
void play1(const httplib::Request &reg, httplib::Response &res)
{
    string s;
    player1::getplayer1()->init();
    player1::getplayer1()->getstr(s);
    res.set_content(s.c_str(),s.size(),"player");
}
void updateplay1(const httplib::Request &reg, httplib::Response &res)
{
    cout<<"enter update player1"<<endl;
    string s;
    player1::getplayer1()->getstr(s);
    res.set_content(s.c_str(),s.size(),"player");
}
void setpos(const httplib::Request &reg, httplib::Response &res)
{
    cout<<"enter setpos:"<<reg.path<<endl;
    string s= reg.path;
    int x = s[0] - '0';
    int y = s[2] - '0';
    if(player1::getplayer1()->update(y-1,x-1,1))
    {
        //cout<<"setpos ok"<<endl;
        if(player1::getplayer1()->iswin(1))
        {
            s = "1";
            res.set_content(s.c_str(),s.size(),"player");
            return;
        }
        player1::getplayer1()->getstr(s);
        cout<<s<<endl;
        while(1)
        {
            cout<<"X:";
            cin>>x;
            cout<<"Y:";
            cin>>y;
            if(player1::getplayer1()->update(y-1,x-1,2))
            {
                break;
            }
            else
            {
                cout<<"input again"<<endl;
            }
         
        }
        if(player1::getplayer1()->iswin(2))
        {
            s = "2";
            res.set_content(s.c_str(),s.size(),"player");
            return;
        }
        s = "4";
        cout<<"ok:"<<s<<endl;
        res.set_content(s.c_str(),s.size(),"player");
        return;
    }
    else
    {
        s = "3";
        res.set_content(s.c_str(),s.size(),"player");
        return;
    }
}
void clear(const httplib::Request &reg, httplib::Response &res)
{
    cout<<"enter clear"<<endl;
    player1::getplayer1()->clear();
}