#include "items.h"
#include "stdlib.h"

item* inventory[16];

item createItem(char* _name, char* _description)
{
    item newItem;
    newItem.name = _name;
    newItem.description = _description;
    return newItem;
}
void addItem(item* _item)
{
    int i = 0;
    while(inventory[i]!=NULL)
    {
        i++;
    };
    inventory[i]=_item;
}