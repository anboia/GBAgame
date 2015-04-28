#ifndef SPRITE_DUDE
#define SPRITE_DUDE
#include "gba.h"

// ========================================================
// ===== DEFINE ===========================================

enum LookDir
{
	LOOK_RIGHT= 0, LOOK_DOWN, LOOK_LEFT, LOOK_UP,
};

#define SPR_STATE_STAND		0x0100
#define SPR_STATE_WALK		0x0200

#define DUDE_SPEED				0x00D0


// ========================================================
// ===== GLOBALS ==========================================

SpriteInfo	road1_dude;			// sprite user

// ========================================================
// ===== PROTOTYPES =======================================


void dude_init(SpriteInfo *dude, int x, int y, int obj_id);
void dude_set_state(SpriteInfo *dude, u32 state);
void dude_input(SpriteInfo *dude);

void dude_move(SpriteInfo *dude);
void dude_animate(SpriteInfo *dude);

void dude_ani_stand(SpriteInfo *dude);
void dude_ani_walk(SpriteInfo *dude);





#endif // SPRITE_DUDE