#include <gba_video.h>
#include <gba_sprites.h>
#include <string.h>
#include <math.h>
#include "font.h"
#include "UI.h"
#include "text.h"
#include "stdlib.h"

char* text;

u16 letter;
u16 delay;
u16 xPos;
u16 yPos;
u16 sizeX;
u16 sizeY;

void loadText()
{
	REG_BG0CNT = BG_PRIORITY(0) | CHAR_BASE(0) | BG_16_COLOR | SCREEN_BASE(7) | BG_SIZE_0;

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
                ((u32*)CHAR_BASE_BLOCK(0))[(row + 4 * hl)] |= (((toncfontTiles[hl] >> (row * 8)) & (0b1 << col)) > 0 ? ((toncfontTiles[hl] >> (row * 8)) & (0b1 << col))*7 : 1<<col) << (3 * col);
            }
        }
    }
	memcpy((u8*)CHAR_BASE_BLOCK(0) + 0xc00, UITiles, UITilesLen);
	
}


void createDialogueBox(const u16 x, const u16 y, const u16 width, const u16 height, const u16 dla)
{
	delay = dla;
	xPos = x;
	yPos = y;
	sizeX = width;
	sizeY = height;

	for (int row = 0; row < sizeY+2; row++)
	{
		for (int col = 0; col < sizeX+2; col++)
		{
			int tile = 0;
			if((row == 0 || row == sizeY+1)&&(col == 0 || col == sizeX+1))
			{
				tile = 0;
			}
			else if(row == 0 || row == sizeY+1)
			{
				tile = 1;
			}
			else if(col == 0 || col == sizeX+1)
			{
				tile = 2;
			}
			else
			{
				tile = 3;
			}
			bool flipX = col > sizeX;
			bool flipY = row > sizeY;

			((u16*)SCREEN_BASE_BLOCK(7))[(row + yPos - 1)*32+col+xPos-1] = (96+tile) | flipX<<10 | flipY<<11;
			//((u16*)SCREEN_BASE_BLOCK(7))[(row*2 + yPos - 1)*32+col*2+(32*flipY)+!flipX] = (96+1+tile*4) | flipX<<10 | flipY<<11;
			//((u16*)SCREEN_BASE_BLOCK(7))[(row*2 + yPos - 1)*32+col*2+(32*!flipY)+flipX] = (96+2+tile*4) | flipX<<10 | flipY<<11;
			//((u16*)SCREEN_BASE_BLOCK(7))[(row*2 + yPos - 1)*32+col*2+(32*!flipY)+!flipX] = (96+3+tile*4) | flipX<<10 | flipY<<11;
		}
	}
}


