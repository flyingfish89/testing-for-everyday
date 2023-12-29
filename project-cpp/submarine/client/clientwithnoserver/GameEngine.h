#pragma once

#include "Sprite.h"

#include<vector>

using namespace std;

#define KEYDOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEYUP(vk_code)   ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)


extern HWND g_hWnd;

extern UINT m_uiMIDIPlayerID;

void PlayMIDISong(LPTSTR szMIDIFileName = TEXT(""), BOOL bRestart = TRUE);

void ReplayMIDISong();
void PauseMIDISong();
void CloseMIDIPlayer();

//���������

extern Bitmap* g_pTorpedoBitmap;//ˮ��λͼ

extern vector<Sprite*> m_Sprites;

//������ײ��Ӧ�ӿڣ����ض�����Ϸʵ��
BOOL SpriteCollisin(Sprite* pSpriteHitter, Sprite* pSpriteHittee);

BOOL CheckSpriteCollsion(Sprite* pTestSprite);

void AddSprite(Sprite* pSprite);

void DrawSprites(HDC hDc);

void UpdateSprites();

void CleanupSprites();

Sprite* IsPointInSprite(int x, int y);
