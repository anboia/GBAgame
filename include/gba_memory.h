#ifndef GBA_MEMORY
#define GBA_MEMORY



// ========================================================
// ===== DEFINES ==========================================

// === MEMMAP ===========================================

// REG_DISPCNT
#define MODE_0				0x0000
#define MODE_1				0x0001
#define MODE_2				0x0002
#define MODE_3				0x0003
#define MODE_4				0x0004
#define MODE_5				0x0005

// layers
#define BG0_ENABLE		0x0100
#define BG1_ENABLE		0x0200
#define BG2_ENABLE		0x0400
#define BG3_ENABLE		0x0800
#define OBJ_ENABLE		0x1000



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

#define DCNT_PAGE				0x0010

// --- VRAM ---
// tile_mem[y] = TILE[]   (char block y)
// tile_mem[y][x] = TILE (char block y, tile x)
#define tile_mem		( (CHARBLOCK*)MEM_VRAM)
#define tile8_mem		((CHARBLOCK8*)MEM_VRAM)

// se_mem[y] = SB_ENTRY[] (screen block y)
// se_mem[y][x] = screen entry (screen block y, screen entry x)
#define se_mem			((SCREENBLOCK*)MEM_VRAM)


// BACKGROUND ==================================================================
/* Scrolling BG defines */
#define REG_BG_OFS			((BG_POINT*)(MEM_IO+0x0010)) // Bg scroll array

#define REG_BG0HOFS			*(vu16*)(MEM_IO+0x0010) // bg 0-3 origins
#define REG_BG0VOFS			*(vu16*)(MEM_IO+0x0012)
#define REG_BG1HOFS			*(vu16*)(MEM_IO+0x0014)
#define REG_BG1VOFS			*(vu16*)(MEM_IO+0x0016)
#define REG_BG2HOFS			*(vu16*)(MEM_IO+0x0018)
#define REG_BG2VOFS			*(vu16*)(MEM_IO+0x001A)
#define REG_BG3HOFS			*(vu16*)(MEM_IO+0x001C)
#define REG_BG3VOFS			*(vu16*)(MEM_IO+0x001E)

/* BG Setup defines */
#define REG_BGCNT				((vu16*)(MEM_IO+0x0008)) // Bg control array
#define REG_BG0CNT			*(vu16*)(MEM_IO+0x0008) // bg 0-3 control
#define REG_BG1CNT			*(vu16*)(MEM_IO+0x000A)
#define REG_BG2CNT			*(vu16*)(MEM_IO+0x000C)
#define REG_BG3CNT			*(vu16*)(MEM_IO+0x000E)
#define BG_COLOR16		0x0000
#define BG_COLOR256		0x0080
#define CHAR_SHIFT 2
#define SCREEN_SHIFT 8
#define WRAPAROUND 0x1

//background tile bitmap sizes
#define TEXTBG_SIZE_256x256 0x0
#define TEXTBG_SIZE_256x512	0x8000
#define TEXTBG_SIZE_512x256	0x4000
#define TEXTBG_SIZE_512x512	0xC000

/* Misc BG defines */
#define BGPaletteMem ((u16*) 0x5000000)
#define charBaseBlock(n) (((n)*0x4000)+0x6000000)
#define screenBaseBlock(n) (((n)*0x800)+0x6000000)

#define BG_CBB_MASK		0x000C
#define BG_CBB_SHIFT		 2
#define BG_CBB(n)		((n)<<CHAR_SHIFT)
#define BG_SBB_MASK		0x1F00
#define BG_SBB_SHIFT		 8
#define BG_SBB(n)		((n)<<SCREEN_SHIFT)

#define BFN_PREP(x, name)	( ((x)<<name##_SHIFT) & name##_MASK )
#define BFN_GET(y, name)	( ((y) & name##_MASK)>>name##_SHIFT )
#define BFN_SET(y, x, name)	(y = ((y)&~name##_MASK) | BFN_PREP(x,name) )
#define BFN_CMP(y, x, name)	( ((y)&name##_MASK) == (x) )

/* DMA Fast Copy defines */
#define REG_DMA3SAD *(vu32*) 0x40000D4
#define REG_DMA3DAD *(vu32*) 0x40000D8
#define REG_DMA3CNT *(vu32*) 0x40000DC
#define DMA_ENABLE 0x80000000
#define DMA_TIMING_IMMEDIATE 0x00000000
#define DMA_16 0x00000000
#define DMA_32 0x04000000
#define DMA_32NOW (DMA_ENABLE | DMA_TIMING_IMMEDIATE | DMA_32)
#define DMA_16NOW (DMA_ENABLE | DMA_TIMING_IMMEDIATE | DMA_16)

// ========================================================
// ===== GLOBALS ==========================================



// ========================================================
// ===== PROTOTYPES =======================================
// INLINE void DMAFastCopy(void* src, void* dest, unsigned int count, unsigned int mode);


// ========================================================
// ===== INLINES ==========================================

INLINE void DMAFastCopy(void* src, void* dest, unsigned int count, unsigned int mode) {
	if(mode == DMA_16NOW || mode == DMA_32NOW) {
		REG_DMA3SAD = (unsigned int) src;
		REG_DMA3DAD = (unsigned int) dest;
		REG_DMA3CNT = count | mode;
	}
}


#endif // GBA_MEMORY