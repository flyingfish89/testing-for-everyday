#include "Sprite.h"

//-----------------------------------------------------------------
// Sprite Constructor(s)/Destructor
//-----------------------------------------------------------------
Sprite::Sprite(Bitmap* pBitmap, int row, int col,RECT& rcBounds, BOUNDSACTION baBoundsAction, bool bOneCycle)
{
	//计算一个随机位置
	int iXPos = rand() % (rcBounds.right - rcBounds.left);
	int iYPos = rand() % (rcBounds.bottom - rcBounds.top);
	
	// Initialize the member variables
	m_pBitmap = pBitmap;

	frameW = m_pBitmap->GetWidth() / col;
	frameH = m_pBitmap->GetHeight() / row;
	this->col = col;


	/*SetRect(&m_rcPosition, iXPos, iYPos, iXPos + pBitmap->GetWidth(),iYPos + pBitmap->GetHeight());*/
	SetRect(&m_rcPosition, iXPos, iYPos, iXPos + frameW, iYPos + frameH);
	CalcCollisionRect();//（add）
	m_ptVelocity.x = m_ptVelocity.y = 0;
	m_iZOrder = 0;
	CopyRect(&m_rcBounds, &rcBounds);
	m_baBoundsAction = baBoundsAction;
	m_bHidden = FALSE;

	m_bDying = false;
	m_bOneCycle = bOneCycle;

	frameSequence = NULL;
	frameCount = 0;//数组的总帧数
	frameIndex = 0; //当前帧索引
	frameDelay = 0; //帧延迟
	frameTriggle = 0; //帧计数器


}

//Sprite::Sprite(Bitmap* pBitmap, int row, int col, RECT& rcBounds, BOUNDSACTION baBoundsAction)
//{
//}

Sprite::Sprite(Bitmap* pBitmap, int row, int col, POINT ptPosition, POINT ptVelocity, int iZOrder,
			   RECT& rcBounds, BOUNDSACTION baBoundsAction, bool bOneCycle)
{

	// Initialize the member variables
	m_pBitmap = pBitmap;

	frameW = m_pBitmap->GetWidth() / col;
	frameH = m_pBitmap->GetHeight() / row;
	this->col = col;

	/*SetRect(&m_rcPosition, ptPosition.x, ptPosition.y,
		ptPosition.x + pBitmap->GetWidth(), ptPosition.y + pBitmap->GetHeight());*/
	SetRect(&m_rcPosition,ptPosition.x,ptPosition.y, ptPosition.x+frameW, ptPosition.y + frameH);

	CalcCollisionRect();//（add）

	m_ptVelocity = ptVelocity;
	m_iZOrder = iZOrder;
	CopyRect(&m_rcBounds, &rcBounds);
	m_baBoundsAction = baBoundsAction;
	m_bHidden = FALSE;

	m_bDying = false;
	m_bOneCycle = bOneCycle;


	frameSequence = NULL;
	frameCount = 0;//数组的总帧数
	frameIndex = 0; //当前帧索引
	frameDelay = 0; //帧延迟
	frameTriggle = 0; //帧计数器




}

Sprite::~Sprite()
{
}

