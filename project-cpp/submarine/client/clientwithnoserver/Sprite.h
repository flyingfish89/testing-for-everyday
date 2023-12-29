#pragma once

#include <windows.h>
#include "Bitmap.h"

typedef WORD        BOUNDSACTION;//边界动作
const BOUNDSACTION  BA_STOP   = 0,//停止
					BA_WRAP   = 1,//环绕
					BA_BOUNCE = 2,//弹开
					BA_DIE    = 3;//删除

typedef WORD        SPRITEACTION;  //碰撞动作（add）
const SPRITEACTION  SA_NONE   = 0x0000L,  //不做任何事情
                    SA_KILL   = 0x0001L, //删除精灵并销毁它
					SA_ADDSPRITE = 0x0002; //创建新的精灵
//以后可以根据需要再添加新的动作，以便扩展精灵管理器的任务。

//-----------------------------------------------------------------
// Sprite Class
//-----------------------------------------------------------------
class Sprite
{
protected:
	Bitmap*       m_pBitmap;
	RECT          m_rcPosition; //位置矩形
	POINT         m_ptVelocity; //速度
	int           m_iZOrder;    //Z顺序
	RECT          m_rcBounds;   //边界矩形
	BOUNDSACTION  m_baBoundsAction;//边界动作
	BOOL          m_bHidden;	//隐藏性

	RECT	      m_rcCollision;  //碰撞矩阵（add）

	bool m_bDying;
	bool m_bOneCycle;//是否显示一次

	int frameW, frameH; // 精灵的宽高
	int col;//图片的列数
	int* frameSequence;//帧序列数组
	int frameCount; // 数组的总帧数
	int frameIndex;//当前帧索引
	int frameDelay;//帧延迟
	int frameTriggle;//帧计数器

	//游戏状态
	int m_gameStatus;

  
	//该函数设计为虚函数，因此派生类可以重写，给出自己特定的碰撞矩形计算方法。
	virtual void  CalcCollisionRect();//计算碰撞矩阵（add）
		
public:
	Sprite(Bitmap* pBitmap, int row,int col,RECT& rcBounds, BOUNDSACTION baBoundsAction = BA_STOP,bool bOneCycle=false);
	Sprite(Bitmap* pBitmap, int row,int col,POINT ptPosition, POINT ptVelocity, int iZOrder,
		RECT& rcBounds, BOUNDSACTION baBoundsAction = BA_STOP, bool bOneCycle = false);
	virtual ~Sprite();	
	
	// General Methods
	//virtual void  Update();（update）
	void          Draw(HDC hDC,bool bTrans=true, COLORREF crTransColor=RGB(255,0,255));
	BOOL          IsPointInside(int x, int y);//击中测试，判断鼠标是否击中了精灵
	
	//void setSequence(int seq[], int count, int delay) {
	//	frameSequence = new int[count];
	//	for (int i = 0; i < count; i++) {
	//		frameSequence[i] = seq[i];
	//		//frameCount = count;//数组的总帧数
	//		//frameIndex = -1;//当前帧索引
	//		//frameDelay = delay; // 帧延迟
	//		//frameTriggle = 0;//帧计数器
	//	}
	//	
	//}
	void setSequence(int seq[], int count, int delay)
	{
		frameSequence = new int[count];
		for (int i = 0; i < count; i++)
		{
			frameSequence[i] = seq[i];
			frameCount = count;   //数组的总帧数
			frameIndex = -1; //当前帧索引
			frameDelay = delay; //帧延迟
			frameTriggle = 0; //帧计数器

		}
	
	}

	//帧切换函数
	void UpdateFrame() {
		++frameTriggle;
		if (frameTriggle > frameDelay) {	//时间到
			frameTriggle = 0;
			if (frameIndex >= frameCount-1) {
				if (m_bOneCycle) {
					m_bDying = true;
				}
				else {
					frameIndex = 0;
				}
			}
			else {
				frameIndex++;
			}
		}
	}
	
	//void UpdateFrame() //帧切换函数
	//{
	//	++frameTriggle;
	//	if (frameTriggle > frameDelay)//时间到
	//	{
	//		frameTriggle = 0;

