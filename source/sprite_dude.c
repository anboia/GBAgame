#include "sprite_dude.h"
#include "game_map.h"

// Default link attributes
const Sprite dudeObjs[1]=
{
	{	0 | MODE_NORMAL 		 | COLOR_256 | TALL, SIZE_32, TID_2D(0,0), 0	},
};

const u32 id_stand[4]= { TID_2D(4,0), TID_2D(0,0), TID_2D(4,0), TID_2D(8,0) };
const u32 id_walk[4][8]= {
 {TID_2D(4,4), TID_2D(4,4), TID_2D(4,4), TID_2D(4,4), TID_2D(4,8), TID_2D(4,8), TID_2D(4,8), TID_2D(4,8)},
 {TID_2D(0,4), TID_2D(0,4), TID_2D(0,4), TID_2D(0,4), TID_2D(0,8), TID_2D(0,8), TID_2D(0,8), TID_2D(0,8)},
 {TID_2D(4,4), TID_2D(4,4), TID_2D(4,4), TID_2D(4,4), TID_2D(4,8), TID_2D(4,8), TID_2D(4,8), TID_2D(4,8)},
 {TID_2D(8,4), TID_2D(8,4), TID_2D(8,4), TID_2D(8,4), TID_2D(8,8), TID_2D(8,8), TID_2D(8,8), TID_2D(8,8)},
};

void dude_init(SpriteInfo *dude, int x, int y, int dude_id)
{
	dude->x= x;
	dude->y= y;
	dude->vx= dude->vy= 0;
	dude->cx = -8;
	dude->cy = -16;

	dude_set_state(dude, SPR_STATE_STAND);
	dude->dir 	= LOOK_RIGHT;
	dude->objId = dude_id;

	DMAFastCopy(dudeObjs, &oamBuff[dude_id], 2, DMA_32NOW);
}

void dude_set_state(SpriteInfo *dude, u32 state)
{
	dude->state= state;
	dude->aniFrame= 0;
}
void dude_input(SpriteInfo *dude)
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

void dude_move(SpriteInfo *dude)
{
	// collision testing here

	dude->x += dude->vx;
	dude->y += dude->vy;
}

void dude_animate(SpriteInfo *dude){
	switch(dude->state)
	{
	case SPR_STATE_STAND:
		dude_ani_stand(dude);
		break;
	case SPR_STATE_WALK:
		dude->aniFrame += 0x56;
		dude_ani_walk(dude);
	}
}

void dude_ani_stand(SpriteInfo *dude){
	Sprite *obj= &oamBuff[dude->objId];
	PT pt = { (dude->x>>8)-road1_vp.x+dude->cx, (dude->y>>8) - road1_vp.y +dude->cy};
	int dir = dude->dir;

	BFN_SET(obj[0].attribute0, pt.y, ATTR0_Y);
	BFN_SET(obj[0].attribute1, pt.x, ATTR1_X);
	BFN_SET(obj[0].attribute1,    0, ATTR1_FLIP);
	obj[0].attribute2 = id_stand[dir];
	if(dir == LOOK_LEFT) obj[0].attribute1 |= HORIZONTAL_FLIP;

}
void dude_ani_walk(SpriteInfo *dude){
	Sprite *obj= &oamBuff[dude->objId];
	PT pt = { (dude->x>>8)-road1_vp.x+dude->cx, (dude->y>>8) - road1_vp.y +dude->cy};
	int dir = dude->dir;
	int frame = (dude->aniFrame>>8) & 7;

	BFN_SET(obj[0].attribute0, pt.y, ATTR0_Y);
	BFN_SET(obj[0].attribute1, pt.x, ATTR1_X);
	BFN_SET(obj[0].attribute1,    0, ATTR1_FLIP);
	obj[0].attribute2 = id_walk[dir][(frame)];
	if(dir == LOOK_LEFT) obj[0].attribute1 |= HORIZONTAL_FLIP;

}
