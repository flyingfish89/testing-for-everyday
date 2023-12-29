#pragma once


#include <windows.h>

//位图类
class Bitmap
{
protected:
	HBITMAP m_hBitmap;		//位图句柄
	int m_iWidth, m_iHeight;	//宽度，高度

	void Free();

public:
	//从文件中加载位图
	Bitmap(HDC hDC, LPTSTR szFileName);
	//从资源中加载位图
	Bitmap(HDC hDC, UINT uiResID, HINSTANCE hInstance);
	//在内存中创建一张空位图，并填充颜色crColor
	Bitmap(HDC hDC, int iWidth, int iHeight, COLORREF crColor = RGB(0, 0, 0));

	virtual ~Bitmap();

	BOOL LoadFromFile(HDC hDC, LPTSTR szFileName);
	BOOL Create(HDC hDC, int iWidth, int iHeight, COLORREF crColor);
	BOOL Create(HDC hDC, UINT uiResID, HINSTANCE hInstance);

	//void kill();
	//画位图
	void Draw(HDC hDC, int x, int y);
	//画透明位图
	void Draw(HDC hDC, int x, int y, bool bTrans, COLORREF crTransColor);

	//对动画帧的支持
	void DrawPart(HDC hDC, int x, int y, int xPart, int yPart,int wPart, int hPart, bool bTrans, COLORREF crTransColor);

	// 获取位图的高和宽
	int  GetWidth() { return m_iWidth; };
	int  GetHeight() { return m_iHeight; };
};