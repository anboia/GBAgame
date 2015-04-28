#include "gba.h"
#include "text.h"

// maps
#include "game_map.h"

// sprites
#include "sprite_dude.h"

//sprite data
#include "sprite_data_2d_8bpp.h"


// ========================================================
// ===== GLOBALS ==========================================


int frame;


// SCENE 1
SpriteInfo	road1_dude;			// sprite user


// ========================================================
// ===== general ==========================================
void init_scene_1(){
	REG_DISPCNT = MODE_0 | BG1_ENABLE;
	// bg1
	DMAFastCopy((void*) Map_Palette, (void*) BGPaletteMem, 128, DMA_32NOW);
	DMAFastCopy((void*) Road1_Tiles, (void*) charBaseBlock(0), sizeof(Road1_Tiles)>>2, DMA_32NOW);
	bg_init(&road1_bg, 1, BG_CBB(0) | BG_SBB(20) | BG_COLOR256 | TEXTBG_SIZE_256x256, Road1_Map, ROAD1_WIDTH, ROAD1_HEIGHT);

	REG_DISPCNT |= OBJ_ENABLE | OBJ_MAP_2D;
	// sprite
	oam_init();
	DMAFastCopy((void*) sprite_data_2d_8bppPal, (void*) SPaletteMem, 128, DMA_32NOW);
	DMAFastCopy((void*) sprite_data_2d_8bppTiles, (void*) spriteData, 1024, DMA_32NOW);
	dude_init(&road1_dude, 120<<8, 80<<8, 0);
}


void init() {

	init_scene_1();

	// init_text();
	// print_box("- Hi! how are you?\n\n- I am fine and you?\n\n- Well, today I'm having a lot of fun doing the final project! game programing rocks!! :D");
	// print_box("- Well, today I'm having a lot of fun doing the final project! game programing rocks!! :D");

	frame = 0;
}


// ========================================================
// ===== main =============================================

int main() {

	init();

	int x, y;

	while(1) {
		WaitVBlank();

		key_poll();

		dude_input(&road1_dude);
		dude_animate(&road1_dude);
		dude_move(&road1_dude);

		x= road1_dude.x>>8, y= road1_dude.y>>8;

		vp_center(&road1_vp, x, y);
		updateSpriteMemory();

		bg_update(&road1_bg, &road1_vp);


		// switch(state){

		// }


		frame++;
	}
	return 0;
}
