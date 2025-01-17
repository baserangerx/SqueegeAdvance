#ifndef TEXT_HEADER
#define TEXT_HEADER
#include <gba_video.h>

void loadText();
//dialogueBox(delay, x position, y position, width, height)
void updateSelection(const u8);
void drawBox(const u16 x, const u16 y, const u16 width, const u16 height);
void loadPage(u16);
void dialoguePrint(const char*, const u16);
void dialogueStep(const long);
void dialogueWrite(const u16 x, const u16 y, const char* name);
void dialogueClear();
#endif