	//		if (frameIndex >= frameCount - 1)
	//			frameIndex = 0;
	//		else
	//			frameIndex++;
	//	}
	//}



	// General Methods
	virtual SPRITEACTION  Update();//（add）//添加了对Die动作的支持

	virtual Sprite* AddNewSprite(Bitmap*bmp); //interface 创建新的精灵



	BOOL	TestCollision(Sprite* pTestSprite);//（add）

	// Accessor Methods
	RECT&   GetCollision() { return m_rcCollision; };//（add）

	RECT&   GetPosition(){ return m_rcPosition; };
	void    SetPosition(RECT& rcPosition){ CopyRect(&m_rcPosition, &rcPosition); };
	void    SetPosition(int x, int y);
	void    SetPosition(POINT ptPosition);	
	
	void    OffsetPosition(int x, int y);//移动位置，相对坐标
	POINT   GetVelocity() { return m_ptVelocity; }
	void    SetVelocity(int x, int y);
	void    SetVelocity(POINT ptVelocity);
	BOOL    GetZOrder() { return m_iZOrder; }
	void    SetZOrder(int iZOrder) { m_iZOrder = iZOrder; }
	void    SetBounds(RECT& rcBounds) { CopyRect(&m_rcBounds, &rcBounds); }
	void    SetBoundsAction(BOUNDSACTION ba) { m_baBoundsAction = ba; }
	BOOL    IsHidden() { return m_bHidden; }
	void    SetHidden(BOOL bHidden) { m_bHidden = bHidden; }
	int     GetWidth() { return m_pBitmap->GetWidth(); }
	int     GetHeight() { return m_pBitmap->GetHeight(); }

	Bitmap* GetBitmap() { return m_pBitmap; }

	void kill() { m_bDying = true; }

};

//-----------------------------------------------------------------
// Sprite Inline Helper Methods
//-----------------------------------------------------------------

///////////////////////////////（add）///////////////////////////////////////

inline void Sprite::CalcCollisionRect()
{
	//缺省实现为：碰撞矩形比位置矩形小1/6
	int iXShrink = (m_rcPosition.left - m_rcPosition.right) / 12;
	int iYShrink = (m_rcPosition.top - m_rcPosition.bottom) / 12;
	CopyRect(&m_rcCollision, &m_rcPosition);
	InflateRect(&m_rcCollision, iXShrink, iYShrink);
}

//-----------------------------------------------------------------
// Sprite Inline General Methods
//-----------------------------------------------------------------
inline BOOL Sprite::TestCollision(Sprite* pTestSprite)
{
	//检测两个碰撞矩形是否有重叠
	RECT& rcTest = pTestSprite->GetCollision();
	return m_rcCollision.left <= rcTest.right && rcTest.left <= m_rcCollision.right &&
		m_rcCollision.top <= rcTest.bottom && rcTest.top <= m_rcCollision.bottom;
}

/////////////////////////////（add）//////////////////////////////////////

inline BOOL Sprite::IsPointInside(int x, int y)
{
	POINT ptPoint;
	ptPoint.x = x;
	ptPoint.y = y;
	return PtInRect(&m_rcPosition, ptPoint);
}

//-----------------------------------------------------------------
// Sprite Inline Accessor Methods
//-----------------------------------------------------------------
inline void Sprite::SetPosition(int x, int y)
{
	OffsetRect(&m_rcPosition, x - m_rcPosition.left, y - m_rcPosition.top);
	CalcCollisionRect();//（add）
}

inline void Sprite::SetPosition(POINT ptPosition)
{
	OffsetRect(&m_rcPosition, ptPosition.x - m_rcPosition.left,
		ptPosition.y - m_rcPosition.top);
	CalcCollisionRect();//（add）
}

inline void Sprite::OffsetPosition(int x, int y)
{
	OffsetRect(&m_rcPosition, x, y);
	CalcCollisionRect();//（add）
}

inline void Sprite::SetVelocity(int x, int y)
{
	m_ptVelocity.x = x;
	m_ptVelocity.y = y;
}

inline void Sprite::SetVelocity(POINT ptVelocity)
{
	m_ptVelocity.x = ptVelocity.x;
	m_ptVelocity.y = ptVelocity.y;
}
