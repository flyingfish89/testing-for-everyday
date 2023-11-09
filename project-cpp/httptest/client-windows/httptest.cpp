#include"httplib.h"
#include<iostream>
#include<io.h>
#include<direct.h>
#include<string>
#include"fileutil.h"
#include<Windows.h>
using namespace std;
using namespace httplib;

void menu()
{
	cout << "--------------------------------------" << endl;
	cout << "---------------菜单-------------------" << endl;
	cout << "-------------1.查看照片---------------" << endl;
	cout << "-------------2.玩三子棋---------------" << endl;
	cout << "-------------3.打麻将-----------------" << endl;
	cout << "-------------4.退出-------------------" << endl;
	cout << "---------------菜单-------------------" << endl;
	cout << "--------------------------------------" << endl;
}
int main()
{
	Client  client("192.168.253.3", 8080);
	client.set_keep_alive(true);
	client.set_connection_timeout(0, 30000000); // 30000 milliseconds
	client.set_read_timeout(200, 0); // 200 seconds
	client.set_write_timeout(50, 0); // 50 seconds
	
	if (access("E:/data", 0) == -1)
	{
		mkdir("E:/data");
	}
	
	while (1)
	{
		system("cls");
		menu();
		int input = 0;
		cout << "输入:";
		cin >> input;

		if (input == 1)
		{
			string s;
			while (1)
			{
				cout << "--------------------------------------" << endl;
				auto it = client.Get("photomenu");
				cout << it->body << endl;
				cout << "----------输入你想获得的东西----------" << endl;
				cin >> s;
				if (s.compare("quit") == 0)
				{
					break;
				}
				if (s.find(".jpg") != string::npos || s.find(".png") != string::npos || s.find(".mp4") != string::npos)
				{
					it = client.Get(s);
					s = "E:/data/" + s;

					if (it != nullptr)
					{
						if (it->body.compare("no") == 0)
						{
							cout << "--------------------------------------" << endl;
							cout << "404 not found" << endl;
						}
						else
						{
							FileUtil fil(s);
							cout << "--------------------------------------" << endl;
							cout << "写入到E:\data文件夹" << endl;
							fil.Write(it->body);
						}
					}
				}
				else
				{
					cout << "格式不正确" << endl;
				}
				
			}
		}
		else if(input == 2)
		{
			string s;
			int x = 0, y = 0;
			auto it = client.Get("play1");
			cout << it->body << endl;
			while (1)
			{
				s.clear();

				cout << "X:";
				cin >> x;
				if (x == -1)
				{
					break;
				}
				cout << "Y:";
				cin >> y;
				s += ('0' + x); s += (','); s += ('0' + y);
				//cout << s << endl;
				it = client.Get(s);
				while(it == nullptr)
				{
					it = client.Get(s);
				}
				//cout << "s:" << s << "get:" << it->body << endl;
				if (it->body.compare("2") == 0)
				{
					cout << "你个垃圾，我都赢不了" << endl;
					it = client.Get("up");
					cout << it->body << endl;
					client.Get("clear");
				}
				else if (it->body.compare("1") == 0)
				{
					cout << "竟然让你侥幸赢了" << endl;
					it = client.Get("up");
					cout << it->body << endl;
					client.Get("clear");
				}
				else if (it->body.compare("3") == 0)
				{
					cout << "该位置有东西了" << endl;
					cout << "重新下：" << endl;
				}
				else
				{
					cout << "--------------------------------------" << endl;
					//cout << "enter getupdate" << endl;
					it = client.Get("up");
					cout << it->body << endl;
					cout << "----------输入你想移动的位置----------" << endl;
				}
			}
		}
		else if(input == 3)
		{
			while (1)
			{
				break;
			}
		}
		else if (input == 4)
		{
			break;
		}
		else
		{
			cout << "无操作" << endl;
		}
	}
	return 0;
}