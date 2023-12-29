#include "AlienSprite.h"

// �ж�Ǳͧ�����Ĭ�Ϻ�����Ĭ�ϳ�ʼ��������Ĭ����������
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

	//��������µľ���
	if (rand() % 60 == 0)
	{
		saAction |= SA_ADDSPRITE;
	}


	return saAction;
}

Sprite* AlienSprite::AddNewSprite(Bitmap* bmp)
{
	//npcǱͧ����ˮ��
	RECT rcBounds = { 0,70,640,480 };
	Sprite* tomb = new Sprite(bmp,1,1, rcBounds, BA_DIE);

	//���Ϸ���
	tomb->SetVelocity(0, -3);

	RECT rcPos = GetPosition();
	int xpos = rcPos.left + GetWidth() / 2;
	if (xpos <= 0 || xpos >= rcBounds.right) {
		return NULL;
	}

	tomb->SetPosition(xpos,rcPos.top);
	return tomb;
}