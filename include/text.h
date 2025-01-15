#ifndef TEXT_HEADER
#define TEXT_HEADER
#include <gba_video.h>
void loadText();
extern bool lockInput;
//dialogueBox(delay, x position, y position, width, height)
void createDialogueBox(const u16 x, const u16 y, const u16 width, const u16 height, const u16 dla);
void loadPage(u16);
void dialoguePrint(const char*);
void dialogueStep(const long);
void dialogueWrite(const u16 x, const u16 y, const char* name);
void dialogueClear();
#endif