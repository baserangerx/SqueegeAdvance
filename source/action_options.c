#include "action_options.h"
#include "draw.h"
#include "text.h"
#include "items.h"

#define POS_X 24
#define POS_Y 10
#define WIDTH 5
#define HEIGHT 2

void showItemOptions()
{
	drawBox(POS_X,POS_Y,WIDTH,HEIGHT);
    dialogueWrite(POS_X,POS_Y,"  Use");
    dialogueWrite(POS_X,POS_Y+1," Info");
}

void clearItemOptions()
{
    drawClear(POS_X,POS_Y,WIDTH,HEIGHT);
}

void useItem()
{

}

void infoItem(const item* _item)
{

}