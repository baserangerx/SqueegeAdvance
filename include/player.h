#ifndef PLAYER_H
#define PLAYER_H

#include "items.h"
#include <gba_types.h>

#define MAX_INVENTORY_SIZE 16

extern item inventory[];
extern u16 itemCount;

extern u16 maxHealth;
extern u16 health;

/*!
    \brief Holds data for the four core stats

    Potential - ability to cast spells.
    Persision - ability to dodge and apply conditions.
    Power - ability to attack.
    Prosperity - ability to take damage and ignore conditions.
*/
extern u16 stats;

#endif