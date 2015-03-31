#ifndef GBA_VIDEO
#define GBA_VIDEO

#include "gba_types.h"
#include "gba_memory.h"
#include "gba_core.h"



// ========================================================
// ===== DEFINES ==========================================
#define SCREEN_WIDTH	240
#define SCREEN_HEIGHT	160

#define COL_BLACK   0x0000
#define COL_RED     0x001F
#define COL_LIME    0x03E0
#define COL_YELLOW  0x03FF
#define COL_BLUE    0x7C00
#define COL_MAG     0x7C1F
#define COL_CYAN    0x7FE0
#define COL_WHITE   0x7FFF

#define videoBuffer	((u16*)MEM_VRAM)
#define frontBuffer	((u16*)MEM_VRAM)
#define backBuffer	((u16*)MEM_VRAM_BACK)
#define paletteMem	((u16*)MEM_PAL)

// ========================================================
// ===== GLOBALS ==========================================

// ========================================================
// ===== PROTOTYPES =======================================
INLINE void WaitVBlank();
void FlipPage();

INLINE void DrawPixel4(int x, int y, COLOR clr);
INLINE COLOR RGB15(u32 red, u32 green, u32 blue);
INLINE COLOR RGB8(u8 red, u8 green, u8 blue);

// ========================================================
// ===== INLINES ==========================================

// vid_vsync
INLINE void WaitVBlank()
{
	while(REG_VCOUNT >= 160);   // wait till VDraw
	while(REG_VCOUNT < 160);    // wait till VBlank
}



INLINE void DrawPixel4(int x, int y, COLOR clr){
	// u16 offset = (y * 120 + x);
	u16 offset = (y * 240 + x) >> 1;
	if (x & 1)
		videoPage[offset] = (videoPage[offset] & 0x00FF) | (clr << 8);
	else
		videoPage[offset] = (videoPage[offset] & 0xFF00) | clr;
}


INLINE COLOR RGB15(u32 red, u32 green, u32 blue)
{	return red | (green<<5) | (blue<<10);	}

INLINE COLOR RGB8(u8 red, u8 green, u8 blue)
{	return  (red>>3) + ((green>>3)<<5) + ((blue>>3)<<10);	}

#endif // GBA_VIDEO