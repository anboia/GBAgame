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


// ========================================================
// ===== GLOBALS ==========================================



// ========================================================
// ===== PROTOTYPES =======================================



#endif // GBA_MEMORY