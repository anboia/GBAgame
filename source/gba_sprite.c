#include "gba_sprite.h"
#include "string.h"

// ========================================================
// ===== FUNCTIONS ========================================


void oam_init(Sprite *oamBuff)
{
	Sprite *obj1= oamBuff;
	Sprite *obj2= (Sprite*)oamMem;
	int i;
	for (i = 0; i < 128; i++)
	{
		obj1[i].attribute0 = (1<<9);
		obj2[i].attribute0 = (1<<9);
	}
	updateSpriteMemory(oamBuff);
}

