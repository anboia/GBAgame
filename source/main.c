#include "gba.h"



// ========================================================
// ===== GLOBALS ==========================================

int frame;

// ========================================================
// ===== general ==========================================

void init() {
	REG_DISPCNT = DCNT_MODE4 | DCNT_BG2;
	videoPage = backBuffer;
	frame = 0;
	// loadImg(10,50, 144, 16, frontBuffer, (u16*)frontBitmap);
	// loadPalette(frontPal, 8);
}


// ========================================================
// ===== main =============================================

int main() {

	init();

	while(1) {
		WaitVBlank();

		if((frame & 7) == 0) {
			key_poll();
		}

		if(key_hit(KEY_LEFT))	{
			DrawPixel4(50, 50, RGB8(1,0,0));
		}
		if(key_hit(KEY_RIGHT))	{
			FlipPage();
		}
		if(key_hit(KEY_UP))		{
		}
		if(key_hit(KEY_DOWN))	{
		}
		if(key_hit(KEY_L))		{
		}
		if(key_hit(KEY_R))		{
		}
		if(key_hit(KEY_A))		{
		}
		if(key_hit(KEY_B))		{
		}
		if(key_hit(KEY_SELECT))	{
		}
		if(key_hit(KEY_START))	{
		}

		frame++;
	}
	return 0;
}
