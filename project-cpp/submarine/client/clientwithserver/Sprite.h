#pragma once

#include <windows.h>
#include "Bitmap.h"

typedef WORD        BOUNDSACTION;//�߽綯��
const BOUNDSACTION  BA_STOP   = 0,//ֹͣ
					BA_WRAP   = 1,//����
					BA_BOUNCE = 2,//����
					BA_DIE    = 3;//ɾ��

typedef WORD        SPRITEACTION;  //��ײ������add��
const SPRITEACTION  SA_NONE   = 0x0000L,  //�����κ�����
                    SA_KILL   = 0x0001L, //ɾ�����鲢������
					SA_ADDSPRITE = 0x0002; //�����µľ���
//�Ժ���Ը�����Ҫ������µĶ������Ա���չ���������������

//-----------------------------------------------------------------
// Sprite Class
//-----------------------------------------------------------------
class Sprite
{
protected:
	Bitmap*       m_pBitmap;
	RECT          m_rcPosition; //λ�þ���
	POINT         m_ptVelocity; //�ٶ�
	int           m_iZOrder;    //Z˳��
	RECT          m_rcBounds;   //�߽����
	BOUNDSACTION  m_baBoundsAction;//�߽綯��
	BOOL          m_bHidden;	//������

	RECT	      m_rcCollision;  //��ײ����add��

	bool m_bDying;
	bool m_bOneCycle;//�Ƿ���ʾһ��

	int frameW, frameH; // ����Ŀ��
	int col;//ͼƬ������
	int* frameSequence;//֡��������
	int frameCount; // �������֡��
	int frameIndex;//��ǰ֡����
	int frameDelay;//֡�ӳ�
	int frameTriggle;//֡������

	//��Ϸ״̬
	int m_gameStatus;

  
	//�ú������Ϊ�麯������������������д�������Լ��ض�����ײ���μ��㷽����
	virtual void  CalcCollisionRect();//������ײ����add��
		
public:
	Sprite(Bitmap* pBitmap, int row,int col,RECT& rcBounds, BOUNDSACTION baBoundsAction = BA_STOP,bool bOneCycle=false);
	Sprite(Bitmap* pBitmap, int row,int col,POINT ptPosition, POINT ptVelocity, int iZOrder,
		RECT& rcBounds, BOUNDSACTION baBoundsAction = BA_STOP, bool bOneCycle = false);
	virtual ~Sprite();	
	
	// General Methods
	//virtual void  Update();��update��
	void          Draw(HDC hDC,bool bTrans=true, COLORREF crTransColor=RGB(255,0,255));
	BOOL          IsPointInside(int x, int y);//���в��ԣ��ж�����Ƿ�����˾���
	
	//void setSequence(int seq[], int count, int delay) {
	//	frameSequence = new int[count];
	//	for (int i = 0; i < count; i++) {
	//		frameSequence[i] = seq[i];
	//		//frameCount = count;//�������֡��
	//		//frameIndex = -1;//��ǰ֡����
	//		//frameDelay = delay; // ֡�ӳ�
	//		//frameTriggle = 0;//֡������
	//	}
	//	
	//}
	void setSequence(int seq[], int count, int delay)
	{
		frameSequence = new int[count];
		for (int i = 0; i < count; i++)
		{
			frameSequence[i] = seq[i];
			frameCount = count;   //�������֡��
			frameIndex = -1; //��ǰ֡����
			frameDelay = delay; //֡�ӳ�
			frameTriggle = 0; //֡������

		}
	
	}

	//֡�л�����
	void UpdateFrame() {
		++frameTriggle;
		if (frameTriggle > frameDelay) {	//ʱ�䵽
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
	
	//void UpdateFrame() //֡�л�����
	//{
	//	++frameTriggle;
	//	if (frameTriggle > frameDelay)//ʱ�䵽
	//	{
	//		frameTriggle = 0;

	//		if (frameIndex >= frameCount - 1)
	//			frameIndex = 0;
	//		else
	//			frameIndex++;
	//	}
	//}



	// General Methods
	virtual SPRITEACTION  Update();//��add��//����˶�Die������֧��

	virtual Sprite* AddNewSprite(Bitmap*bmp); //interface �����µľ���



	BOOL	TestCollision(Sprite* pTestSprite);//��add��

	// Accessor Methods
	RECT&   GetCollision() { return m_rcCollision; };//��add��

	RECT&   GetPosition(){ return m_rcPosition; };
	void    SetPosition(RECT& rcPosition){ CopyRect(&m_rcPosition, &rcPosition); };
	void    SetPosition(int x, int y);
	void    SetPosition(POINT ptPosition);	
	
	void    OffsetPosition(int x, int y);//�ƶ�λ�ã��������
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

///////////////////////////////��add��///////////////////////////////////////

inline void Sprite::CalcCollisionRect()
{
	//ȱʡʵ��Ϊ����ײ���α�λ�þ���С1/6
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
	//���������ײ�����Ƿ����ص�
	RECT& rcTest = pTestSprite->GetCollision();
	return m_rcCollision.left <= rcTest.right && rcTest.left <= m_rcCollision.right &&
		m_rcCollision.top <= rcTest.bottom && rcTest.top <= m_rcCollision.bottom;
}

/////////////////////////////��add��//////////////////////////////////////

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
	CalcCollisionRect();//��add��
}

inline void Sprite::SetPosition(POINT ptPosition)
{
	OffsetRect(&m_rcPosition, ptPosition.x - m_rcPosition.left,
		ptPosition.y - m_rcPosition.top);
	CalcCollisionRect();//��add��
}

inline void Sprite::OffsetPosition(int x, int y)
{
	OffsetRect(&m_rcPosition, x, y);
	CalcCollisionRect();//��add��
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
