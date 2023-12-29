#include "httplib.h"
#include <iostream>
#include <cstdlib>
#include <map>
#include "userinfo.h"

using namespace std;

// ��¼�û����� ��һ���˳�ʱ��Ѫ��  ��һ���˳�ʱ�ĵ÷�  ���û�����߷�
map<string, user::userinfo> mymap;
string scorename; // ��¼��ǰ���ӵĿͻ��˵�ID

void Getmaxscore(const httplib::Request& reg, httplib::Response& res)
{
    string s;
    // �ݴ����ͻ����ϴ���ǰ�Ŀͻ����û�ID������˸��µ�ǰ�������û�
    scorename.clear();
    scorename.append(reg.path, 8, reg.path.size() - 8);

    // ������ҵ��洢���û���߷���Ϣ
    if (mymap.find(scorename) != mymap.end())
    {
        s = std::to_string(mymap[scorename].usermaxscore);
    }
    else
    {
        mymap.insert(make_pair(scorename, user::userinfo()));
        s = std::to_string(mymap[scorename].usermaxscore);
    }

    // ����˻ظ���߷���Ϣ
    res.set_content(s.c_str(), s.size(), "maxscore");
}
void Setmaxscore(const httplib::Request& reg, httplib::Response& res)
{
    string s;
    //cout << "hello" << endl;
    // ȡ�ÿͻ�������ʱ�ϴ�������
    s.append(reg.path, 11, reg.path.size() - 11);
    // ���·������洢�ĸ��û�����߷���Ϣ
    mymap[scorename].usermaxscore = atoi(s.c_str());
    s = scorename;
    // ��߷��и��£����ӡ��Ϣ
    cout << "��ϲ" << s << "�����¼�¼: " << mymap[scorename].usermaxscore << endl;
    // �ظ�OK
    res.set_content("ok", 2, "maxscore");
}
void Setuserblood(const httplib::Request& reg, httplib::Response& res)
{
    string s;
    //cout << "hello" << endl;
    // ȡ�ÿͻ�������ʱ�ϴ�������
    s.append(reg.path, 8, reg.path.size() - 8);
    // ���÷���˴�����û�Ѫ����Ϣ
    mymap[scorename].userblood = atoi(s.c_str());
    //cout << mymap[scorename].userblood << endl;
    // �ظ�OK
    res.set_content("ok", 2, "blood");
}
void Getuserblood(const httplib::Request& reg, httplib::Response& res)
{
    string s;
    // �ݴ���ȡ�ÿͻ����ϴ����û�ID��Ϣ
    scorename.clear();
    scorename.append(reg.path, 5, reg.path.size() - 5);
    // ���û�OR���û�
    if (mymap.find(scorename) != mymap.end())
    {
        // ���û�
        if (mymap[scorename].userblood == 0)
        {
            // Ѫ��Ϊ0����ʼ����ǰ�ķ֣������û�Ѫ��
            mymap[scorename].setinituserinfo();
        }
        // �洢�û�Ѫ����Ϣ
        s = std::to_string(mymap[scorename].userblood);
        if (mymap[scorename].username.size() == 0)
            mymap[scorename].username.append(scorename);
    }
    else
    {
        // ���û�������userinfoĬ�Ϲ��캯������һ�����û�����
        mymap.insert(make_pair(scorename, user::userinfo()));
        s = std::to_string(mymap[scorename].userblood);
        // �������û���ID
        if (mymap[scorename].username.size() == 0)
            mymap[scorename].username.append(scorename);
    }

    // �ظ�Ѫ������Ϣ���ͻ���
    res.set_content(s.c_str(), s.size(), "blood");
}

// �ú���һ������getblood֮����Ѫ��Ϊ0��ʱ�򣬷���˵�ǰ�ĵ÷������һ�����
void Getscore(const httplib::Request& reg, httplib::Response& res)
{
    string s;
    // �ݴ���ȡ�ÿͻ����ϴ����û�ID��Ϣ
    scorename.clear();
    scorename.append(reg.path, 5, reg.path.size() - 5);
    if (mymap.find(scorename) != mymap.end())
    {
        // ���û�����ȡ����˵��û�Ŀǰ�ķ�����洢��s
        s = std::to_string(mymap[scorename].userscore);
    }
    else
    {
        // �ݴ������û�������һ���µ�userinfo����
        mymap.insert(make_pair(scorename, user::userinfo()));
        s = std::to_string(mymap[scorename].userscore);
    }
    //cout << s << endl;
    // �ظ����ͻ��˵�ǰ�ĵ÷����
    res.set_content(s.c_str(), s.size(), "score");
}
void Setscore(const httplib::Request& reg, httplib::Response& res)
{
    string s;
    //cout << "hello" << endl;
    // ���·���˵�ǰ�÷����
    s.append(reg.path, 8, reg.path.size() - 8);
    mymap[scorename].userscore = atoi(s.c_str());
    // �ظ�OK
    res.set_content("ok", 2, "blood");
}
void Setuser(const httplib::Request& reg, httplib::Response& res)
{
    // ���õ�ǰ�����Ӷ���
    scorename.clear(); 
    scorename.append(reg.path, 7, reg.path.size() - 7);
    // �ظ�OK
    res.set_content("ok", 2, "user");
}
int main()
{
    // �����û������������˵��������������һ��Ĭ���û�lala
    mymap.insert(make_pair("lala", user::userinfo()));
    mymap["lala"].userblood = 1;
    mymap["lala"].userscore = 3;

    // ��ʼ��һ�������
    httplib::Server server;

    // ����˰�IP��ַ�Ͷ˿ڣ��пͻ��������ʱ����Ҫ���Ӹ�IP��ַ�͸ö˿�
    server.bind_to_port("192.168.1.19", 9090);
    // �ͻ��˻�ȡ��߷ֵ���Ӧ����
    server.Get("maxscore(.*)", Getmaxscore);
    // �ͻ���������߷ֵ���Ӧ����
    server.Get("setmaxscore(.*)", Setmaxscore);
    // �ͻ������õ�ǰѪ������Ӧ����
    server.Get("setblood(.*)", Setuserblood);
    // �ͻ��˳�ʼ��Ѫ��ʱ����Ӧ����
    server.Get("blood(.*)", Getuserblood);
    // �ͻ��˸���Ŀǰ�÷ֵ���Ӧ����
    server.Get("setscore(.*)", Setscore);
    // �ͻ��˻�ȡĿǰ�÷ֵ���Ӧ����
    server.Get("score(.*)", Getscore);
    // �ͻ������÷���˵�ǰ�����Ӷ���ÿһ��������Ҫ��ǰ�������Ӷ���
    server.Get("setuser", Setuser);

    // �ͻ��˽������״̬���жϿͻ��˵���������
    server.listen_after_bind();
    return 0;
}