#include "text.h"
#include "string.h"

#define DIALOG_WIDTH 28
#define TILE_ASCI_TRAN 0
#define TILE_ASCI_OPAC 104
#define TILE_BORDER_1 95
#define TILE_BORDER_2 0

// ========================================================
// ===== STRUCTS ==========================================


// ========================================================
// ===== GLOBALS ==========================================


// ========================================================
// ===== FUNCTIONS ========================================
void print(int x, int y, const char *str, int type)
{
	int c;
	SCR_ENTRY *dst = &se_mem[30][y*32+x];

	x=0;
	while((c=*str++) != 0)
	{
		if(c == '\n')
		{
			while(x<26)dst[x++] = type;
			dst += (2&~31) + 32;    x=0;    }
		else
			dst[x++] = c-32+type;
	}
}
void set_tile(int x, int y, int id){
	se_mem[30][y*32+x] = id;
}
void draw_box(int h){
	int top = 20-h-2, left = 1, bottom = 19, right = 28, i;

	set_tile(left, top, TILE_BORDER_1);
	set_tile(right, top, TILE_BORDER_1+2);
	set_tile(right, bottom, TILE_BORDER_1+8);
	set_tile(left, bottom, TILE_BORDER_1+6);
	for (i = left+1; i < right; ++i)
	{
		set_tile(i,top,TILE_BORDER_1+1);
		set_tile(i,bottom,TILE_BORDER_1+7);
	}
	for (i = top+1; i < bottom; ++i)
	{
		set_tile(left,i,98);
		set_tile(right,i,100);
	}
}

void print_box(const char *str){
	// int n = strlen(str);
	// int i = 0, j = 0, p = 0, line = 0;
	// int w = DIALOG_WIDTH - 2;
	// char buff[1000];
	// memset(buff,0,sizeof buff);
	// while(i < n){
	// 	int k = min(i+w,n);
	// 	while(k>i && str[k]!=' ' && str[k]!='\0' )k--;
	// 	if(k==i){
	// 		k = w;
	// 	}else{
	// 		k -=i;
	// 	}
	// 	for (j = 0; j < k; ++j, p++)
	// 	{
	// 		buff[p] = str[i+j];
	// 	}
	// 	buff[p++] = '\n';
	// 	i+=k;
	// }
	// for ( i = 0; buff[i]; ++i)
	// {
	// 	if (buff[i] == '\n')
	// 	{
	// 		line++;
	// 	}
	// }

	// print( 2, 19 - line, buff, TILE_ASCI_OPAC);
	// draw_box(line);
	int n = strlen(str);
	int i = 0, j = 0, p = 0, line = 0;
	int w = DIALOG_WIDTH - 2;
	char buff[1000];
	memset(buff,0,sizeof buff);
	while(i < n){
		int k = min(i+w,n);
		for ( j = i; j < k; ++j)
			if(str[j]=='\n')
				k = j + 1;
		while(k>i && str[k]!=' ' && str[k]!='\0' && str[k]!='\n')
			k--;
		if(k==i)
			k = j-i;
		else
			k -=i;
		for (j = 0; j < k; ++j, p++)
			buff[p] = str[i+j];
		if(buff[p]!='\n')
			buff[p++] = '\n';
		i += k + 1;
	}
	for ( i = 0; buff[i]; ++i)
		if (buff[i] == '\n')
			line++;

	print( 2, 19 - line, buff, TILE_ASCI_OPAC);
	draw_box(line);
}


void init_text(){
	REG_BG0CNT = BG_CBB(0) | BG_SBB(30) | BG_COLOR256 | TEXTBG_SIZE_256x256;
	REG_DISPCNT = DCNT_MODE0 | DCNT_BG0;
	// Load palette
	memcpy(paletteMem, fontPal, fontPalLen);
	// Load tiles into CBB 0
	memcpy(&tile_mem[0][0], fontTiles, fontTilesLen);

}