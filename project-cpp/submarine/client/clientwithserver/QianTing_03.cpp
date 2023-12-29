// QianTing_03.cpp : 定义应用程序的入口点。
//
#define WIN32_LEAN_AND_MEAN
#include<Windows.h>
#include <windowsx.h>
#include<stdio.h>
#include<stdlib.h>
#include<mmsystem.h>
#include<math.h>
#include<iostream>
#include"httplib.h"

//#include "Sprite.h"
#include "GameEngine.h"
//#include "SpriteManager.h"
#define MAX_LOADSTRING 100

#define WINDOW_CLASS_NAME "WINCLASS1"

#include "AlienSprite.h"

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "msimg32.lib")


#define KEYDOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEYUP(vk_code)   ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)


// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


Bitmap* g_pBackgroundBitmap; // 背景
Bitmap* g_pStartBitmap; // 背景

Bitmap* StartMenu; // 开始菜单
Bitmap* ButtonBitmap; // 
Bitmap* Button2Bitmap; // 
Bitmap* ExitBitmap; //
Bitmap* Exit2Bitmap;

Bitmap* g_pShipBitmap; //轮船位图
Bitmap* g_pBombBitmap; //导弹位图

Bitmap* g_pLeftSubmarineBitmap; //潜艇位图
Bitmap* g_pRightSubmarineBitmap; //潜艇位图
Bitmap* g_pTorpedoBitmap;//水雷位图

//失败
Bitmap* g_pGameOverBitmap;
//成功
Bitmap* g_pGameSuccessBitmap;

Bitmap* g_pSmExplosionBitmap;
//Bitmap* g_pLgExplosionBitmap;
Bitmap* g_pLgExplosionBitmap[10];

Sprite* g_pShipSprite;
Sprite* g_pButtonSprite;
Sprite* g_pStartBgSprite;

//单人游戏按钮
Sprite* button1Sprite;
Sprite* button2Sprite;
//退出游戏按钮
Sprite* exitSprite1;
Sprite* exitSprite2;

RECT rcBounds = { 0,0,640,480 };

int g_iNumLives, g_iScore, g_iDifficulty;
int g_MaxScore = 0;
BOOL g_bGameOver;
BOOL g_bSuccess;

const int WINDOW_WIDTH = 640; //窗口大小
const int WINDOW_HEIGHT = 480;

const int NUM = 4; //车数
// GLOBALS /////////////////////////////////////////////////

HWND		g_hWnd = NULL;//保存全局窗口句柄
HINSTANCE	g_hInstance = NULL;//保存全局实例句柄

HDC         g_hOffscreenDC;
HBITMAP     g_hOffscreenBitmap;

Bitmap* g_pHighwayBitmap;

Bitmap* g_pChickenBitmap2;
Bitmap* g_pChickenBitmap3;


Bitmap* za2Bitmap;


Bitmap* g_pCarBitmaps[NUM];
Bitmap* g_pChickenHeadBitmap;
//Bitmap* g_pChickenHeadBitmap2;
int state = 0;
//按键延迟
int         g_iFireInputDelay;  //输入延迟变量，有助于改变键盘和游戏杆的输入响应，以便改进游戏的可玩性


BOOL isRunning = false;  

int seq[8] = { 0,1,2,3,4,5,6,7 };

// 我方血量
int HP = 5;