void loadPage(u16 page)
{
	dialogueClear();
	((u16*)SCREEN_BASE_BLOCK(7))[(xPos-1) + (yPos-1)*32] = 96;
	for(int i = 1; i < 4*2+1; i++)
	{
		((u16*)SCREEN_BASE_BLOCK(7))[(xPos-1+i) + (yPos-1)*32] = 97;
	}

	switch (page)
	{
		case 0:
			*((vu16*)0x500000E) = *((vu16*)0x5000006);
			*((vu16*)0x5000010) = *((vu16*)0x5000006);
			//*((vu16*)0x5000012) = *((vu16*)0x5000008);
			//*((vu16*)0x5000014) = *((vu16*)0x500000A);

			((u16*)SCREEN_BASE_BLOCK(7))[(xPos-1) + (yPos-1)*32] = 98;
			((u16*)SCREEN_BASE_BLOCK(7))[(xPos) + (yPos-1)*32] = 99;
			((u16*)SCREEN_BASE_BLOCK(7))[(xPos+1) + (yPos-1)*32] = 100;
			break;
		case 1:
			*((vu16*)0x500000E) = *((vu16*)0x5000008);
			*((vu16*)0x5000010) = *((vu16*)0x5000008);
			*((vu16*)0x5000012) = *((vu16*)0x5000008);
			//*((vu16*)0x5000014) = *((vu16*)0x500000A);

			((u16*)SCREEN_BASE_BLOCK(7))[(xPos+1) + (yPos-1)*32] = 99;
			((u16*)SCREEN_BASE_BLOCK(7))[(xPos+2) + (yPos-1)*32] = 99;
			((u16*)SCREEN_BASE_BLOCK(7))[(xPos+3) + (yPos-1)*32] = 100;
			break;
		case 2:
			*((vu16*)0x500000E) = *((vu16*)0x500000A);
			//*((vu16*)0x5000010) = *((vu16*)0x5000008);
			*((vu16*)0x5000012) = *((vu16*)0x500000A);
			*((vu16*)0x5000014) = *((vu16*)0x500000A);

			((u16*)SCREEN_BASE_BLOCK(7))[(xPos+3) + (yPos-1)*32] = 99;
			((u16*)SCREEN_BASE_BLOCK(7))[(xPos+4) + (yPos-1)*32] = 99;
			((u16*)SCREEN_BASE_BLOCK(7))[(xPos+5) + (yPos-1)*32] = 100;

			for(int i = 0; i < 6; i++)
			{
				dialogueWrite(xPos + (i%2)*sizeX/2, yPos + floor(i/2)*2, "- ");
				//Write(xPos + (i%2)*sizeX/2 + 2, yPos + floor(i/2)*2, );
			}
			break;
		case 3:
			*((vu16*)0x500000E) = *((vu16*)0x500000C);
			//*((vu16*)0x5000010) = *((vu16*)0x5000008);
			//*((vu16*)0x5000012) = *((vu16*)0x500000A);
			*((vu16*)0x5000014) = *((vu16*)0x500000C);

			((u16*)SCREEN_BASE_BLOCK(7))[(xPos+5) + (yPos-1)*32] = 99;
			((u16*)SCREEN_BASE_BLOCK(7))[(xPos+6) + (yPos-1)*32] = 99;
			((u16*)SCREEN_BASE_BLOCK(7))[(xPos+7) + (yPos-1)*32] = 100;

		case 4:
			for (int i = 0; i < 4; i++)
            {
                ((u16*)SCREEN_BASE_BLOCK(7))[(xPos-1+(2*i)) + (yPos-3)*32] = 104+(4*i);
                ((u16*)SCREEN_BASE_BLOCK(7))[(xPos+(2*i)) + (yPos-3)*32] = 104+1+(4*i);
                ((u16*)SCREEN_BASE_BLOCK(7))[(xPos-1+(2*i)) + (yPos-2)*32] = 104+2+(4*i);
                ((u16*)SCREEN_BASE_BLOCK(7))[(xPos+(2*i)) + (yPos-2)*32] = 104+3+(4*i);
            }
			((u16*)SCREEN_BASE_BLOCK(7))[(xPos-1+(2*4)) + (yPos-3)*32] = 101;
            ((u16*)SCREEN_BASE_BLOCK(7))[(xPos-1+(2*4)) + (yPos-2)*32] = 103;
			break;
	};
}

void dialoguePrint(const char* txt)
{
	dialogueClear();
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
void dialogueStep(const long frame)
{
	if(text == NULL) return;
	if(frame % delay == 0)
	{
		if(strlen(text) - letter)
		{
			lockInput = 1;
			((u16*)SCREEN_BASE_BLOCK(7))[letter + (xPos - (int)floor(letter/sizeX)*sizeX) + (yPos + (int)floor(letter/sizeX))*32] = (text[letter]== ' ' ? 0x7F : text[letter])-32;
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
void dialogueWrite(const u16 x, const u16 y, const char* text)
{
	for (u16 i = 0; i < strlen(text); i++)
	{
		((u16*)SCREEN_BASE_BLOCK(7))[x+i + y*32] = (text[i]== ' ' ? 0x7F : text[i])-32;;
	}
}
void dialogueClear()
{
	for(u16 row = 0; row < sizeY; row++)
	{
		for(u16 col = 0; col < sizeX; col++)
		{
			((u16*)SCREEN_BASE_BLOCK(7))[(xPos + col) + (yPos + row)*32] = 0x5F;
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
