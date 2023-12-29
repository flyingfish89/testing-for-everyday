
#include "Sprite.h"
class AlienSprite : public Sprite
{
public:
    AlienSprite(Bitmap* pBitmap, int row, int col, RECT& rcBounds, BOUNDSACTION baBoundsAction = BA_STOP);
    virtual ~AlienSprite();

    virtual SPRITEACTION Update();

    virtual Sprite* AddNewSprite(Bitmap* bmp);
};

