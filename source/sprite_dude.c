#include "sprite_dude.h"
#include "game_map.h"

// Default link attributes
Sprite dudeObjs[1]=
{
	{	0 | MODE_NORMAL 		 | COLOR_256 | TALL, SIZE_32, TID_2D(0,0)| 1<<11, 0	},
};

const u32 id_stand[4]= { TID_2D(4,0), TID_2D(0,0), TID_2D(4,0), TID_2D(8,0) };
const u32 id_walk[4][8]= {
 {TID_2D(4,4), TID_2D(4,4), TID_2D(4,0), TID_2D(4,0), TID_2D(4,8), TID_2D(4,8), TID_2D(4,8), TID_2D(4,0)},
 {TID_2D(0,4), TID_2D(0,4), TID_2D(0,0), TID_2D(0,0), TID_2D(0,8), TID_2D(0,8), TID_2D(0,8), TID_2D(0,0)},
 {TID_2D(4,4), TID_2D(4,4), TID_2D(4,0), TID_2D(4,0), TID_2D(4,8), TID_2D(4,8), TID_2D(4,8), TID_2D(4,0)},
 {TID_2D(8,4), TID_2D(8,4), TID_2D(8,0), TID_2D(8,0), TID_2D(8,8), TID_2D(8,8), TID_2D(8,8), TID_2D(8,0)},
};

void dude_init(SpriteHandler *sh, VIEWPORT *current_vp, int x, int y, int dude_id)
{
	sh->dude.current_vp = current_vp;

	sh->dude.x= x;
	sh->dude.y= y;
	sh->dude.vx= sh->dude.vy= 0;
	sh->dude.cx = -8;
	sh->dude.cy = -16;

	dude_set_state(&sh->dude, SPR_STATE_STAND);
	sh->dude.dir 	= LOOK_RIGHT;
	sh->dude.objId = dude_id;
	sh->dude.oamBuff = sh->oamBuff;

	DMAFastCopy(dudeObjs, &(sh->oamBuff[dude_id]), 2, DMA_32NOW);
}
void dude_update(SpriteCharacter *dude, VIEWPORT *vp){

	int x, y;
	dude_input(dude);
	dude_animate(dude);
	dude_move(dude);

	x= (dude->x)>>8, y= (dude->y)>>8;
	vp_center(vp, x, y);
}
void dude_set_state(SpriteCharacter *dude, u32 state)
{
	dude->state= state;
	dude->aniFrame= 0;
}
void dude_input(SpriteCharacter *dude)
{
	dude->vx= dude->vy= 0;

	if( key_is_down(KEY_RIGHT) )
	{
		dude->vx= DUDE_SPEED;
		dude->dir= LOOK_RIGHT;
	}
	else if( key_is_down(KEY_LEFT) )
	{
		dude->vx= -DUDE_SPEED;
		dude->dir= LOOK_LEFT;
	}

	if( key_is_down(KEY_DOWN) )
	{
		dude->vy= DUDE_SPEED;
		dude->dir= LOOK_DOWN;
	}
	else if( key_is_down(KEY_UP) )
	{
		dude->vy= -DUDE_SPEED;
		dude->dir= LOOK_UP;
	}

	if( !key_is_down(KEY_DIR) )
		dude_set_state(dude, SPR_STATE_STAND);

	if( key_hit(KEY_DIR) )
		dude_set_state(dude, SPR_STATE_WALK);
}

void dude_move(SpriteCharacter *dude)
{
	// collision testing here

	dude->x += dude->vx;
	dude->y += dude->vy;
}

void dude_animate(SpriteCharacter *dude){
	switch(dude->state)
	{
	case SPR_STATE_STAND:
		dude_ani_stand(dude);
		break;
	case SPR_STATE_WALK:
		dude->aniFrame += DUDE_SPEED/3;
		dude_ani_walk(dude);
	}
}

void dude_ani_stand(SpriteCharacter *dude){
	Sprite *obj= &dude->oamBuff[dude->objId];
	PT pt = { (dude->x>>8) - dude->current_vp->x+dude->cx, (dude->y>>8) - dude->current_vp->y +dude->cy};
	int dir = dude->dir;

	BFN_SET(obj[0].attribute0, pt.y, ATTR0_Y);
	BFN_SET(obj[0].attribute1, pt.x, ATTR1_X);
	BFN_SET(obj[0].attribute1,    0, ATTR1_FLIP);
	obj[0].attribute2 = id_stand[dir] | 1<<11;
	if(dir == LOOK_LEFT) obj[0].attribute1 |= HORIZONTAL_FLIP;

}
void dude_ani_walk(SpriteCharacter *dude){
	Sprite *obj= &dude->oamBuff[dude->objId];
	PT pt = { (dude->x>>8)- dude->current_vp->x+dude->cx, (dude->y>>8) - dude->current_vp->y +dude->cy};
	int dir = dude->dir;
	int frame = (dude->aniFrame>>8) & 7;

	BFN_SET(obj[0].attribute0, pt.y, ATTR0_Y);
	BFN_SET(obj[0].attribute1, pt.x, ATTR1_X);
	BFN_SET(obj[0].attribute1,    0, ATTR1_FLIP);
	obj[0].attribute2 = id_walk[dir][(frame)] |  1<<11;
	if(dir == LOOK_LEFT) obj[0].attribute1 |= HORIZONTAL_FLIP;

}
