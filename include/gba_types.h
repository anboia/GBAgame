#ifndef GBA_TYPES
#define GBA_TYPES

// ========================================================
// ===== TYPES ============================================

typedef unsigned char				u8;
typedef unsigned short			u16;
typedef unsigned int				u32;
typedef unsigned long long	u64;

typedef signed char			s8;
typedef signed short		s16;
typedef signed int			s32;

typedef volatile u8			vu8;
typedef volatile u16		vu16;
typedef volatile u32		vu32;

typedef u16							COLOR;
typedef u8							bool;

#define TRUE 			1
#define FALSE 		0

#define ALIGN4		__attribute__((aligned(4)))
#define INLINE		static inline

typedef struct { u32 data[8];  } TILE, TILE4;
typedef struct { u32 data[16]; } TILE8;
typedef u16				SCR_ENTRY;
typedef SCR_ENTRY	SCREENBLOCK[1024];
typedef TILE			CHARBLOCK[512];
typedef TILE8			CHARBLOCK8[256];

typedef struct BG_POINT { s16 x, y; } ALIGN4 BG_POINT, PT;

typedef struct VIEWPORT
{
	int x, xmin, xmax, xpage;
	int y, ymin, ymax, ypage;
} VIEWPORT;

typedef struct Sprite {
	/* Attribute 0: Color mode, sprite shape, y location */
	u16 attribute0;
	/* Attribute 1: Base size, horizontal & vertical flip, x location */
	u16 attribute1;
	/* Attribute 2: Image location, priority */
	u16 attribute2;
	u16 attribute3;
} ALIGN4 Sprite;

typedef struct SpriteCharacter
{
	VIEWPORT *current_vp;
	s32			x, y;			// Position
	s32			vx, vy;		// Velocity
	u16			state;		// Sprite state
	u8			dir;			// Look direction
	u8			objId;		// Object index
	s32			aniFrame;	// Animation frame counter
	s32 		cx, cy;		// Center offset

	Sprite *oamBuff;
} SpriteCharacter;


/* Bounding boxes for sprites and portals */
typedef struct boundingBox {
	int y, ySize, x, xSize;
} boundingBox;

/* Portal for region movement */
typedef struct Portal {
	boundingBox* hitbox;
	int destination;
	int destX, destY;
} Portal;

/* Holds all necessary information for the different maps (Ground, Water, Hitmap, Unused) */
typedef struct MapHandler {
	u16 bgnr;							// BG number
	u16 cnt;							// REG_BGxCNT
	s32 mapX;							// REG_BGxHOFS (X-coord on map)
	s32 mapY;							// REG_BGxVOFS (Y-coord on map)
	VIEWPORT *vp;					// Map VIEWPORT

	// Destination data
	SCR_ENTRY *dstMap;		// Screenblock pointer
	// Source data
	SCR_ENTRY *srcMap;		// Source map address
	u32 srcMapWidth;			// Source map width  (pixels)
	u32 srcMapHeight;			// Source map height (pixels)
	SCR_ENTRY *srcTiles;	// Source tiles address
	u32 sizeTiles;

	int numPortals;
	Portal* portals;
} MapHandler;

/* Holds all the information for the current screen tiles */
typedef struct SpriteHandler {
	Sprite oamBuff[128];		// current OAM buffer
	SpriteCharacter dude;		// Main Character
	SCR_ENTRY *srcTiles;		// Tiles Data (2D)
} SpriteHandler;

/* Holds all the information for the game */
typedef struct ResourcePack {
	// MapHandler *mh0; /* Text -> handled diferently */
	MapHandler mh1;		/* Ground */
	MapHandler mh2;		/* Hitmap */
	MapHandler mh3;		/* Water */
	SpriteHandler sh; /* Sprites */

	VIEWPORT vp;

	u16* palleteS; // sprite pallete
	u16* palleteB; // background pallete
} ResourcePack;


#endif // GBA_TYPES