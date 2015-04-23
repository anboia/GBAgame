#include "gba.h"
#include "text.h"



// ========================================================
// ===== GLOBALS ==========================================

int frame;



// ========================================================
// ===== general ==========================================

void init() {
	init_text();
	print_box("- Hi! how are you?\n\n- I am fine and you?\n\n- Well, today I'm having a lot of fun doing the final project! game programing rocks!! :D");
	// print_box("- Well, today I'm having a lot of fun doing the final project! game programing rocks!! :D");

	frame = 0;
}


// ========================================================
// ===== main =============================================

int main() {

	init();

	while(1) {
		WaitVBlank();

		if((frame & 7) == 0)
		{
			key_poll();
		}

		// switch(state){

		// }


		frame++;
	}
	return 0;
}
