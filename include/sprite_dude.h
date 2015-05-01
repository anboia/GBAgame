#ifndef SPRITE_DUDE
#define SPRITE_DUDE
#include "gba.h"
#include "game_map.h"

// ========================================================
// ===== DEFINE ===========================================

enum LookDir
{
	LOOK_RIGHT= 0, LOOK_DOWN, LOOK_LEFT, LOOK_UP,
};

#define SPR_STATE_STAND		0x0100
#define SPR_STATE_WALK		0x0200


// character speed
// #define DUDE_SPEED				0x000F
#define DUDE_SPEED				0x0400




// ========================================================
// ===== PROTOTYPES =======================================

void dude_update(SpriteCharacter *dude, VIEWPORT *current_vp);

void dude_init(SpriteHandler *sh, VIEWPORT *current_vp, int x, int y, int obj_id);
void dude_set_state(SpriteCharacter *dude, u32 state);
void dude_input(SpriteCharacter *dude);

void dude_move(SpriteCharacter *dude);
void dude_animate(SpriteCharacter *dude);

void dude_ani_stand(SpriteCharacter *dude);
void dude_ani_walk(SpriteCharacter *dude);





#endif // SPRITE_DUDE