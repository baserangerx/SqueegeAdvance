#include <gba_video.h>
#include <gba_sprites.h>
#include <string.h>
#include "font.h"

/*
void load()
{
    memcpy(BG_PALETTE, textPAL, 32);
    u16* a = (u16*)VRAM;
    for(int hl = 0; hl < 192; hl++)
    {
        for(int row = 0; row < 4; row++)
        {
            for(int col = 0; col < 2; col++)
            {
                a[(col + 2*row + 2*4*hl)] = ((toncfontTiles[hl] >> (col*4+row*8)) & 0b1);
                a[(col + 2*row + 2*4*hl)] |= (((toncfontTiles[hl] >> (col*4+row*8)) & 0b10))<<3;
                a[(col + 2*row + 2*4*hl)] |= (((toncfontTiles[hl] >> (col*4+row*8)) & 0b100))<<6;
                a[(col + 2*row + 2*4*hl)] |= (((toncfontTiles[hl] >> (col*4+row*8)) & 0b1000))<<9;
            }
        }
    }
}
*/

void load()
{
	REG_BG0CNT = BG_PRIORITY(0) | CHAR_BASE(0) | BG_16_COLOR | SCREEN_BASE(8) | BG_SIZE_0;

    memcpy(BG_PALETTE, textPAL, 32);
    //u32* a = (u32*)CHAR_BASE_BLOCK(0);
    for (int hl = 0; hl < 192; hl++)
    {
        for (int row = 0; row < 4; row++)
        {
            ((u32*)CHAR_BASE_BLOCK(0))[(row + 4 * hl)] = 0;
            for (int col = 0; col < 8; col++)
            {
                ((u32*)CHAR_BASE_BLOCK(0))[(row + 4 * hl)] |= ((toncfontTiles[hl] >> (row * 8)) & (0b1 << col)) << (3 * col);
            }
        }
    }
}

static const char* text = NULL;
static int i = 0;
static int delay;
void print(const char* txt, const int DLA)
{
	text = txt;
	i = 0;
	delay = DLA;
}

void step(const int frame)
{
	if(frame % delay == 0)
	{
		if(strlen(text) - i)
		{
			((u16*)SCREEN_BASE_BLOCK(8))[i] = text[i]-32;
			i++;
		}
	}
}
/*
0 0 0 1 1 0 0 0
0001 1000
0001 1000
0001 1000

1000000000000
0000000000001

*/
