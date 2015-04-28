#ifndef GAME_MAP
#define GAME_MAP

#include "string.h"
#include "gba.h"

#include "Map_Palette.h"
#include "Road1.h"

// ========================================================
// ===== DEFINES ==========================================


// ========================================================
// ===== TYPES ============================================
typedef struct VIEWPORT
{
	int x, xmin, xmax, xpage;
	int y, ymin, ymax, ypage;
} VIEWPORT;

typedef struct MapInfo
{
	u16 bgnr;							// BG number
	u16 cnt;							// REG_BGxCNT

	// Destination data
	SCR_ENTRY *dstMap;		// Screenblock pointer
	// Source data
	SCR_ENTRY *srcMap;		// Source map address
	u32 srcMapWidth;			// Source map width  (pixels)
	u32 srcMapHeight;			// Source map height (pixels)
	s32 mapX;							// REG_BGxHOFS (X-coord on map)
	s32 mapY;							// REG_BGxVOFS (Y-coord on map)
} MapInfo;


// ========================================================
// ===== GLOBALS ==========================================
VIEWPORT		road1_vp;				// current viewport
MapInfo			text_bg;				// bg 0
MapInfo			road1_bg;				// bg 1
MapInfo			collision_bg;		// bg 2
MapInfo			water_bg;				// bg 3



// ========================================================
// ===== PROTOTYPES =======================================

INLINE void vp_center(VIEWPORT *vp, s32 x, s32 y);
void vp_set_pos(VIEWPORT *vp, s32 x, s32 y);

void bg_init(MapInfo *bgt, int bgnr, u32 ctrl, const void *map, u32 map_width, u32 map_height);
void bg_colcpy(MapInfo *bgt, int tx, int ty);
void bg_rowcpy(MapInfo *bgt, int tx, int ty);
void bg_update(MapInfo *bgt, VIEWPORT *vp);


// ========================================================
// ===== INLINES ==========================================

INLINE void vp_center(VIEWPORT *vp, int x, int y)
{	vp_set_pos(vp, x - vp->xpage/2, y - vp->ypage/2);	}





#endif // GAME_MAP