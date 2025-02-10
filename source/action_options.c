#include "action_options.h"
#include "draw.h"
#include "text.h"
#include "items.h"

#define POS_X 24
#define POS_Y 10
#define WIDTH 5
#define HEIGHT 2

void showItemOptions(bool _true)
{
    if (_true)
    {
        drawBox(POS_X,POS_Y,WIDTH,HEIGHT);
        dialogueWrite(POS_X,POS_Y,"  Use");
        dialogueWrite(POS_X,POS_Y+1," Info");
        drawColour(POS_X,POS_Y,WIDTH,1,1);
    }
    else
    {
        drawClear(POS_X,POS_Y,WIDTH,HEIGHT);
    }
}

void useItem()
{

}

//const item* _item
void infoItem()
{
    showItemOptions(0);
    showPageIcons(0);
    loadDialogueBox();
}

void updateOption(const u8 _selected)
{
    drawColour(POS_X, POS_Y, WIDTH, HEIGHT, 0);
    drawColour(POS_X, POS_Y+_selected, WIDTH, 1, 1);
}