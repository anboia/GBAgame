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

#endif // GBA_TYPES