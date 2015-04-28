#include "sprite_dude.h"
#include "game_map.h"

// Default link attributes
const Sprite dudeObjs[1]=
{
	{	0 | MODE_NORMAL | COLOR_256 | TALL, SIZE_32, 0, 0	},
};


void dude_init(SpriteInfo *dude, int x, int y, int dude_id)
{
	dude->x= x;
	dude->y= y;
	dude->vx= dude->vy= 0;

	dude_set_state(dude, SPR_STATE_STAND);
	dude->dir= LOOK_RIGHT;
	dude->objId= dude_id;

	// oam_copy(&obj_buffer[obj_id], cLinkObjs, 3);
	// memset(oamBuff,0xff,sizeof(oamBuff));

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

	if( !key_is_down(KEY_RIGHT) )
		dude_set_state(dude, SPR_STATE_STAND);

	if( key_hit(KEY_RIGHT) )
		dude_set_state(dude, SPR_STATE_WALK);
}

void dude_move(SpriteInfo *dude)
{
	// collision testing here

	dude->x += dude->vx;
	dude->y += dude->vy;
}

void dude_animate(SpriteInfo *dude){
	Sprite *obj= &oamBuff[dude->objId];
	PT pt= { (dude->x>>8)-road1_vp.x, (dude->y>>8) - road1_vp.y };
	BFN_SET(obj[0].attribute0, pt.y, ATTR0_Y);
	BFN_SET(obj[0].attribute1, pt.x, ATTR1_X);

}
