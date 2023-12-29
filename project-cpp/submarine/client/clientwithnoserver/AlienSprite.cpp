#include "AlienSprite.h"

// 敌对潜艇的相关默认函数，默认初始化函数和默认析构函数
AlienSprite::AlienSprite(Bitmap* pBitmap, int row, int col, RECT& rcBounds, BOUNDSACTION baBoundsAction) :
	Sprite(pBitmap, row, col, rcBounds, baBoundsAction)
{

}


AlienSprite::~AlienSprite()
{

}


SPRITEACTION AlienSprite::Update()
{
	SPRITEACTION saAction = Sprite::Update();

	//随机创建新的精灵
	if (rand() % 60 == 0)
	{
		saAction |= SA_ADDSPRITE;
	}


	return saAction;
}

Sprite* AlienSprite::AddNewSprite(Bitmap* bmp)
{
	//npc潜艇发射水雷
	RECT rcBounds = { 0,70,640,480 };
	Sprite* tomb = new Sprite(bmp,1,1, rcBounds, BA_DIE);

	//向上发射
	tomb->SetVelocity(0, -3);

	RECT rcPos = GetPosition();
	int xpos = rcPos.left + GetWidth() / 2;
	if (xpos <= 0 || xpos >= rcBounds.right) {
		return NULL;
	}

	tomb->SetPosition(xpos,rcPos.top);
	return tomb;
}