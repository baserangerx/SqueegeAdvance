#include <gba_video.h>
#include <gba_sprites.h>
#include <string.h>
#include <math.h>
#include "font.h"
#include "UI.h"
#include "text.h"

void loadText()
{
	REG_BG0CNT = BG_PRIORITY(0) | CHAR_BASE(0) | BG_16_COLOR | SCREEN_BASE(8) | BG_SIZE_0;

    memcpy(BG_PALETTE, UIPal, UIPalLen);
	//memcpy((u8*)BG_PALETTE + 0x20, UIPal, 32);
    //u32* a = (u32*)CHAR_BASE_BLOCK(0);

    for (int hl = 2; hl < 192; hl++)
    {
        for (int row = 0; row < 4; row++)
        {
            ((u32*)CHAR_BASE_BLOCK(0))[(row + 4 * hl)] = 0;
            for (int col = 0; col < 8; col++)
            {
                ((u32*)CHAR_BASE_BLOCK(0))[(row + 4 * hl)] |= (((toncfontTiles[hl] >> (row * 8)) & (0b1 << col)) > 0 ? ((toncfontTiles[hl] >> (row * 8)) & (0b1 << col)) : 2<<col) << (3 * col);
            }
        }
    }
	memcpy((u8*)CHAR_BASE_BLOCK(0) + 0xc00, UITiles, UITilesLen);
	
}


dialogueBox::dialogueBox(u16 x, u16 y, u16 width, u16 height, u16 dla)
{
	delay = dla;
	xPos = x;
	yPos = y;
	sizeX = width;
	sizeY = height;

	for (int row = 0; row < sizeY/2+1; row++)
	{
		for (int col = 0; col < sizeX/2+1; col++)
		{
			int tile = 0;
			if((row == 0 || row == sizeY/2)&&(col == 0 || col == sizeX/2))
			{
				tile = 0;
			}
			else if(row == 0 || row == sizeY/2)
			{
				tile = 1;
			}
			else if(col == 0 || col == sizeX/2)
			{
				tile = 3;
			}
			else
			{
				tile = 4;
			}
			bool flipX = col > sizeX/2-1;
			bool flipY = row > sizeY/2-1;

			((u16*)SCREEN_BASE_BLOCK(8))[(row*2 + yPos - 1)*32+col*2+(32*flipY)+flipX] = (96+tile*4) | flipX<<10 | flipX<<10 | flipY<<11;
			((u16*)SCREEN_BASE_BLOCK(8))[(row*2 + yPos - 1)*32+col*2+(32*flipY)+!flipX] = (96+1+tile*4) | flipX<<10 | flipY<<11;
			((u16*)SCREEN_BASE_BLOCK(8))[(row*2 + yPos - 1)*32+col*2+(32*!flipY)+flipX] = (96+2+tile*4) | flipX<<10 | flipY<<11;
			((u16*)SCREEN_BASE_BLOCK(8))[(row*2 + yPos - 1)*32+col*2+(32*!flipY)+!flipX] = (96+3+tile*4) | flipX<<10 | flipY<<11;
		}
	}
}


void dialogueBox::Page(const u16 page)
{
	Clear();
	switch (page)
	{
		case 0:
			*((vu16*)0x5000002) = 0b0000000000011111;
			break;
		case 1:
			*((vu16*)0x5000002) = 0b0000001111100000;
			break;
		case 2:
			*((vu16*)0x5000002) = 0b0111110000000000;
			break;
	};
}

void dialogueBox::Print(const char* txt)
{
	Clear();
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
	if(text == NULL) return;
	if(frame % delay == 0)
	{
		if(strlen(text) - letter)
		{
			lockInput = 1;
			((u16*)SCREEN_BASE_BLOCK(8))[letter + (xPos - (int)floor(letter/sizeX)*sizeX) + (yPos + (int)floor(letter/sizeX))*32] = (text[letter]== ' ' ? 0x7F : text[letter])-32;
			//((u16*)SCREEN_BASE_BLOCK(8))[letter + (xPos - (int)floor(letter/sizeX)*sizeX) + (yPos + (int)floor(letter/sizeX))*32] = (text[letter]-32) | (2<<10);
			//((u16*)SCREEN_BASE_BLOCK(8))[letter + (xPos - (int)floor(letter/sizeX)*sizeX) + (yPos + (int)floor(letter/sizeX))*32] += (1 << 12);
			letter++;
		}
		else
		{
			free(text);
			lockInput = 0;
		}
	}
}
void dialogueBox::Clear()
{
	for(u16 row = 0; row < sizeY; row++)
	{
		for(u16 col = 0; col < sizeX; col++)
		{
			((u16*)SCREEN_BASE_BLOCK(8))[(xPos + col) + (yPos + row)*32] = 0x5F;
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
