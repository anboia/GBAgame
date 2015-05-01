#ifndef GAME_STATE
#define GAME_STATE

#include "gba.h"
#include "text.h"
#include "game_controller.h"


typedef enum {
	SCREEN_1 = 0,
	SCREEN_2,
	SCREEN_3,
	SCREEN_4,
	SCREEN_5,
	SCREEN_6,
	SCREEN_7,
	SCREEN_8,
	SCREEN_9,
	SCREEN_10,
} screen_state;

// ========================================================
// ===== GLOBALS ==========================================


int frame;
screen_state	current_screen_state, next_screen_state;
ResourcePack	screen[10];
MapHandler		text_bg; // bg 0

// ========================================================
// ===== PROTOTYPES =======================================

void initMapHandler(MapHandler *bg, VIEWPORT *vp, u32 bgnr, u32 priority, u32 charBlock, u32 screenBlock, const void *bg_map, const void *bg_tiles, int sizeTiles, int map_width, int map_height);
void loadMapHandler(MapHandler *bg);
void initSpriteHandler(ResourcePack *current_screen, u16 *srcTiles, u32 dudeX, u32 dudeY);
void loadSpriteHandler(SpriteHandler *sh);
void loadScreen(ResourcePack * current_screen);
void initialize();
void checkStateChange();

void init_screen_1();
void update_screen_1();
void draw_screen_1();

void init_screen_2();
void update_screen_2();
void draw_screen_2();

void init_screen_3();
void update_screen_3();
void draw_screen_3();

void init_screen_4();
void update_screen_4();
void draw_screen_4();

void init_screen_5();
void update_screen_5();
void draw_screen_5();

void init_screen_6();
void update_screen_6();
void draw_screen_6();

void init_screen_7();
void update_screen_7();
void draw_screen_7();

void init_screen_8();
void update_screen_8();
void draw_screen_8();

void init_screen_9();
void update_screen_9();
void draw_screen_9();

void init_screen_10();
void update_screen_10();
void draw_screen_10();


#endif // GAME_STATE