// http客户端初始化
string getscorename;  // 记录当前客户端的ID信息
httplib::Client  client("192.168.1.19", 9090); // 初始化要连接的服务端的IP地址和端口

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void HandleKeys();
//精灵碰撞事件响应函数
BOOL SpriteCollisin(Sprite* pSpriteHitter, Sprite* pSpriteHittee)
{
    Bitmap* pHitter = pSpriteHitter->GetBitmap();
    Bitmap* pHittee = pSpriteHittee->GetBitmap();


    //1.玩家导弹与NPC潜艇的碰撞
    if (pHitter == g_pBombBitmap && (pHittee == g_pLeftSubmarineBitmap || pHittee == g_pRightSubmarineBitmap) ||
        (pHittee == g_pBombBitmap && (pHitter == g_pLeftSubmarineBitmap || pHitter == g_pRightSubmarineBitmap)))
    {
        g_iScore++;

        // 更新服务器用户目前得分
        client.Get("setuser" + getscorename);
        client.Get("setscore" + std::to_string(g_iScore));
        //only kill tomb
        pSpriteHitter->kill();
        pSpriteHittee->kill();

        //产生一个大爆炸
        RECT rcpos = pSpriteHitter->GetPosition();
        RECT rcBounds = { 0,0,640,480 };

        //Sprite* explore_Sprite[8];
        for (int i = 0; i < 8; i++) {
            Sprite* explore_Sprite = new Sprite(g_pLgExplosionBitmap[i], 1, 1, rcBounds, BA_WRAP, true);
            /* explore_Sprite->setSequence(seq, 8, 2);*/
            explore_Sprite->SetPosition(rcpos.left, rcpos.top);

            AddSprite(explore_Sprite);
        }

    }

    //2.潜艇水雷与玩家军舰的碰撞
    if (pHitter == g_pTorpedoBitmap && pHittee == g_pShipBitmap ||
        (pHittee == g_pTorpedoBitmap && pHitter == g_pShipBitmap))
    {
        //kill both
        HP--;

        // 更新服务器当前用户的血量
        client.Get("setuser" + getscorename);
        client.Get("setblood" + std::to_string(HP));

        if (pHitter == g_pTorpedoBitmap) {
            pSpriteHitter->kill();
        }
        else {
            pSpriteHittee->kill();
        }

        //产生一个大爆炸
        RECT rcpos = pSpriteHitter->GetPosition();
        RECT rcBounds = { 0,0,640,480 };

        for (int i = 0; i < 8; i++) {
            Sprite* explore_Sprite = new Sprite(g_pLgExplosionBitmap[i], 1, 1, rcBounds, BA_WRAP, true);
            /* explore_Sprite->setSequence(seq, 8, 2);*/
            explore_Sprite->SetPosition(rcpos.left, rcpos.top);

            AddSprite(explore_Sprite);
        }

        g_pShipSprite->SetPosition(320, 45);
    }



    return FALSE;
}


void NewGame()
{
    // 清除上一张图的所有
    CleanupSprites();

    // 创建潜艇
    g_pShipSprite = new Sprite(g_pShipBitmap, 1, 1, rcBounds, BA_STOP);
    g_pShipSprite->SetPosition(30, 70 - 27);
    AddSprite(g_pShipSprite);
    g_pShipSprite->SetHidden(true);

    g_iFireInputDelay = 0;
    g_iScore = 0;

    // 更新最高分
    auto it = client.Get("maxscore" + getscorename);
    sscanf_s(it->body.c_str(), "%d", &g_MaxScore);
    // 更新血量和上一次的目前得分
    it = client.Get("blood" + getscorename);
    sscanf_s(it->body.c_str(), "%d", &HP);
    // 与服务器请求更新目前得分情况
    it = client.Get("score" + getscorename);
    sscanf_s(it->body.c_str(), "%d", &g_iScore);

    g_iNumLives = 3;
    g_iDifficulty = 80;
    g_bGameOver = FALSE;

    //PlayMIDISong();
}


///////////////////////////////////////////////
AlienSprite* pSprite;
//创建随机敌人潜艇
void AddSubmarine()
{
    RECT rcBounds = { 0,70,640,480 };
    //AlienSprite* pSprite;

    switch (rand() % 2)
    {// 判断敌人的出生方向，左边还是右边
    case 0: //left
        pSprite = new AlienSprite(g_pLeftSubmarineBitmap, 1, 1, rcBounds, BA_WRAP);
        pSprite->SetPosition(640, rand() % 300 + 100);
        pSprite->SetVelocity(-rand() % 4, 0);
        break;
    case 1: //right
        pSprite = new AlienSprite(g_pRightSubmarineBitmap, 1, 1, rcBounds, BA_WRAP);
        pSprite->SetPosition(-64, rand() % 300 + 100);
        pSprite->SetVelocity(rand() % 4, 0);
        break;

    }
    AddSprite(pSprite);
}

