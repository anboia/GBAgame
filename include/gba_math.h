#ifndef GBA_MATH
#define GBA_MATH

#include "gba_types.h"

// ========================================================
// ===== DEFINES ==========================================


// ========================================================
// ===== GLOBALS ==========================================


// ========================================================
// ===== PROTOTYPES =======================================
INLINE int min(int a, int b);
INLINE int max(int a, int b);
INLINE int int_abs(int a);
int int_sqrt(int x);
INLINE int clamp(int x, int min, int max);

// ========================================================
// ===== INLINES ==========================================

INLINE int min(int a, int b){	return a<b?a:b;	}

INLINE int max(int a, int b){	return a>b?a:b;	}

INLINE int int_abs(int a){	return a<0?-a:a;	}

// Truncates x to stay in range [ min, max )
INLINE int clamp(int x, int min, int max)
{	return (x>=max) ? (max-1) : ( (x<min) ? min : x );	}

#endif // GBA_MATH