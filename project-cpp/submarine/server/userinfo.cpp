#include "userinfo.h"

// �û���Ϣ��Ĭ�Ϲ��캯����Ѫ��Ϊ5��Ŀǰ�ķ֣���ߵ÷־���ʼ��Ϊ0
user::userinfo::userinfo()
{
    userblood = 5; // �û�Ѫ��
    userscore = 0; // �û�Ŀǰ�÷�
    usermaxscore = 0; // �û���ߵ÷�
}

// �û�Ѫ����Ϊ0ʱ�Ļָ�Ĭ�Ϻ���
void user::userinfo::setinituserinfo()
{
    userblood = 5;  // �����û�Ѫ��
    userscore = 0;  // �����û���ǰ�ĵ÷�
}