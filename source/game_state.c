#include "game_state.h"


// maps
#include "Maps.h"
#include "Map_Palette.h"

#include "testMap.h"

//sprite data
#include "sprite_data_2d_8bpp.h"


// ============================================================================================== // ===== SCREEN 1
// ===== SCREEN 1 =============================================================================== // ===== SCREEN 1
u32 water_x = 0;
u32 water_y = 0;
void init_screen_1(){
	screen[SCREEN_1].vp = (VIEWPORT){
		0, 0, ROAD1_WIDTH<<3, 240,
		0, 0, ROAD1_HEIGHT<<3, 160,
	};
	// init backgrounds
	// bg1 Road1
	initMapHandler(	/*MapHandler*/ &screen[SCREEN_1].mh1, /*VIEWPORT*/ &screen[SCREEN_1].vp,
									/*bg num*/ 1, /*priority*/ 2, /*char block*/ 1, /*screen block*/ 31,
									Road1_Map, Road1_Tiles, sizeof(Road1_Tiles), ROAD1_WIDTH, ROAD1_HEIGHT);
	// bg2 Water
	initMapHandler(	/*MapHandler*/ &screen[SCREEN_1].mh2, /*VIEWPORT*/ NULL,
									/*bg num*/ 2, /*priority*/ 2, /*char block*/ 2, /*screen block*/ 30,
									Water_Map, Water_Tiles, sizeof(Water_Tiles), WATER_WIDTH, WATER_HEIGHT);
	screen[SCREEN_1].mh3.srcMap = NULL;

	// init sprites
	initSpriteHandler(&screen[SCREEN_1], (u16*)sprite_data_2d_8bppTiles, 120<<8, 80<<8);

	// points to background palette
	screen[SCREEN_1].palleteB = (u16*)Map_Palette;
	// points to sprite palette
	screen[SCREEN_1].palleteS = (u16*)sprite_data_2d_8bppPal;
}

void update_screen_1(){
	//update player position and change viewport
	dude_update(&screen[SCREEN_1].sh.dude, &screen[SCREEN_1].vp);

	/* update water background position */
	water_x += 20;
	water_y += 3;
	REG_BG_OFS[screen[SCREEN_1].mh2.bgnr].x= screen[SCREEN_1].mh2.mapX= (water_x>>8);
	REG_BG_OFS[screen[SCREEN_1].mh2.bgnr].y= screen[SCREEN_1].mh2.mapY= (water_y>>8);
}

void draw_screen_1(){
	// draw sprite to OAM
	updateSpriteMemory(screen[SCREEN_1].sh.oamBuff);

	/* update bacground screenblok. Sincronize the view region with vp (viewport) */
	bg_update(&screen[SCREEN_1].mh1, &screen[SCREEN_1].vp);
}

// ============================================================================================== // ===== SCREEN 2
// ===== SCREEN 2 =============================================================================== // ===== SCREEN 2
void init_screen_2(){
	screen[SCREEN_2].vp = (VIEWPORT){
		0, 0, 1024, 240,
		0, 0, 1024, 160,
	};

	// init backgrounds
	initMapHandler(	/*MapHandler*/ &screen[SCREEN_2].mh1, /*VIEWPORT*/ &screen[SCREEN_2].vp,
									/*bg num*/ 1, /*priority*/ 2, /*char block*/ 1, /*screen block*/ 30,
									TestMapMap, TestMapTiles, sizeof(TestMapTiles), 128, 128);
	screen[SCREEN_2].mh2.srcMap = NULL;
	screen[SCREEN_2].mh3.srcMap = NULL;

	// init sprites
	initSpriteHandler(&screen[SCREEN_2], (u16*)sprite_data_2d_8bppTiles, 120<<8, 80<<8);

	// points to background palette
	screen[SCREEN_2].palleteB = (u16*)TestMapPal;
	// points to sprite palette
	screen[SCREEN_2].palleteS = (u16*)sprite_data_2d_8bppPal;
}
void update_screen_2(){
	//update player position and change viewport
	dude_update(&screen[SCREEN_2].sh.dude, &screen[SCREEN_2].vp);
}
void draw_screen_2(){
	// draw sprite to OAM
	updateSpriteMemory(screen[SCREEN_2].sh.oamBuff);

	/* update bacground screenblok. Sincronize the view region with vp (viewport) */
	bg_update(&screen[SCREEN_2].mh1, &screen[SCREEN_2].vp);
}
// ============================================================================================== // ===== SCREEN 3
// ===== SCREEN 3 =============================================================================== // ===== SCREEN 3
void init_screen_3(){}
void update_screen_3(){}
void draw_screen_3(){}
// ============================================================================================== // ===== SCREEN 4
// ===== SCREEN 4 =============================================================================== // ===== SCREEN 4
void init_screen_4(){}
void update_screen_4(){}
void draw_screen_4(){}
// ============================================================================================== // ===== SCREEN 5
// ===== SCREEN 5 =============================================================================== // ===== SCREEN 5
void init_screen_5(){}
void update_screen_5(){}
void draw_screen_5(){}
// ============================================================================================== // ===== SCREEN 6
// ===== SCREEN 6 =============================================================================== // ===== SCREEN 6
void init_screen_6(){}
void update_screen_6(){}
void draw_screen_6(){}
// ============================================================================================== // ===== SCREEN 7
// ===== SCREEN 7 =============================================================================== // ===== SCREEN 7
void init_screen_7(){}
void update_screen_7(){}
void draw_screen_7(){}
// ============================================================================================== // ===== SCREEN 8
// ===== SCREEN 8 =============================================================================== // ===== SCREEN 8
void init_screen_8(){}
void update_screen_8(){}
void draw_screen_8(){}
// ============================================================================================== // ===== SCREEN 9
// ===== SCREEN 9 =============================================================================== // ===== SCREEN 9
void init_screen_9(){}
void update_screen_9(){}
void draw_screen_9(){}
// ============================================================================================== // ===== SCREEN 10
// ===== SCREEN 10 =============================================================================== // ===== SCREEN 10
void init_screen_10(){}
void update_screen_10(){}
void draw_screen_10(){}



