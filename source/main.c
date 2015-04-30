#include "gba.h"
#include "text.h"

// maps
#include "game_map.h"

// sprites
#include "sprite_dude.h"

//sprite data
#include "sprite_data_2d_8bpp.h"

// ========================================================
// ===== TYPES ============================================

typedef enum {
	SCENE_1 = 0,
	SCENE_2,
	SCENE_3,
} scene_state;


// ========================================================
// ===== GLOBALS ==========================================

scene_state current_scene;

int frame;

// ========================================================
// ===== SCENE 1 ==========================================

void init_scene_1(){


	REG_DISPCNT = MODE_0 | BG1_ENABLE | BG0_ENABLE;

	// bg1
	DMAFastCopy((void*) Map_Palette, (void*) BGPaletteMem, 128, DMA_32NOW);
	DMAFastCopy((void*) Road1_Tiles, (void*) charBaseBlock(1), sizeof(Road1_Tiles)>>2, DMA_32NOW);
	bg_init(&road1_bg, 1, BG_CBB(1) | BG_SBB(29) | BG_COLOR256 | TEXTBG_SIZE_256x256 | 2, Road1_Map, ROAD1_WIDTH, ROAD1_HEIGHT);

	// bg0
	init_text();

	REG_DISPCNT |= OBJ_ENABLE | OBJ_MAP_2D;
	// sprite
	oam_init();
	DMAFastCopy((void*) sprite_data_2d_8bppPal, (void*) SPaletteMem, 128, DMA_32NOW);
	DMAFastCopy((void*) sprite_data_2d_8bppTiles, (void*) spriteData, 4096, DMA_32NOW);
	dude_init(&road1_dude, 120<<8, 80<<8, 0);

	// draw_box(18, TILE_ASCI_OPAC);
	print_story(2, "- Hi! how are you?\n\n- I am fine and you?\n\n- Well, today I'm having a lot of fun doing the final project! game programing rocks!! :D", "- Well, today I'm having a lot of fun doing the final project! game programing rocks!! :D");

}

void update_scene_1(){
	int x, y;
	dude_input(&road1_dude);
	dude_animate(&road1_dude);
	dude_move(&road1_dude);

	x= road1_dude.x>>8, y= road1_dude.y>>8;
	vp_center(&road1_vp, x, y);
}

void draw_scene_1(){
	updateSpriteMemory();
	bg_update(&road1_bg, &road1_vp);
}

// ========================================================
// ===== SCENE 2 ==========================================
void init_scene_2(){}
void update_scene_2(){}
void draw_scene_2(){}
// ========================================================
// ===== SCENE 3 ==========================================
void init_scene_3(){}
void update_scene_3(){}
void draw_scene_3(){}


// ========================================================
// ===== general ==========================================

void init() {
	current_scene = SCENE_1;
	frame = 0;
}

// ========================================================
// ===== main =============================================

int main() {

	init();
	switch(current_scene){
		case SCENE_1: init_scene_1();
		case SCENE_2: init_scene_2();
		case SCENE_3: init_scene_3();
	}

	while(1) {
		WaitVBlank();
		key_poll();

		switch(current_scene){
			case SCENE_1: update_scene_1(); draw_scene_1(); break;
			case SCENE_2: update_scene_2(); draw_scene_2(); break;
			case SCENE_3: update_scene_3(); draw_scene_3(); break;
		}

		frame++;
	}
	return 0;
}
