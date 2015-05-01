
//{{BLOCK(TestMap)

//======================================================================
//
//	TestMap, 1024x1024@8, 
//	+ palette 256 entries, not compressed
//	+ 353 tiles (t|f reduced) not compressed
//	+ regular map (flat), not compressed, 128x128 
//	Total size: 512 + 22592 + 32768 = 55872
//
//	Time-stamp: 2015-04-30, 16:06:58
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.12
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_TESTMAP_H
#define GRIT_TESTMAP_H

#define TestMapTilesLen 22592
extern const unsigned int TestMapTiles[5648];

#define TestMapMapLen 32768
extern const unsigned short TestMapMap[16384];

#define TestMapPalLen 512
extern const unsigned short TestMapPal[256];

#endif // GRIT_TESTMAP_H

//}}BLOCK(TestMap)
