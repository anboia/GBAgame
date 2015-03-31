#include "gba_math.h"

// ========================================================
// ===== FUNCTIONS ========================================

int int_sqrt(int x)
{
	int i = 1;
	int j = x;
	int k = i + ((j-i)>>1);
	while(i<j){
		k = i + ((j-i)>>1);
		if( k*k > x ) j = k;
		else i = k + 1;
	}

   return k;
}
