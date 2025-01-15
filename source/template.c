#include <gba_video.h>
#include <gba_interrupt.h>
#include <gba_systemcalls.h>
#include <gba_input.h>
#include <gba_sprites.h>
#include <string.h>
#include "squeege.h"
#include "UI.h"
#include "sewer.h"
#include "text.h"

/*

REMEMBER TO ADD THE Monoter

bits & bytes
bytecoin
*/

#define OAM_SIZE 128
volatile Sprite oamBuffer[OAM_SIZE];

int i = 0;
long frame = 0;

bool lockInput = 0;
void VBlankHandler(void);

int main(void) 
{
    createDialogueBox(1,14,28,5,2);
    irqInit();
    irqSet(IRQ_VBLANK, VBlankHandler); // Calls VBlankHandler during VBLANK
    irqEnable(IRQ_VBLANK);
    
    // Set display mode (mode 3 + object layer enabled)
    SetMode(MODE_0 | OBJ_ON | OBJ_1D_MAP | BG0_ON | BG1_ON);

    memcpy(SPRITE_PALETTE, squeegePal, squeegePalLen); // Commit the pallet to VRAM
    memset((void*)(oamBuffer), 0, sizeof(oamBuffer));
    memcpy(SPRITE_PALETTE+16, UIPal, UIPalLen);
    //memcpy((u8*)SPRITE_GFX+0x400, UITiles, UITilesLen);

    memcpy(BG_PALETTE+0x20, sewerPal, sewerPalLen);
    memcpy(CHAR_BASE_BLOCK(1), sewerTiles, sewerTilesLen);
    REG_BG1CNT = BG_PRIORITY(0) | CHAR_BASE(1) | BG_16_COLOR | SCREEN_BASE(6) | BG_SIZE_0;
    REG_BG1VOFS=8*5;
    
    for(int row = 0; row < 20; row++)
    {
        for(int col = 0; col < 30; col++)
        {
            ((u16*)SCREEN_BASE_BLOCK(6))[row*32 + col] = (row*30+col) | (2<<0xc);
        }
    }
    //Consumable apple("apple", "cool apple");
    //gainItem(apple);

    loadText();
    dialoguePrint("Idk the font seems really big compared to the screen. Like this probably takes up four lines! (i gotta test more lines!)");

	int page = 0;
	

	//dB.Print("Holiday my horses! what the fwip dude thets pwetty cwazy my guy :}");
	//dB.Print("Once I was seven years old and I ate a large bird!!!");
    //dB.Print("At least is wasnt freddy fivebaer cuz wilmlum afleon fount the kids and he murdered the frebby and now the kids frebbify and chicka is chicken & evil >:(");
    
    //dB.Print("why are you missing danny's birthday, cohen? You know pain is a small price to pay to spend time with those you love");

    //dB.Print("the homuncules bot that nate mitchell has made is terrible and disgusting, evan landry himself has decided that the bot in un constitional, %%!");

    //dB.Print("I am squeege, the lone deciple of YoRe!                             Prepare thyself!");

    //dB.Print("Check out all my wires")

    oamBuffer[0].Y = 5*8; 
    oamBuffer[0].Shape = 0;  // Y=80, square sprite
    oamBuffer[0].X = ((30/2)-2)*8;
    oamBuffer[0].Size = 2;
    oamBuffer[0].HFlip = 0;  // X=60, 8x8 size
    oamBuffer[0].Character = 0;  // Tile 0, palette 0
    oamBuffer[0].Palette = 0;

    // Main loop
    while (1) {
        VBlankIntrWait(); // Waits for screen to be fully drawn
		int womp = keysDown();

        if ((womp & KEY_A) && !lockInput)
        {
            loadPage(4);
            loadPage(page=0);      
        }
        if ((womp & KEY_R) && !lockInput)
        {
            loadPage(page<3 ? ++page : (page=0));
        }
        if ((womp & KEY_L) && !lockInput)
        {
            loadPage(page>0 ? --page : (page=3));
        }
        //u16 keys_released = keysUp();

        //*((vu16*)0x5000002) += 1;
	
    }

    return 0;
}

// VBlank interrupt handler
void VBlankHandler(void) {
    // Code to run during VBlank (e.g., update sprite positions, palette, etc.)
    memcpy(SPRITE_GFX, squeegeTiles + i*squeegeTilesLen/(4*6), squeegeTilesLen/6);   // Commit sprites to VRAM
    memcpy(OAM, (Sprite*)oamBuffer, sizeof(oamBuffer)); // Commit OAM to VRAM
    scanKeys();
    dialogueStep(frame);
    frame++;
    if (frame % 5 == 0)
        {
            i >= 5 ? i = 0 : i++;
        }
}
