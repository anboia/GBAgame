#include "game_state.h"

// ========================================================
// ===== main =============================================



int main() {
	initialize();
	loadScreen(&screen[current_screen_state]);
	while(1) {
		WaitVBlank();
		key_poll();


		// testing change between screen_1 and screen_2
		if(key_hit(KEY_A)){
			next_screen_state = (current_screen_state+1)%2;
		}

		switch(current_screen_state){
			case SCREEN_1: update_screen_1(); draw_screen_1(); break;
			case SCREEN_2: update_screen_2(); draw_screen_2(); break;
			case SCREEN_3: update_screen_3(); draw_screen_3(); break;
			case SCREEN_4: update_screen_4(); draw_screen_4(); break;
			case SCREEN_5: update_screen_5(); draw_screen_5(); break;
			case SCREEN_6: update_screen_6(); draw_screen_6(); break;
			case SCREEN_7: update_screen_7(); draw_screen_7(); break;
			case SCREEN_8: update_screen_8(); draw_screen_8(); break;
			case SCREEN_9: update_screen_9(); draw_screen_9(); break;
			case SCREEN_10: update_screen_10(); draw_screen_10(); break;
		}
		debug(0,0,current_screen_state);

		checkStateChange();

	}
	return 0;
}
