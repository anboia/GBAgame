#include "game_map.h"

// ========================================================
// ===== STRUCTS ==========================================


// ========================================================
// ===== GLOBALS ==========================================
VIEWPORT road1_vp = {
	// 0, 0, 1024, 240,
	// 0, 0, 1024, 160,
	0, 0, ROAD1_WIDTH<<3, 240,
	0, 0, ROAD1_HEIGHT<<3, 160,
};

// ========================================================
// ===== FUNCTIONS ========================================

void vp_set_pos(VIEWPORT *vp, int x, int y)
{
	vp->x= clamp(x, vp->xmin, vp->xmax - vp->xpage);
	vp->y= clamp(y, vp->ymin, vp->ymax - vp->ypage);
}

void bg_init(MapInfo *bg, int bgnr, u32 ctrl, const void *map, u32 map_width, u32 map_height)
{
	memset(bg, 0, sizeof(MapInfo));

	bg->bgnr= bgnr;
	bg->cnt= ctrl;
	bg->dstMap= se_mem[BFN_GET(ctrl, BG_SBB)];

	REG_BGCNT[bgnr]= ctrl;
	REG_BG_OFS[bgnr].x= 0;
	REG_BG_OFS[bgnr].y= 0;

	bg->srcMap= (SCR_ENTRY*)map;
	bg->srcMapWidth= map_width;
	bg->srcMapHeight= map_height;

	int ix, iy;
	SCR_ENTRY *dst= bg->dstMap, *src= bg->srcMap;
	for(iy=0; iy<32; iy++)
		for(ix=0; ix<32; ix++)
			dst[iy*32+ix]= src[	iy*bg->srcMapWidth+ix];
}

void bg_colcpy(MapInfo *bg, int tx, int ty)
{
	int iy, y0= ty&31;

	int srcP= bg->srcMapWidth;
	SCR_ENTRY *srcL= &bg->srcMap[ty*srcP + tx];
	SCR_ENTRY *dstL= &bg->dstMap[y0*32 + (tx&31)];

	for(iy=y0; iy<32; iy++)
	{	*dstL= *srcL;	dstL += 32;	srcL += srcP;	}

	dstL -= 1024;

	for(iy=0; iy<y0; iy++)
	{	*dstL= *srcL;	dstL += 32;	srcL += srcP;	}
}

void bg_rowcpy(MapInfo *bg, int tx, int ty)
{
	int ix, x0= tx&31;

	int srcP= bg->srcMapWidth;
	SCR_ENTRY *srcL= &bg->srcMap[ty*srcP + tx];
	SCR_ENTRY *dstL= &bg->dstMap[(ty&31)*32 + x0];

	for(ix=x0; ix<32; ix++)
		*dstL++= *srcL++;

	dstL -= 32;

	for(ix=0; ix<x0; ix++)
		*dstL++= *srcL++;
}

void bg_update(MapInfo *bg, VIEWPORT *vp)
{
	// Pixel coords
	int vx= vp->x, vy= vp->y;
	int bx= bg->mapX, by= bg->mapY;

	// Tile coords
	int tvx= vx>>3, tvy= vy>>3;
	int tbx= bx>>3, tby= by>>3;

	if(tvx < tbx)							// add on left
		bg_colcpy(bg, tvx, tvy);
	else if(tvx > tbx)				// add on right
		bg_colcpy(bg, tvx+31, tvy);

	if(tvy < tby)							// add on top
		bg_rowcpy(bg, tvx, tvy);
	else if(tvy > tby)				// add on bottom
		bg_rowcpy(bg, tvx, tvy+31);

	// Update MapInfo and reg-offsets
	int bgnr= bg->bgnr;
	REG_BG_OFS[bgnr].x= bg->mapX= vx;
	REG_BG_OFS[bgnr].y= bg->mapY= vy;
}
