#ifndef TEXT
#define TEXT
#include "gba.h"
#include "font.h"
#include "stdarg.h"


// ========================================================
// ===== DEFINES ==========================================

#define DIALOG_WIDTH 28

// Tiles Offset
#define TILE_ASCI_TRAN 0
#define TILE_ASCI_OPAC 95
#define TILE_BORDER_1 190
#define TILE_BORDER_2 199

// Borders offset
#define BORDER_TOP_LEFT			0
#define BORDER_TOP					1
#define BORDER_TOP_RIGHT		2
#define BORDER_LEFT 				3
#define BORDER_MIDDLE				4
#define BORDER_RIGHT 				5
#define BORDER_BOTTOM_LEFT 	6
#define BORDER_BOTTOM 			7
#define BORDER_BOTTOM_RIGHT	8

#define PALETTE_START	253 // PALLETE COLLOR START
#define PALETTE_SIZE	3
#define COLLOR_BORDER	253
#define COLLOR_TEXT		254
#define COLLOR_BACK		255



#define TEXT_SBB 30
#define TEXT_CBB 0

/*
	EXAMPLE USAGE
	print dialog with two story. press KEY_A to continue
	print_story(2, "- Hi! how are you?\n\n- I am fine and you?\n\n- Well, today I'm having a lot of fun doing the final project! game programing rocks!! :D", "- Well, today I'm having a lot of fun doing the final project! game programing rocks!! :D");

	// draw a box
	draw_box(18, TILE_ASCI_OPAC);

	print(2,1,"  asdfasdf l", TILE_ASCI_OPAC);
*/



// ========================================================
// ===== GLOBALS ==========================================



// ========================================================
// ===== PROTOTYPES =======================================
void print(int x, int y, const char *str, int type);
void draw_box(int hight, int type);
void init_text();
void reset_text();
void print_story( int num, ... );


#endif // TEXT