// ========================================================
// ===== FUNCTIONS ========================================



/* initialize background variables */
void initMapHandler(MapHandler *bg, VIEWPORT *vp, u32 bgnr, u32 priority, u32 charBlock, u32 screenBlock, const void *bg_map, const void *bg_tiles, int sizeTiles, int map_width, int map_height){
	u32 ctrl = BG_CBB(charBlock) | BG_SBB(screenBlock) | BG_COLOR256 | TEXTBG_SIZE_256x256 | priority;

	bg->bgnr					= bgnr;
	bg->cnt						= ctrl;

	bg->mapX					= 0;
	bg->mapY					= 0;

	bg->vp = vp;

	bg->dstMap				= se_mem[BFN_GET(ctrl, BG_SBB)]; // get destination addres (screen block address)
	bg->srcMap				= (SCR_ENTRY*)bg_map;
	bg->srcMapWidth		= map_width;
	bg->srcMapHeight	= map_height;
	bg->srcTiles			= (SCR_ENTRY*)bg_tiles;
	bg->sizeTiles 		= sizeTiles;

	bg->numPortals = 0;
	bg->portals = NULL;
}

/* load the background in VRAM (map and tiles) , must be previously initialized*/
void loadMapHandler(MapHandler *bg){
	// load tiles in charblock
	DMAFastCopy((void*) bg->srcTiles, (void*) charBaseBlock(BFN_GET(bg->cnt, BG_CBB)), bg->sizeTiles, DMA_32NOW);

	// Load Map in screenblock
	SCR_ENTRY *dst= bg->dstMap, *src= bg->srcMap;
	int ix, iy;
	int tvx = (bg->vp->x)>>3, tvy= (bg->vp->y)>>3;

	// put back to VRAM map screenblock
	for(iy=tvy; iy<32+tvy; iy++)
		for(ix=tvx; ix<32+tvx; ix++)
			dst[(iy&31)*32+(ix&31)]= src[iy*bg->srcMapWidth+ix];

	// Load Regs
	REG_BGCNT[bg->bgnr]			= bg->cnt;
	REG_BG_OFS[bg->bgnr].x	= bg->mapX = bg->vp->x;
	REG_BG_OFS[bg->bgnr].y	= bg->mapY = bg->vp->y;
}

/* initialize sprites variables*/
void initSpriteHandler(ResourcePack *current_screen, u16 *srcTiles, u32 dudeX, u32 dudeY){
	oam_init( current_screen->sh.oamBuff );
	current_screen->sh.srcTiles = srcTiles;
	dude_init(&current_screen->sh, &current_screen->vp, dudeX, dudeY, 0);
}

void loadSpriteHandler(SpriteHandler *sh){
	DMAFastCopy((void*) sh->srcTiles, (void*) spriteData, 4096, DMA_32NOW);
	updateSpriteMemory(sh->oamBuff);
}

void loadScreen(ResourcePack * current_screen){
	REG_DISPCNT = MODE_0 | BG0_ENABLE | OBJ_ENABLE | OBJ_MAP_2D;

	// load palletes
	DMAFastCopy((void*) current_screen->palleteB, (void*) BGPaletteMem, 128, DMA_32NOW);
	DMAFastCopy((void*) current_screen->palleteS, (void*) SPaletteMem,  128, DMA_32NOW);

	// load backgrounds if srcMap != NULL
	if(current_screen->mh1.srcMap)loadMapHandler(&current_screen->mh1), REG_DISPCNT |= BG1_ENABLE;
	if(current_screen->mh2.srcMap)loadMapHandler(&current_screen->mh2), REG_DISPCNT |= BG2_ENABLE;
	if(current_screen->mh3.srcMap)loadMapHandler(&current_screen->mh3), REG_DISPCNT |= BG3_ENABLE;

	// load sprites
	loadSpriteHandler(&current_screen->sh);

	init_text();
}

void initialize(){
	REG_DISPCNT = MODE_0 | BG0_ENABLE | OBJ_ENABLE | OBJ_MAP_2D;
	// REG_DISPCNT = MODE_0 | BG0_ENABLE | BG1_ENABLE  | OBJ_ENABLE | OBJ_MAP_2D;
	next_screen_state = current_screen_state = SCREEN_1;
	frame = 0;

	init_screen_1();
	init_screen_2();
	init_screen_3();
	init_screen_4();
	init_screen_5();
	init_screen_6();
	init_screen_7();
	init_screen_8();
	init_screen_9();
	init_screen_10();
}

void checkStateChange(){
	if(next_screen_state != current_screen_state){
		current_screen_state = next_screen_state;
		loadScreen(&screen[current_screen_state]);
	}
}
