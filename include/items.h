#ifndef ITEMS_H
#define ITEMS_H

#include <gba_types.h>

typedef struct item
{
    char* name;
    u16 type;
    char* description;
    u16 value;
} item;

extern item inventory[];

item newItem(char*,u16,char*,u16);
void addItem(item*);
void useItem(item*);

#endif