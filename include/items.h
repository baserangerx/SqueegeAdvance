#ifndef ITEMS_H
#define ITEMS_H

#include <gba_types.h>

#define EFFECT_NONE 0
#define EFFECT_BURN 1
#define EFFECT_FREEZE 1<<1
#define EFFECT_POISON 1<<2
#define EFFECT_STUN 1<<3

typedef struct item
{
    char* name;
    char* description;
    u16 type;
    u16 value;
    u16 effect;
} item;

enum {
    WEAPON,
    ARMOUR,
    CONSUMABLE
};

//extern item inventory[];

void addItem(item);
void useItem(item*);

#endif