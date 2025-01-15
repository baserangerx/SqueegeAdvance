#ifndef TEXT_H
#define TEXT_H

void loadText();
extern bool lockInput;

class DialogueBox
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
		DialogueBox(const u16 x, const u16 y, const u16 width, const u16 height, const u16 dla = 2);
		void Page(const u16);
		void Print(const char*);
		void Step(const long);
		void Write(const u16 x, const u16 y, const char* name);
		void Clear();
};


#endif