//-----------------------------------------------------------------
// Sprite General Methods
//-----------------------------------------------------------------
SPRITEACTION Sprite::Update()//完成精灵移动和碰撞检测
{

	if (m_bDying) {
		return SA_KILL;
	}


	UpdateFrame();
	//更新位置
	POINT ptNewPosition, ptSpriteSize, ptBoundsSize;
	ptNewPosition.x = m_rcPosition.left + m_ptVelocity.x;
	ptNewPosition.y = m_rcPosition.top + m_ptVelocity.y;
	ptSpriteSize.x = m_rcPosition.right - m_rcPosition.left;
	ptSpriteSize.y = m_rcPosition.bottom - m_rcPosition.top;
	ptBoundsSize.x = m_rcBounds.right - m_rcBounds.left;
	ptBoundsSize.y = m_rcBounds.bottom - m_rcBounds.top;
	
	// 检查边界动作
	// 环绕?
	if (m_baBoundsAction == BA_WRAP)
	{
		if ((ptNewPosition.x + ptSpriteSize.x) < m_rcBounds.left)
			ptNewPosition.x = m_rcBounds.right;//到了左边，就移动到右边边界
		else if (ptNewPosition.x > m_rcBounds.right)
			ptNewPosition.x = m_rcBounds.left - ptSpriteSize.x;
		if ((ptNewPosition.y + ptSpriteSize.y) < m_rcBounds.top)
			ptNewPosition.y = m_rcBounds.bottom;
		else if (ptNewPosition.y > m_rcBounds.bottom)
			ptNewPosition.y = m_rcBounds.top - ptSpriteSize.y;
	}
	// 弹开?（更改速度方向）
	else if (m_baBoundsAction == BA_BOUNCE)
	{
		BOOL bBounce = FALSE;
		POINT ptNewVelocity = m_ptVelocity;
		if (ptNewPosition.x < m_rcBounds.left)
		{
			bBounce = TRUE;
			ptNewPosition.x = m_rcBounds.left;
			ptNewVelocity.x = -ptNewVelocity.x;
		}
		else if ((ptNewPosition.x + ptSpriteSize.x) > m_rcBounds.right)
		{
			bBounce = TRUE;
			ptNewPosition.x = m_rcBounds.right - ptSpriteSize.x;
			ptNewVelocity.x = -ptNewVelocity.x;
		}
		if (ptNewPosition.y < m_rcBounds.top)
		{
			bBounce = TRUE;
			ptNewPosition.y = m_rcBounds.top;
			ptNewVelocity.y = -ptNewVelocity.y;
		}
		else if ((ptNewPosition.y + ptSpriteSize.y) > m_rcBounds.bottom)
		{
			bBounce = TRUE;
			ptNewPosition.y = m_rcBounds.bottom - ptSpriteSize.y;
			ptNewVelocity.y = -ptNewVelocity.y;
		}
		if (bBounce)//重设速度
			SetVelocity(ptNewVelocity);
	}

	//////////////////////（add）/////////////////////////////////
	// Die?
	else if (m_baBoundsAction == BA_DIE)
	{
		if ((ptNewPosition.x + ptSpriteSize.x) < m_rcBounds.left ||
			ptNewPosition.x > m_rcBounds.right ||
			(ptNewPosition.y + ptSpriteSize.y) < m_rcBounds.top ||
			ptNewPosition.y > m_rcBounds.bottom)
			return SA_KILL;
	}
	////////////////////////（add）/////////////////////////////////


	//停止(默认)
	else
	{
		//改变速度，以停止精灵
		if (ptNewPosition.x  < m_rcBounds.left ||
			ptNewPosition.x > (m_rcBounds.right - ptSpriteSize.x))
		{
			ptNewPosition.x = max(m_rcBounds.left, min(ptNewPosition.x,
				m_rcBounds.right - ptSpriteSize.x));
			SetVelocity(0, 0);
		}
		if (ptNewPosition.y  < m_rcBounds.top ||
			ptNewPosition.y > (m_rcBounds.bottom - ptSpriteSize.y))
		{
			ptNewPosition.y = max(m_rcBounds.top, min(ptNewPosition.y,
				m_rcBounds.bottom - ptSpriteSize.y));
			SetVelocity(0, 0);

		}
	}
	SetPosition(ptNewPosition);

	return SA_NONE;//（add）
}

void Sprite::Draw(HDC hDC,bool bTrans, COLORREF crTransColor)
{
	// Draw the sprite if it isn't hidden
	if (m_pBitmap != NULL && !m_bHidden)
	{
		if(!bTrans)
			m_pBitmap->Draw(hDC, m_rcPosition.left, m_rcPosition.top);
		else
			m_pBitmap->Draw(hDC, m_rcPosition.left, m_rcPosition.top, true, crTransColor);
	}
}


Sprite* Sprite::AddNewSprite(Bitmap* bmp)
{
	return NULL;
}