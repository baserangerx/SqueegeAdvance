#include <gba_video.h>
#include <gba_sprites.h>
#include <string.h>
#include <math.h>
#include "font.h"
#include "UI.h"
#include "text.h"
#include "stdlib.h"
#include "items.h"
#include "input.h"
#include "draw.h"
#include "stdarg.h"


char* text;
u16 textLength = 0;

#define POS_X 1
#define POS_Y 14
#define WIDTH 28
#define HEIGHT 5


u16 letter;
u16 delay;
//u16 xPos;
//u16 yPos;
//u16 sizeX;
//u16 sizeY;

void loadText()
{
	REG_BG0CNT = BG_PRIORITY(0) | CHAR_BASE(0) | BG_16_COLOR | SCREEN_BASE(7) | BG_SIZE_0;

    memcpy(BG_PALETTE, UIPal, UIPalLen);
	*(BG_PALETTE + 0x11) = BG_PALETTE[1];
	*(BG_PALETTE + 0x17) = 0b000001111111111;
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
	loadDialogueBox();
}

void loadDialogueBox()
{
	drawBox(POS_X,POS_Y,WIDTH,HEIGHT);
}

void updateSelection(const u8 selected)
{
	drawColour(POS_X, POS_Y, WIDTH, HEIGHT, 0);
	drawColour(POS_X+((selected%2)*WIDTH/2), POS_Y+(floor(selected/2)*2), WIDTH/2, 1, 1);
	//for(int i = 0; i < WIDTH/2; i++)
	//{
		//((u16*)SCREEN_BASE_BLOCK(7))[(u16)(POS_Y+floor(selected/2)*2)*32 + POS_X+i+((selected%2)*WIDTH/2)] &= 0x0FFF;
		//((u16*)SCREEN_BASE_BLOCK(7))[(u16)(POS_Y+floor(selected/2)*2)*32 + POS_X+i+((selected%2)*WIDTH/2)] |= (1<<0xC);
	//}
}

void showPageIcons(bool _true)
{
	if (_true == 1)
	{
		for (int i = 0; i < 4; i++)
            {
                ((u16*)SCREEN_BASE_BLOCK(7))[(POS_X-1+(2*i)) + (POS_Y-3)*32] = 104+(4*i);
                ((u16*)SCREEN_BASE_BLOCK(7))[(POS_X+(2*i)) + (POS_Y-3)*32] = 104+1+(4*i);
                ((u16*)SCREEN_BASE_BLOCK(7))[(POS_X-1+(2*i)) + (POS_Y-2)*32] = 104+2+(4*i);
                ((u16*)SCREEN_BASE_BLOCK(7))[(POS_X+(2*i)) + (POS_Y-2)*32] = 104+3+(4*i);
            }
			((u16*)SCREEN_BASE_BLOCK(7))[(POS_X-1+(2*4)) + (POS_Y-3)*32] = 101;
            ((u16*)SCREEN_BASE_BLOCK(7))[(POS_X-1+(2*4)) + (POS_Y-2)*32] = 103;
	}
	else
	{
		drawClear(POS_X, POS_Y-2, 7, 0);
	}
}

