#ifndef GBA_MEMORY
#define GBA_MEMORY



// ========================================================
// ===== DEFINES ==========================================

// === MEMMAP ===========================================

// REG_DISPCNT
#define DCNT_MODE0			0x0000
#define DCNT_MODE1      0x0001
#define DCNT_MODE2      0x0002
#define DCNT_MODE3      0x0003
#define DCNT_MODE4      0x0004
#define DCNT_MODE5      0x0005

#define DCNT_PAGE				0x0010

// layers
#define DCNT_BG0				0x0100
#define DCNT_BG1				0x0200
#define DCNT_BG2				0x0400
#define DCNT_BG3				0x0800
#define DCNT_OBJ				0x1000


// main sections
#define MEM_IO					0x04000000
#define MEM_VRAM				0x06000000 // video Buffer
#define MEM_PAL					0x05000000 // Palette

// main sections sizes
#define PAL_SIZE				0x00400
#define VRAM_SIZE				0x18000

#define VRAM_PAGE_SIZE	0x0A000

#define MEM_VRAM_BACK	(MEM_VRAM + VRAM_PAGE_SIZE)

// registers
#define REG_DISPCNT     *((vu32*)(MEM_IO+0x0000))
#define REG_KEY     		*((vu32*)(MEM_IO+0x0130))
#define REG_VCOUNT 			*((vu16*)(MEM_IO+0x0006))

// background
#define REG_BG0CNT			*(vu16*)(MEM_IO+0x0008)	// bg 0-3 control
#define REG_BG1CNT			*(vu16*)(MEM_IO+0x000A)
#define REG_BG2CNT			*(vu16*)(MEM_IO+0x000C)
#define REG_BG3CNT			*(vu16*)(MEM_IO+0x000E)

#define REG_BG0HOFS			*(vu16*)(MEM_IO+0x0010)		// bg 0-3 origins
#define REG_BG0VOFS			*(vu16*)(MEM_IO+0x0012)
#define REG_BG1HOFS			*(vu16*)(MEM_IO+0x0014)
#define REG_BG1VOFS			*(vu16*)(MEM_IO+0x0016)
#define REG_BG2HOFS			*(vu16*)(MEM_IO+0x0018)
#define REG_BG2VOFS			*(vu16*)(MEM_IO+0x001A)
#define REG_BG3HOFS			*(vu16*)(MEM_IO+0x001C)
#define REG_BG3VOFS			*(vu16*)(MEM_IO+0x001E)

//background tile bitmap sizes
#define TEXTBG_SIZE_256x256 0x0
#define TEXTBG_SIZE_256x512	0x8000
#define TEXTBG_SIZE_512x256	0x4000
#define TEXTBG_SIZE_512x512	0xC000

// util
#define BG_COLOR16		0x0080
#define BG_COLOR256		0x0080

#define BG_CBB_MASK		0x000C
#define CHAR_SHIFT 2
#define BG_CBB(n)		((n)<<CHAR_SHIFT)

#define BG_SBB_MASK		0x1F00
#define SCREEN_SHIFT 8
#define BG_SBB(n)		((n)<<SCREEN_SHIFT)

#define CharBaseBlock(n) (((n)*0x4000)+0x6000000)
#define ScreenBaseBlock(n) (((n)*0x800)+0x6000000)



// --- VRAM ---
// tile_mem[y] = TILE[]   (char block y)
// tile_mem[y][x] = TILE (char block y, tile x)
#define tile_mem		( (CHARBLOCK*)MEM_VRAM)
#define tile8_mem		((CHARBLOCK8*)MEM_VRAM)

// se_mem[y] = SB_ENTRY[] (screen block y)
// se_mem[y][x] = screen entry (screen block y, screen entry x)
#define se_mem			((SCREENBLOCK*)MEM_VRAM)


// ========================================================
// ===== GLOBALS ==========================================



// ========================================================
// ===== PROTOTYPES =======================================



#endif // GBA_MEMORY