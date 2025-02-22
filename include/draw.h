#ifndef DRAW_H
#define DRAW_H
#include <gba_types.h>

/*!
    \brief Creates a rectangle
*/
void drawBox(const u16 X, const u16 Y, const u16 Width, const u16 Height);
/*!
    \brief Changes the pallet within a rectangle
*/
void drawColour(const u16 X, const u16 Y, const u16 Width, const u16 Height, const u8 Pallet);
/*!
    \brief Removes tile data within a rectangle
*/
void drawClear(const u16 X, const u16 Y, const u16 Width, const u16 Height);

#endif