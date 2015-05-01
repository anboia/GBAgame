#ifndef GBA_SPRITE
#define GBA_SPRITE

#include "gba.h"

// ========================================================
// ===== DEFINES ==========================================
/* OAM */
#define oamMem ((u16*) 0x7000000)
/* Sprite image data */
#define spriteData ((u16*) 0x6010000)
/* Sprite palette */
#define SPaletteMem ((u16*) 0x5000200)
/* Constants */
#define OBJ_MAP_1D 0x40
#define OBJ_MAP_2D 0x0
#define OBJ_ENABLE 0x1000

#define TID_2D(i,j) ((i<<5)+j)

/* Attribute 0 */
#define MODE_NORMAL				 0				// Regular object
#define ROTATION_FLAG			0x0100		// Affine object
#define MODE_TRANSPARENT	0x0200		// Inactive object
#define ATTR0_AFF_DBL			0x0300		// Double-size affine object
#define SIZE_DOUBLE				0x0200
#define ATTR0_BLEND				0x0400		// Enable blend
#define MODE_WINDOWED			0x0800		// Use for object window
#define MOSAIC						0x1000		// Enable mosaic
#define COLOR_16					0					// Use 4bpp (16 color) tiles
#define COLOR_256					0x2000		// Use 8bpp (256 color) tiles
#define SQUARE						0					// Square shape
#define WIDE							0x4000		// Tall shape (height &gt; width)
#define TALL							0x8000		// Wide shape (height &lt; width)

#define ATTR0_Y_MASK		0x00FF
#define ATTR0_Y_SHIFT			 0
#define ATTR0_Y(n)			((n)<<ATTR0_Y_SHIFT)


/* Attribute 1 */
#define ROTDATA(n) ((n) << 9)
#define HORIZONTAL_FLIP		0x1000	// Horizontal flip (reg obj only)
#define VERTICAL_FLIP			0x2000	// Vertical flip (reg obj only)
#define SIZE_8			 0
#define SIZE_16		0x4000
#define SIZE_32		0x8000
#define SIZE_64		0xC000

#define ATTR1_X_MASK		0x01FF
#define ATTR1_X_SHIFT			 0
#define ATTR1_X(n)			((n)<<ATTR1_X_SHIFT)

#define ATTR1_FLIP_MASK		0x3000
#define ATTR1_FLIP_SHIFT		12
#define ATTR1_FLIP(n)		((n)<<ATTR1_FLIP_SHIFT)

/* Attribute 2 */
#define PRIORITY(n) ((n) << 10)
#define PALETTE(n) ((n) << 12)



// ========================================================
// ===== PROTOTYPES =======================================

INLINE void updateSpriteMemory();
void oam_init(Sprite * oamBuff);

// ========================================================
// ===== INLINES ==========================================

INLINE void updateSpriteMemory(Sprite *oamBuff) {
	// memcpy(oamMem, oamBuff, 512);
	DMAFastCopy((void*) oamBuff, (void*) oamMem, 128, DMA_32NOW);
}


#endif // GBA_SPRITE