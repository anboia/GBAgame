#ifndef GBA_TYPES
#define GBA_TYPES

// ========================================================
// ===== TYPES ============================================

typedef unsigned char   u8;
typedef unsigned short  u16;
typedef unsigned int    u32;

typedef volatile u8  vu8;
typedef volatile u16 vu16;
typedef volatile u32 vu32;

typedef u16 COLOR;

typedef u8 bool;
#define TRUE 1
#define FALSE 0

#define INLINE static inline

typedef u16 SCR_ENTRY, SE;
typedef struct { u32 data[8];  } TILE, TILE4;
typedef struct { u32 data[16]; } TILE8;
typedef SCR_ENTRY	SCREENBLOCK[1024];
typedef TILE			CHARBLOCK[512];


#endif // GBA_TYPES