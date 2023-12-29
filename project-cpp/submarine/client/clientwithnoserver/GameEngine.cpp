#include "GameEngine.h"


vector<Sprite*>     m_vSprites;
//������������

UINT m_uiMIDIPlayerID = 0;

/*
����MIDI����
*/

// ��������
void PlayMIDISong(LPTSTR szMIDIFileName, BOOL hRestart)
{
	if (m_uiMIDIPlayerID == 0) {
		MCI_OPEN_PARMS mciOpenParms;
		mciOpenParms.lpstrDeviceType = "sequencer";
		mciOpenParms.lpstrElementName = szMIDIFileName;
		/*if (mciSenCommand(NULL, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT,(DWORD)&mciOpenParms) == 0) {

		}*/
	}
}


// ������л���
void CleanupSprites()
{
	// Delete and remove the sprites in the sprite vector
	vector<Sprite*>::iterator siSprite;  // ����ָ���������ͨ���������������
	for (siSprite = m_vSprites.begin(); siSprite != m_vSprites.end(); siSprite++)
	{
		// ɾ�������ľ���
		delete (*siSprite);
		//	m_vSprites.erase(siSprite);
		//	siSprite--;
	}
	// ���û����������
	m_vSprites.clear();
}





BOOL CheckSpriteCollsion(Sprite* pTestSprite)
{
	// See if the sprite has collided with any other sprites
	vector<Sprite*>::iterator siSprite;
	for (siSprite = m_vSprites.begin(); siSprite != m_vSprites.end(); siSprite++)
	{
		// Make sure not to check for collision with itself
		if (pTestSprite == (*siSprite))
			continue;

		// Test the collision
		if (pTestSprite->TestCollision(*siSprite))
			// Collision detected
			return SpriteCollisin((*siSprite), pTestSprite);
	}

	// No collision
	return FALSE;
}
void AddSprite(Sprite* pSprite)
{
	if (pSprite != NULL)
	{
		// See if there are sprites already in the sprite vector
		if (m_vSprites.size() > 0)
		{
			// Find a spot in the sprite vector to insert the sprite by its z-order
			vector<Sprite*>::iterator siSprite;
			for (siSprite = m_vSprites.begin(); siSprite != m_vSprites.end(); siSprite++)
				if (pSprite->GetZOrder() < (*siSprite)->GetZOrder())
				{
					// Insert the sprite into the sprite vector
					m_vSprites.insert(siSprite, pSprite);
					return;
				}
		}

		// The sprite's z-order is highest, so add it to the end of the vector
		m_vSprites.push_back(pSprite);
	}
}



void DrawSprites(HDC hDC)
{
	// Draw the sprites in the sprite vector
	vector<Sprite*>::iterator siSprite;
	for (siSprite = m_vSprites.begin(); siSprite != m_vSprites.end(); siSprite++)
		(*siSprite)->Draw(hDC);
}


void UpdateSprites()
{
	// Check to see if the sprite vector needs to grow
	if (m_vSprites.size() >= (m_vSprites.capacity() / 2))
		m_vSprites.reserve(m_vSprites.capacity() * 2);

	// Update the sprites in the sprite vector
	RECT          rcOldSpritePos;
	SPRITEACTION  saSpriteAction;
	vector<Sprite*>::iterator siSprite;
	for (siSprite = m_vSprites.begin(); siSprite != m_vSprites.end(); siSprite++)
	{
		// Save the old sprite position in case we need to restore it
		rcOldSpritePos = (*siSprite)->GetPosition();

		// Update the sprite
		saSpriteAction = (*siSprite)->Update();


		if (saSpriteAction & SA_ADDSPRITE)
		{
			//��Ҫ�����µľ���
			Sprite*tomb = (*siSprite)->AddNewSprite(g_pTorpedoBitmap);
			AddSprite(tomb);
		}


		// Handle the SA_KILL sprite action
		if (saSpriteAction & SA_KILL)
		{
			delete (*siSprite);
			siSprite = m_vSprites.erase(siSprite);
			//if (siSprite != m_vSprites.begin())
				siSprite--;
			continue;
		}

		// See if the sprite collided with any others
		if (CheckSpriteCollsion(*siSprite))
			// Restore the old sprite position
			(*siSprite)->SetPosition(rcOldSpritePos);
	}
}



Sprite* IsPointInSprite(int x, int y)
{
	// See if the point is in a sprite in the sprite vector
	vector<Sprite*>::reverse_iterator siSprite;
	for (siSprite = m_vSprites.rbegin(); siSprite != m_vSprites.rend(); siSprite++)
		if (!(*siSprite)->IsHidden() && (*siSprite)->IsPointInside(x, y))
			return (*siSprite);

	// The point is not in a sprite
	return NULL;
}