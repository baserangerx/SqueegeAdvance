#ifndef TEXT_H
#define TEXT_H

void loadText();
extern bool lockInput;

class dialogueBox
{
	char* text;
	u16 letter;
	u16 delay;
	u16 xPos;
	u16 yPos;
	u16 sizeX;
	u16 sizeY;
	//dialogueBox(delay, x position, y position, width, height)
	public:
		dialogueBox(u16 x, u16 y, u16 width, u16 height, u16 dla = 2);
		void Page(const u16);
		void Print(const char*);
		void Step(const long);
		void Clear();
};


#endif