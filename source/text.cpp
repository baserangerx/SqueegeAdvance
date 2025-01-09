#include <gba_video.h>
#include <gba_sprites.h>
#include <string.h>
#include <math.h>
#include "font.h"
#include "text.h"

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


dialogueBox::dialogueBox(u16 x, u16 y, u16 width, u16 height, u16 dla)
{
	delay = dla;
	xPos = x;
	yPos = y;
	sizeX = width;
	sizeY = height;
}
void dialogueBox::Print(const char* txt)
{
	text = (char*)malloc(sizeof(char)*sizeX*sizeY);

	for(int i = 0, j = 1, k = 0; txt[i] != 0; i++)
	{
		if(txt[i] == ' ')
		{
			while(!(txt[i + j] == ' ' || txt[i+j] == 0))
			{
				j++;
			}
			//if (txt[i+j] == 0) break;
			if((i + j + k)/(1+floor((i+k)/sizeX)) > sizeX)
			{
				while((i + k) % sizeX != 0)
				{
					text[i+k] = ' ';
					k++;
					/*
					once_i_was_nine_years_old
					15
					6
					0


					10
					1
					2
					Welcome/to///
					the/internet.../
					*/
				}
				
			}
			j = 1;
		}

		text[i+k] = txt[i];
		if ((i + k) % sizeX == 0 && txt[i] == ' ') k--;

	}
	
	letter = 0;
}
void dialogueBox::Step(const long frame)
{
	if(frame % delay == 0)
	{
		if(strlen(text) - letter)
		{
			((u16*)SCREEN_BASE_BLOCK(8))[letter + (xPos - (int)floor(letter/sizeX)*sizeX) + (yPos + (2)*(int)floor(letter/sizeX))*32] = text[letter]-32;
			letter++;
		}
		else
		{
			free(text);
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
