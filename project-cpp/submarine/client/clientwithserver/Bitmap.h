#pragma once


#include <windows.h>

//λͼ��
class Bitmap
{
protected:
	HBITMAP m_hBitmap;		//λͼ���
	int m_iWidth, m_iHeight;	//��ȣ��߶�

	void Free();

public:
	//���ļ��м���λͼ
	Bitmap(HDC hDC, LPTSTR szFileName);
	//����Դ�м���λͼ
	Bitmap(HDC hDC, UINT uiResID, HINSTANCE hInstance);
	//���ڴ��д���һ�ſ�λͼ���������ɫcrColor
	Bitmap(HDC hDC, int iWidth, int iHeight, COLORREF crColor = RGB(0, 0, 0));

	virtual ~Bitmap();

	BOOL LoadFromFile(HDC hDC, LPTSTR szFileName);
	BOOL Create(HDC hDC, int iWidth, int iHeight, COLORREF crColor);
	BOOL Create(HDC hDC, UINT uiResID, HINSTANCE hInstance);

	//void kill();
	//��λͼ
	void Draw(HDC hDC, int x, int y);
	//��͸��λͼ
	void Draw(HDC hDC, int x, int y, bool bTrans, COLORREF crTransColor);

	//�Զ���֡��֧��
	void DrawPart(HDC hDC, int x, int y, int xPart, int yPart,int wPart, int hPart, bool bTrans, COLORREF crTransColor);

	// ��ȡλͼ�ĸߺͿ�
	int  GetWidth() { return m_iWidth; };
	int  GetHeight() { return m_iHeight; };
};