///////////////////////////////////////////////
int strindex = 0;  //输入账户时的字符串位置偏移，原始位置280加上该偏移是下一个字符的位置
void shoustr(HDC hDC, string s)
{
    // 从x:280,y:620开始创建字符，实时更新
    RECT rect1 = { 280+strindex,620,289 + strindex,10 };
    strindex+=8; //下一个字符的位置偏移
    SetBkMode(hDC, TRANSPARENT);
    SetTextColor(hDC, RGB(255, 255, 255));
    // 画字符
    DrawText(hDC, s.c_str(), 1, &rect1, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
}
void Menustart(HDC hDC)
{
    // 登陆界面显示，输入账号提示信息
    string s("输入账户：");
    string schar; // 存储每一次的输入情况
    RECT rect = { 200,600,300,30 }; //输入账号的起始位置
    SetBkMode(hDC, TRANSPARENT);
    SetTextColor(hDC, RGB(255, 255, 255));
    // 画布画出登陆界面进行显示
    DrawText(hDC, s.c_str(), s.size(), &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

    s.clear();  // 清除登陆界面字符串
    char c = '0';  // 判断是否有按键输入
    while (1)
    {
        // 该循环 1.判断是否有按键输入，2.显示字符串 3.记录当前账号信息（方便与服务器交互）
        if (KEYDOWN(65))
        {
            if (c != 'a')
            {
                c = 'a';
                s.push_back('a');
                schar.clear();
                schar.push_back(c);
                shoustr(hDC, schar);
            }
        }
        else if (KEYDOWN(66))
        {
            if (c != 'b')
            {
                c = 'b';
                s.push_back('b');
                schar.clear();
                schar.push_back(c);
                shoustr(hDC, schar);
            }
        }
        else if (KEYDOWN(67))
        {
            if (c != 'c')
            {
                c = 'c';
                s.push_back('c');
                schar.clear();
                schar.push_back(c);
                shoustr(hDC, schar);
            }
        }
        else if (KEYDOWN(68))
        {
            if (c != 'd')
            {
                c = 'd';
                s.push_back('d');
                schar.clear();
                schar.push_back(c);
                shoustr(hDC, schar);
            }
        }
        else if (KEYDOWN(69))
        {
            if (c != 'e')
            {
                c = 'e';
                s.push_back('e');
                schar.clear();
                schar.push_back(c);
                shoustr(hDC, schar);
            }
        }
        else if (KEYDOWN(70))
        {
            if (c != 'f')
            {
                c = 'f';
                s.push_back('f');
                schar.clear();
                schar.push_back(c);
                shoustr(hDC, schar);
            }
        }
        else if (KEYDOWN(71))
        {
            if (c != 'g')
            {
                c = 'g';
                s.push_back('g');
                schar.clear();
                schar.push_back(c);
                shoustr(hDC, schar);
            }
        }
        else if (KEYDOWN(72))
        {
            if (c != 'h')
            {
                c = 'h';
                s.push_back('h');
                schar.clear();
                schar.push_back(c);
                shoustr(hDC, schar);
            }
        }
        else if (KEYDOWN(73))
        {
            if (c != 'i')
            {
                c = 'i';
                s.push_back('i');
                schar.clear();
                schar.push_back(c);
                shoustr(hDC, schar);
            }
        }
        else if (KEYDOWN(74))
        {
            if (c != 'j')
            {
                c = 'j';
                s.push_back('j');
                schar.clear();
                schar.push_back(c);
                shoustr(hDC, schar);
            }
        }
        else if (KEYDOWN(75))
        {
            if (c != 'k')
            {
                c = 'k';
                s.push_back('k');
                schar.clear();
                schar.push_back(c);
                shoustr(hDC, schar);
            }
        }
        else if (KEYDOWN(76))
        {
            if (c != 'l')
            {
                c = 'l';
                s.push_back('l');
                schar.clear();
                schar.push_back(c);
                shoustr(hDC, schar);
            }
        }
        else if (KEYDOWN(77))
        {
            if (c != 'm')
            {
                c = 'm';
                s.push_back('m');
                schar.clear();
                schar.push_back(c);
                shoustr(hDC, schar);
            }
        }
        else if (KEYDOWN(78))
        {
            if (c != 'n')
            {
                c = 'n';
                s.push_back('n');
                schar.clear();
                schar.push_back(c);
                shoustr(hDC, schar);
            }
        }
        else if (KEYDOWN(79))
        {
            if (c != 'o')
            {
                c = 'o';
                s.push_back('o');
                schar.clear();
                schar.push_back(c);
                shoustr(hDC, schar);
            }
        }
        else if (KEYDOWN(80))
        {
            if (c != 'p')
            {
                c = 'p';
                s.push_back('p');
                schar.clear();
                schar.push_back(c);
                shoustr(hDC, schar);
            }
        }
        else if (KEYDOWN(81))
        {
            if (c != 'q')
            {
                c = 'q';
                s.push_back('q');
                schar.clear();
                schar.push_back(c);
                shoustr(hDC, schar);
            }
        }
        else if (KEYDOWN(82))
        {
            if (c != 'r')
            {
                c = 'r';
                s.push_back('r');
                schar.clear();
                schar.push_back(c);
                shoustr(hDC, schar);
            }
        }
        else if (KEYDOWN(83))
        {
            if (c != 's')
            {
                c = 's';
                s.push_back('s');
                schar.clear();
                schar.push_back(c);
                shoustr(hDC, schar);
            }
        }
        else if (KEYDOWN(84))
        {
            if (c != 't')
            {
                c = 't';
                s.push_back('t');
                schar.clear();
                schar.push_back(c);
                shoustr(hDC, schar);
            }
        }
        else if (KEYDOWN(85))
        {
            if (c != 'u')
            {
                c = 'u';
                s.push_back('u');
                schar.clear();
                schar.push_back(c);
                shoustr(hDC, schar);
            }
        }
        else if (KEYDOWN(86))
        {
            if (c != 'v')
            {
                c = 'v';
                s.push_back('v');
                schar.clear();
                schar.push_back(c);
                shoustr(hDC, schar);
            }
        }
        else if (KEYDOWN(87))
        {
            if (c != 'w')
            {
                c = 'w';
                s.push_back('w');
                schar.clear();
                schar.push_back(c);
                shoustr(hDC, schar);
            }
        }
        else if (KEYDOWN(88))
        {
            if (c != 'x')
            {
                c = 'x';
                s.push_back('x');
                schar.clear();
                schar.push_back(c);
                shoustr(hDC, schar);
            }
        }
        else if (KEYDOWN(89))
        {
            if (c != 'y')
            {
                c = 'y';
                s.push_back('y');
                schar.clear();
                schar.push_back(c);
                shoustr(hDC, schar);
            }
        }
        else if (KEYDOWN(90))
        {
            if (c != 'z')
            {
                c = 'z';
                s.push_back('z');
                schar.clear();
                schar.push_back(c);
                shoustr(hDC, schar);
            }
        }
        else if (KEYDOWN(13))
        {
            // enter 结束账号输入，更新当前客户端的ID信息
            getscorename.clear();
            getscorename.append(s);
            Sleep(500);
            break;
        }
    }
}
void GameStart(HDC hDC)
{
    // Seed the random number generator
    srand(GetTickCount());
    // 播放背景音乐
    PlaySound("Res/bground.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    //创建屏幕外设备环境和位图
    g_hOffscreenDC = CreateCompatibleDC(hDC);
    g_hOffscreenBitmap = CreateCompatibleBitmap(hDC, WINDOW_WIDTH, WINDOW_HEIGHT);
    SelectObject(g_hOffscreenDC, g_hOffscreenBitmap);
    g_pBackgroundBitmap = new Bitmap(hDC, "Res/background.bmp");
    g_pShipBitmap = new Bitmap(hDC, "Res/SHIP2.bmp");
    g_pLeftSubmarineBitmap = new Bitmap(hDC, "Res/submarine1.bmp");
    g_pRightSubmarineBitmap = new Bitmap(hDC, "Res/submarine2.bmp");
    g_pBombBitmap = new Bitmap(hDC, "Res/BOMB.bmp");
    g_pTorpedoBitmap = new Bitmap(hDC, "Res/TORPEDO.bmp");
    g_pSmExplosionBitmap = new Bitmap(hDC, "Res/SmExplosion.bmp");
    /*g_pLgExplosionBitmap = new Bitmap(hDC, "Res/LgExplosion.bmp");*/
    //游戏失败图片
    g_pGameOverBitmap = new Bitmap(hDC, "Res/GameOver.bmp");
    //游戏成功图片
    g_pGameSuccessBitmap = new Bitmap(hDC, "Res/success.bmp");

    //爆炸
    g_pLgExplosionBitmap[0] = new Bitmap(hDC, "Res/ex/1.bmp");
    g_pLgExplosionBitmap[1] = new Bitmap(hDC, "Res/ex/2.bmp");
    g_pLgExplosionBitmap[2] = new Bitmap(hDC, "Res/ex/3.bmp");
    g_pLgExplosionBitmap[3] = new Bitmap(hDC, "Res/ex/4.bmp");
    g_pLgExplosionBitmap[4] = new Bitmap(hDC, "Res/ex/5.bmp");
    g_pLgExplosionBitmap[5] = new Bitmap(hDC, "Res/ex/6.bmp");
    g_pLgExplosionBitmap[6] = new Bitmap(hDC, "Res/ex/7.bmp");
    g_pLgExplosionBitmap[7] = new Bitmap(hDC, "Res/ex/8.bmp");

    //开始菜单
    //RECT rcBounds = { 0,0,640,480 };

    ButtonBitmap = new Bitmap(hDC, "Res/button1.bmp");
    Button2Bitmap = new Bitmap(hDC, "Res/button2.bmp");
    ExitBitmap = new Bitmap(hDC, "Res/button7.bmp");
    Exit2Bitmap = new Bitmap(hDC, "Res/button8.bmp");

    //开始菜单
    g_pStartBitmap = new Bitmap(hDC, "Res/menu.bmp");
    g_pStartBitmap->Draw(hDC, 0, 0);
    NewGame();

}



void GameEnd()
{
    //CloseMIDIPlayer();
    // 
    // Cleanup the sprites
    // 清除位图信息
    CleanupSprites();

    // 清除窗口信息
    DeleteObject(g_hOffscreenBitmap);
    DeleteObject(g_hOffscreenDC);

    // 清除全局控制变量
    delete g_pBackgroundBitmap;
    delete g_pShipBitmap;
    delete g_pLeftSubmarineBitmap;
    delete g_pRightSubmarineBitmap;
    delete g_pBombBitmap;
    delete g_pTorpedoBitmap;
    delete g_pSmExplosionBitmap;
    delete g_pLgExplosionBitmap;
    delete g_pGameOverBitmap;

}

//图像的绘制
void GamePaint(HDC hDC)
{
    //绘制背景
    //g_pStartBitmap->Draw(hDC, 0, 0);
    g_pBackgroundBitmap->Draw(hDC, 0, 0);

    //绘制精灵
    DrawSprites(hDC);
    //绘制得分
    char szText[64];
    RECT rect = { 150,0,400,30 };
    sprintf_s(szText, "目前得分:%d", g_iScore);
    SetBkMode(hDC, TRANSPARENT);
    SetTextColor(hDC, RGB(255, 255, 255));
    DrawText(hDC, szText, -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

    //绘制最高得分
    RECT rect1 = { 400,0,500,30 };
    if (g_MaxScore >= g_iScore)
    {
        sprintf_s(szText, "最高得分:%d", g_MaxScore);
    }
    else
    {
        sprintf_s(szText, "最高得分:%d", g_iScore);
        g_MaxScore = g_iScore;
        // 更新服务器的最高得分
        client.Get("setuser" + getscorename);
        client.Get("setmaxscore" + std::to_string(g_MaxScore));
    }
    SetBkMode(hDC, TRANSPARENT);
    SetTextColor(hDC, RGB(255, 255, 255));
    DrawText(hDC, szText, -1, &rect1, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

    // 绘制血量
    char szText1[64];
    RECT rect2 = { 0,0,200,30 };
    sprintf_s(szText1, "我方血量:%d", HP);
    SetBkMode(hDC, TRANSPARENT);
    SetTextColor(hDC, RGB(255, 0, 0));
    DrawText(hDC, szText1, -1, &rect2, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

    //大于3分
    if (g_iScore >= 3) {
        // 游戏成功
        g_pGameSuccessBitmap->Draw(hDC, 0, 0);

    }

    if (HP <= 0) {
        g_bGameOver = true;
    }

    // 绘制Game over窗口
    if (g_bGameOver) {
        char szText[64];
        RECT rect = { 270,200,370,30 };
        sprintf_s(szText, "血量为0");
        SetBkMode(hDC, TRANSPARENT);
        SetTextColor(hDC, RGB(255, 0, 0));
        DrawText(hDC, szText, -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
        g_pGameOverBitmap->Draw(hDC, 190, 140, TRUE, RGB(255, 0, 255));
    }

    /* g_pLgExplosionBitmap[8]->Draw(hDC, 190, 140, TRUE, RGB(255, 0, 255));*/
}

void GameCycle(HDC hDC)
{
    if (!g_bGameOver)
    {

        //随机创建敌人潜艇精灵
        if (rand() % g_iDifficulty == 0)
        {
            AddSubmarine();
        }

        HandleKeys();
        //更新精灵
        UpdateSprites();

        // 绘制游戏窗口
        GamePaint(g_hOffscreenDC);

        BitBlt(hDC, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, g_hOffscreenDC, 0, 0, SRCCOPY);
    }
}


void MoveShip(int iXDistance, int iYDistance)
{
    // Move the chicken to its new position
    g_pShipSprite->OffsetPosition(iXDistance, iYDistance);

    // See if the chicken made it across
    if (g_pShipSprite->GetPosition().left > 640)
    {
        // Move the chicken back to the start and add to the score

    }
}


//键盘的事件
void HandleKeys()
{
    if (!g_bGameOver)
    {
        // Move the chicken based upon key presses
        // 获取左右按键，左右移动
        POINT ptVelcoity = g_pShipSprite->GetVelocity();
        if (KEYDOWN(VK_LEFT))
        {
            // 左移动
            ptVelcoity.x = max(ptVelcoity.x - 1, -4);
            g_pShipSprite->SetVelocity(ptVelcoity);
        }
        else if (KEYDOWN(VK_RIGHT))
        {
            // 右移动
            ptVelcoity.x = min(ptVelcoity.x + 2, 6);
            g_pShipSprite->SetVelocity(ptVelcoity);
        }

        //按下空格键发射导弹
        if ((++g_iFireInputDelay > 6) && KEYDOWN(VK_SPACE))
        {
            RECT rcBounds = { 0,0,640,480 };
            RECT rcPos = g_pShipSprite->GetPosition();
            Sprite* pSprite = new Sprite(g_pBombBitmap, 1, 1, rcBounds, BA_DIE);
            pSprite->SetPosition(rcPos.left + 15, 70);
            pSprite->SetVelocity(0, 3);
            AddSprite(pSprite);

            //重置输入延迟
            g_iFireInputDelay = 0;
        }

    }
    //按下回车键开始一个新的游戏
    if (g_bGameOver && KEYDOWN(VK_RETURN))
    {
        NewGame();
    }


}
Bitmap* menu;
Bitmap* button1;
HDC hMenDC;
HDC g_hdc;

HWND 		g_hwnd;//保存全局窗口句柄
int buttonUp = 0;
int buttonDown = 0;
void MouseButtonDown(int x, int y, BOOL bLeft)
{
    //GameStart(hdc);
    //g_pStartBgSprite->SetHidden(true);
    if (x >= 200 && x <= 400 && y >= 230 && y <= 300) {
        buttonDown = 1;
        state = 1;
        //button2Sprite->SetHidden(true);
        g_pShipSprite->SetHidden(false);
    }
    else if (x >= 200 && x <= 400 && y >= 300 && y <= 400) {
        //退出游戏
        state = -1;

    }


}
void MouseButtonUp(int x, int y, BOOL bLeft) {
    if (x >= 200 && x <= 400 && y >= 230 && y <= 300) {
        buttonUp = 1;
    }
}

//回调函数，完成对消息的处理，由操作系统直接调用
LRESULT CALLBACK WinProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{	//根据不同的消息类型进行相应的处理
    switch (uMsg)
    {
        // 鼠标的左键按下和按起的判断
    case WM_LBUTTONDOWN:
        MouseButtonDown(LOWORD(lParam), HIWORD(lParam), TRUE);
        //MouseButtonDown(200, 230, TRUE);
        return 0;
    case WM_LBUTTONUP:
        MouseButtonUp(LOWORD(lParam), HIWORD(lParam), TRUE);
        return 0;
    case WM_DESTROY: //窗口销毁时触发的消息
        PostQuitMessage(0);
        break;
    default:
        break;
    }
    //未被上述代码处理的消息都交由这里处理。
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

// 创建http客户端
void httpclient()
{
    // 设置与服务端的连接相关属性,请求恢复在多少毫秒之内
    client.set_keep_alive(true); // 保持连接
    client.set_connection_timeout(0, 30000000); // 30000 milliseconds
    client.set_read_timeout(200, 0); // 200 mseconds
    client.set_write_timeout(50, 0); // 50 mseconds
}

/*windows主函数（程序运行的入口，从这里进入执行，离开该函数表示程序的结束）*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow
)
{
    //定义一个窗口类的对象（参考MSDN）
    WNDCLASSEX winclass;
    winclass.cbSize = sizeof(WNDCLASSEX);
    winclass.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    winclass.lpfnWndProc = WinProc;
    winclass.cbClsExtra = 0;
    winclass.cbWndExtra = 0;
    winclass.hInstance = hInstance;
    winclass.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    winclass.hCursor = LoadCursor(hInstance, IDC_ARROW);
    winclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    winclass.lpszMenuName = NULL;
    winclass.lpszClassName = "GameWndClass";
    winclass.hIconSm = LoadIcon(hInstance, IDI_APPLICATION);

    //注册窗口类
    if (!RegisterClassEx(&winclass))
        return 0;

    //将实例句柄用一个全局变量保存，方便在其他函数中使用
    g_hInstance = hInstance;
    HWND hwnd = CreateWindowEx(
        NULL,
        "GameWndClass",
        "潜艇大战",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH, WINDOW_HEIGHT,
        NULL,
        NULL,
        hInstance,
        NULL
    );
    int count = 50;


    //将窗口句柄用一个全局变量保存，方便在其他函数中使用
    g_hWnd = hwnd;
    HDC hdc = GetDC(hwnd);
    ShowWindow(hwnd, SW_SHOW);//显示窗口
    UpdateWindow(hwnd);//重新绘制一遍窗口

    /*HDC hdc = GetDC(g_hWnd);*/
    Menustart(hdc);
    GameStart(hdc);
    //MenuStart(hdc);

    //启动消息循环，注意这里使用一种非阻塞的获取消息的方式
    MSG msg;
    while (1)
    {
        DWORD starttime = GetTickCount();
        count--;
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                break;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        //点击esc键弹出窗口，点击中止即可退出整个程序
        if (KEYDOWN(VK_ESCAPE))
        {
            PostQuitMessage(1);
        }
        //Sprite* 
        if (state == 1) {


            GameCycle(hdc);
        }
        else if (state == 0) {
            Button2Bitmap->Draw(hdc, 200, 230, TRUE, RGB(255, 0, 255));
            Exit2Bitmap->Draw(hdc, 200, 300, TRUE, RGB(255, 0, 255));
        }
        else if (state == -1) {
            exit(0);
        }

        if (GetTickCount() - starttime < 33)
            Sleep(33 - (GetTickCount() - starttime));
    }

    GameEnd();

    return 1;
}


