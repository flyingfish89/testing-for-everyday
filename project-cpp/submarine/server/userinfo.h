#include <iostream>
#include <string>

// �û���Ϣ�����
namespace user
{
    class userinfo
    {
    public:
        userinfo();
        void setinituserinfo();
    public:
        std::string username; //�û�ID
        int userblood; // �û�Ѫ��
        int userscore; // �û�Ŀǰ�ķ�
        int usermaxscore; // �û���ߵ÷�
    };
}

