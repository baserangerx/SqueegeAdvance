#include "items.h"
#include "text.h"
#include "action_options.h"
//#include "stdlib.h"

//sweet treat

enum {
    weapon,
    armour,
    consumable
};

item inventory[16];

item newItem(char* _name, u16 _type, char* _description, u16 _value)
{
    item newItem;
    newItem.name = _name;
    newItem.type = _type;
    newItem.description = _description;
    newItem.value = _value;
    return newItem;
}
void addItem(item* _item)
{
    int i = 0;
    while(inventory[i].name!=NULL)
    {
        i++;
    };
    inventory[i]=*_item;
}
void useItem(item* _item)
{
    if (_item->type == consumable)
    {
        showItemOptions(0);
        showPageIcons(0);
        loadDialogueBox();
        dialoguePrint("it tastes like circles. You regained %i hp!!! wiksmmd n ajnnjdn eee",1, _item->value);
    }
}
