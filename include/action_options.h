#ifndef ACTION_OPTIONS_H
#define ACTION_OPTIONS_H
#include <gba_types.h>
#include "items.h"

void showItemOptions(bool);
//void clearItemOptions();
void useItem(item*);
void infoItem(item*);
void updateOption(const u8);
//void selected(const u8);

#endif