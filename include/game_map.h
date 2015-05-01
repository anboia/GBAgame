#ifndef GAME_MAP
#define GAME_MAP

#include "string.h"
#include "gba.h"

// ========================================================
// ===== PROTOTYPES =======================================

INLINE void vp_center(VIEWPORT *vp, s32 x, s32 y);
void vp_set_pos(VIEWPORT *vp, s32 x, s32 y);

void bg_init(MapHandler *bgt, int bgnr, u32 ctrl, const void *map, u32 map_width, u32 map_height);
void bg_colcpy(MapHandler *bgt, int tx, int ty);
void bg_rowcpy(MapHandler *bgt, int tx, int ty);
void bg_update(MapHandler *bgt, VIEWPORT *vp);


// ========================================================
// ===== INLINES ==========================================

INLINE void vp_center(VIEWPORT *vp, int x, int y)
{	vp_set_pos(vp, x - vp->xpage/2, y - vp->ypage/2);	}





#endif // GAME_MAP