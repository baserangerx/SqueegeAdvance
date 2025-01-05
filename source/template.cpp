#include <gba_video.h>
#include <gba_interrupt.h>
#include <gba_systemcalls.h>
#include <gba_input.h>
#include <gba_sprites.h>
#include <string.h>
#include "squeege.h"
#include "text.h"


// Simple sprite palette with white color
const u16 sprite_palette[16] = {
    RGB5(0, 0, 0),      // --BLANK--
    RGB5(20, 0, 10),     // Dark Purple
    RGB5(31, 5, 5),     // Red
    RGB5(5, 15, 5),     // Dark Green
    RGB5(31, 31, 31),    // White
    RGB5(0, 0, 0),      // --BLANK--
    RGB5(20, 0, 10),     // Dark Purple
    RGB5(31, 5, 5),     // Red
    RGB5(5, 15, 5),     // Dark Green
    RGB5(31, 31, 31),    // White
    RGB5(0, 0, 0),      // --BLANK--
    RGB5(20, 0, 10),     // Dark Purple
    RGB5(31, 5, 5),     // Red
    RGB5(5, 15, 5),     // Dark Green
    RGB5(31, 31, 31),    // White
    RGB5(20,20,20)
};

#define OAM_SIZE 128
volatile Sprite oamBuffer[OAM_SIZE];

int i = 0;
long frame = 0;

// VBlank interrupt handler
void VBlankHandler(void) {
    // Code to run during VBlank (e.g., update sprite positions, palette, etc.)
	memcpy(SPRITE_PALETTE, squeegePal, squeegePalLen); // Commit the pallet to VRAM
    memcpy(SPRITE_GFX, squeegeTiles + i*squeegeTilesLen/(4*6), squeegeTilesLen/6);   // Commit sprites to VRAM
    memcpy(OAM, (Sprite*)oamBuffer, sizeof(oamBuffer)); // Commit OAM to VRAM
    frame++;
    if (frame % 5 == 0)
        {
            i >= 5 ? i = 0 : i++;
        }
}

int main(void) 
{
    irqInit();
	irqSet(IRQ_VBLANK, VBlankHandler); // Calls VBlankHandler during VBLANK
    irqEnable(IRQ_VBLANK);
    //REG_IME = 1;
    
    // Set display mode (mode 3 + object layer enabled)
    SetMode(MODE_0 | OBJ_ON | OBJ_1D_MAP | BG0_ON);

	load();
	dialogueBox dB(1,10,28,4);

	//dB.Print("Holiday my horses! what the fwip dude thets pwetty cwazy my guy :}");
	//dB.Print("Once I was seven years old and I ate a large bird!!!");
    dB.Print("Gwimbke gumplbe hiuosaghjisahbnd");

    memset((void*)(oamBuffer), 0, sizeof(oamBuffer));

    oamBuffer[0].Y = 6*8; 
    oamBuffer[0].Shape = 0;  // Y=80, square sprite
    oamBuffer[0].X = ((30/2)-2)*8;
    oamBuffer[0].Size = 2;
    oamBuffer[0].HFlip = 0;  // X=60, 8x8 size
    oamBuffer[0].Character = 0;  // Tile 0, palette 0
    oamBuffer[0].Palette = 0;

    // Main loop
    while (1) {
        VBlankIntrWait(); // Waits for screen to be fully drawn
		dB.Step(frame);
		//testing github commits
		//step(frame);

        //scanKeys();

        //u16 keys_pressed = keysDown();
        //u16 keys_released = keysUp();

    
	
    }

    return 0;
}