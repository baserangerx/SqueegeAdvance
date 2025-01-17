#include "draw.h"
#include <gba_video.h>

void drawBox(const u16 _x, const u16 _y, const u16 _width, const u16 _height)
{
	for (int row = 0; row < _height+2; row++)
	{
		for (int col = 0; col < _width+2; col++)
		{
			int tile = 0;
			if((row == 0 || row == _height+1)&&(col == 0 || col == _width+1))
			{
				tile = 0;
			}
			else if(row == 0 || row == _height+1)
			{
				tile = 1;
			}
			else if(col == 0 || col == _width+1)
			{
				tile = 2;
			}
			else
			{
				tile = 3;
			}
			bool flipX = col > _width;
			bool flipY = row > _height;

			((u16*)SCREEN_BASE_BLOCK(7))[(row + _y - 1)*32+col+_x-1] = (96+tile) | flipX<<10 | flipY<<11;
			//((u16*)SCREEN_BASE_BLOCK(7))[(row*2 + yPos - 1)*32+col*2+(32*flipY)+!flipX] = (96+1+tile*4) | flipX<<10 | flipY<<11;
			//((u16*)SCREEN_BASE_BLOCK(7))[(row*2 + yPos - 1)*32+col*2+(32*!flipY)+flipX] = (96+2+tile*4) | flipX<<10 | flipY<<11;
			//((u16*)SCREEN_BASE_BLOCK(7))[(row*2 + yPos - 1)*32+col*2+(32*!flipY)+!flipX] = (96+3+tile*4) | flipX<<10 | flipY<<11;
		}
	}
}

void drawClear(const u16 _x, const u16 _y, const u16 _width, const u16 _height)
{
    for (int row = 0; row < _height+2; row++)
	{
		for (int col = 0; col < _width+2; col++)
		{
			((u16*)SCREEN_BASE_BLOCK(7))[(row + _y - 1)*32+col+_x-1] = 0;
		}
	}
}