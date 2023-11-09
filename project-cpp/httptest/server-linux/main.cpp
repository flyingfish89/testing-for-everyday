#include"./httplib/httplib.h"
#include<iostream>
#include<string>
#include<sys/types.h>
#include<dirent.h>
#include <sys/stat.h> 
#include"./getmethod/getmethod.hpp"
using namespace std;
using namespace httplib;


int main()
{
    if (opendir("./data") == nullptr)
	{
		mkdir("./data", 0777);
	}
	if (opendir("./photo") == nullptr)
	{
		mkdir("./photo", 0777);
	}

	photo1::getphotomanage()->Initphotomanage();

	Server server;
	server.set_read_timeout(50, 0); // 50 seconds
    server.set_write_timeout(50, 0); // 50 seconds
    server.set_idle_interval(0, 10000000); // 10000 milliseconds


	server.Get("photomenu",photomenu);
	server.Get("(.*).png",photo);
    server.Get("(.*).jpg",photo);
	server.Get("(.*).mp4",photo);
	server.Get("play1",play1);
	server.Get("clear",clear);
	server.Get("up",updateplay1);
	server.Get("(\\d).(\\d)",setpos);
	//server.listen("192.168.1.30", 8080);
	return 0;
}