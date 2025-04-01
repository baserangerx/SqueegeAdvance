#include "items.h"
#include "text.h"
#include "action_options.h"
#include "player.h"
//#include "stdlib.h"

//sweet treat

//item inventory[16];
void addItem(item _item)
{
    if (itemCount < MAX_INVENTORY_SIZE)
    {
        inventory[itemCount]=_item;
        itemCount++;
    }
    else
    {
        //add too many items warning
    }
}
void removeItem(item* _item)
{
    for (int i = 0; i <= itemCount; i++)
    {
        if (inventory[i].name == _item->name)
        {
            while(i<=itemCount)
            {
                inventory[i] = inventory[i+1];
                i++;
            }
            itemCount--;
            break;
        }
    }
}
void useItem(item* _item)
{
    if (_item->type == CONSUMABLE)
    {
        showItemOptions(0);
        showPageIcons(0);
        loadDialogueBox();
        dialoguePrint("it tastes like '%s'. You regained %i hp!!!",1, _item->name, _item->value);
        removeItem(_item);
    }
}