void loadPage(u16 page)
{
	dialogueClear();
	updateSelection(0);
	((u16*)SCREEN_BASE_BLOCK(7))[(POS_X-1) + (POS_Y-1)*32] = 96;
	for(int i = 1; i < 4*2+1; i++)
	{
		((u16*)SCREEN_BASE_BLOCK(7))[(POS_X-1+i) + (POS_Y-1)*32] = 97;
	}

	switch (page)
	{
		case 0:
			*((vu16*)0x500000E) = *((vu16*)0x5000006);
			*((vu16*)0x5000010) = *((vu16*)0x5000006);
			//*((vu16*)0x5000012) = *((vu16*)0x5000008);
			//*((vu16*)0x5000014) = *((vu16*)0x500000A);

			((u16*)SCREEN_BASE_BLOCK(7))[(POS_X-1) + (POS_Y-1)*32] = 98;
			((u16*)SCREEN_BASE_BLOCK(7))[(POS_X) + (POS_Y-1)*32] = 99;
			((u16*)SCREEN_BASE_BLOCK(7))[(POS_X+1) + (POS_Y-1)*32] = 100;
			break;
		case 1:
			*((vu16*)0x500000E) = *((vu16*)0x5000008);
			*((vu16*)0x5000010) = *((vu16*)0x5000008);
			*((vu16*)0x5000012) = *((vu16*)0x5000008);
			//*((vu16*)0x5000014) = *((vu16*)0x500000A);

			((u16*)SCREEN_BASE_BLOCK(7))[(POS_X+1) + (POS_Y-1)*32] = 99;
			((u16*)SCREEN_BASE_BLOCK(7))[(POS_X+2) + (POS_Y-1)*32] = 99;
			((u16*)SCREEN_BASE_BLOCK(7))[(POS_X+3) + (POS_Y-1)*32] = 100;
			break;
		case 2:
			*((vu16*)0x500000E) = *((vu16*)0x500000A);
			//*((vu16*)0x5000010) = *((vu16*)0x5000008);
			*((vu16*)0x5000012) = *((vu16*)0x500000A);
			*((vu16*)0x5000014) = *((vu16*)0x500000A);

			((u16*)SCREEN_BASE_BLOCK(7))[(POS_X+3) + (POS_Y-1)*32] = 99;
			((u16*)SCREEN_BASE_BLOCK(7))[(POS_X+4) + (POS_Y-1)*32] = 99;
			((u16*)SCREEN_BASE_BLOCK(7))[(POS_X+5) + (POS_Y-1)*32] = 100;
			for(int i = 0; i < 6; i++)
			{
				dialogueWrite(POS_X + (i%2)*WIDTH/2, POS_Y + floor(i/2)*2, "- ");
				dialogueWrite(POS_X + (i%2)*WIDTH/2 + 2, POS_Y + floor(i/2)*2, inventory[i].name != NULL ? inventory[i].name : "");
			}
			break;
		case 3:
			*((vu16*)0x500000E) = *((vu16*)0x500000C);
			//*((vu16*)0x5000010) = *((vu16*)0x5000008);
			//*((vu16*)0x5000012) = *((vu16*)0x500000A);
			*((vu16*)0x5000014) = *((vu16*)0x500000C);

			((u16*)SCREEN_BASE_BLOCK(7))[(POS_X+5) + (POS_Y-1)*32] = 99;
			((u16*)SCREEN_BASE_BLOCK(7))[(POS_X+6) + (POS_Y-1)*32] = 99;
			((u16*)SCREEN_BASE_BLOCK(7))[(POS_X+7) + (POS_Y-1)*32] = 100;
			break;
	};
}

void dialoguePrint(const char* _txt, const u16 _delay, ...)
{
	va_list arg_ptr;
	va_start (arg_ptr, _delay);

	dialogueClear();
	textLength = 0;
	delay = _delay;
	text = (char*)calloc(WIDTH*HEIGHT,sizeof(char));

	//int i = 0, k = 0, l = 0;
	for(int i = 0, k = 0; _txt[i] != '\0'; i++, k++)
	{
		if(_txt[i] == '%')
		{
			i++;
			//k--;
			
			switch(_txt[i])
			{
				case 'i': {
					int value = va_arg(arg_ptr, int);
					int div;
					for (div = 1; div <= value; div*=10);
					do
					{
						div/=10;
						text[k++] = value/div + 48;
						//textLength++;
						value%=div;
					} while (value);
					i++;
					//k--;
					break;
				}
				case 's': {
					//k++;
					break;
				}
			}
		}
		if(_txt[i] == ' ')
		{
			int j = 1;
			while(!(_txt[i + j] == ' ' || _txt[i+j] == 0))
			{
				j++;
			}
			//if (txt[i+j] == 0) break;
			if(((k-1) % WIDTH) + j > WIDTH)
			{
				while((k) % WIDTH != 0)
				{
					text[k++] = ' ';
					//textLength++;
					//k++;
					/*
					while((i + k) % WIDTH != 0)
					{
						text[i+k] = ' ';
						textLength++;
						k++;
					}
					*/
				
				}
				i++;
				//textLength--;
			}
			
			//j = 1;
		}
		else
		{
			//k++;
		}

		text[k] = _txt[i];
		textLength = k+1;
		//if ((i + k) % WIDTH == 0 && _txt[i] == ' ') k--;

	}
	letter = 0;
}
void dialogueStep(const long frame)
{
	if(text == NULL) return;
	if(frame % delay == 0)
	{
		if(textLength > letter)
		{
			lockInput = 1;
			while(text[letter] == ' ')
			{
				letter++;
			}
			((u16*)SCREEN_BASE_BLOCK(7))[(letter % WIDTH) + POS_X  + (POS_Y + (u16)floor(letter/WIDTH))*32] = (text[letter]== ' ' ? 0x7F : text[letter])-32;
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
		((u16*)SCREEN_BASE_BLOCK(7))[x+i + y*32] &= 0xF000;
		((u16*)SCREEN_BASE_BLOCK(7))[x+i + y*32] |= (text[i]== ' ' ? 0x7F : text[i])-32;
	}
}
void dialogueClear()
{
	for(u16 row = 0; row < HEIGHT; row++)
	{
		for(u16 col = 0; col < WIDTH; col++)
		{
			((u16*)SCREEN_BASE_BLOCK(7))[(POS_X + col) + (POS_Y + row)*32] = 0x5F;
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
