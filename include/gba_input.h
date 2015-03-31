#ifndef GBA_INPUT
#define GBA_INPUT

#include "gba_input.h"
#include "gba_types.h"
#include "gba_memory.h"

// ========================================================
// ===== DEFINES ==========================================

// ===== KEY INPUT
#define KEY_A        0x0001
#define KEY_B        0x0002
#define KEY_SELECT   0x0004
#define KEY_START    0x0008
#define KEY_RIGHT    0x0010
#define KEY_LEFT     0x0020
#define KEY_UP       0x0040
#define KEY_DOWN     0x0080
#define KEY_R        0x0100
#define KEY_L        0x0200

#define KEY_MASK		0x03FF


// ========================================================
// ===== GLOBALS ==========================================


extern u16 key_curr;
extern u16 key_prev;


// ========================================================
// ===== PROTOTYPES =======================================

// basic keystates

void key_poll();
INLINE u32 key_curr_state(void);
INLINE u32 key_prev_state(void);

INLINE u32 key_is_down(u32 key);
INLINE u32 key_is_up(u32 key);

INLINE u32 key_was_down(u32 key);
INLINE u32 key_was_up(u32 key);

// transitional keystates

INLINE u32 key_transit(u32 key);
INLINE u32 key_held(u32 key);
INLINE u32 key_hit(u32 key);
INLINE u32 key_released(u32 key);


// ========================================================
// ===== INLINES ==========================================

// Get current keystate
INLINE u32 key_curr_state(void)		{	return key_curr;				}

// Get previous key state
INLINE u32 key_prev_state(void)		{	return key_prev;				}

// Gives the keys of a key that are currently down
INLINE u32 key_is_down(u32 key)		{	return  key_curr & key;	}

// Gives the keys of a key that are currently up
INLINE u32 key_is_up(u32 key)		{	return ~key_curr & key;		}

// Gives the keys of a key that were previously down
INLINE u32 key_was_down(u32 key)	{	return  key_prev & key;	}

// Gives the keys of a key that were previously down
INLINE u32 key_was_up(u32 key)		{	return ~key_prev & key;	}



// Gives the keys of a key that are different from before
INLINE u32 key_transit(u32 key)
{	return ( key_curr ^  key_prev) & key;	}

// Gives the keys of a key that are being held down
INLINE u32 key_held(u32 key)
{	return ( key_curr &  key_prev) & key;	}

// Gives the keys of a key that are pressed (down now but not before)
INLINE u32 key_hit(u32 key)
{	return ( key_curr &~ key_prev) & key;	}

// Gives the keys of a key that are being released
INLINE u32 key_released(u32 key)
{	return (~key_curr &  key_prev) & key;	}



#endif // GBA_INPUT
