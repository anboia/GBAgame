#include "gba_video.h"

// ========================================================
// ===== GLOBALS ==========================================

COLOR * videoPage;

// ========================================================
// ===== FUNCTIONS ========================================

void FlipPage(){
	videoPage = (u16*)((u32)videoPage ^ VRAM_PAGE_SIZE);
	REG_DISPCNT ^= DCNT_PAGE;
}


