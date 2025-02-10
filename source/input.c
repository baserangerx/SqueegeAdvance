#include "input.h"
#include "text.h"
#include "draw.h"
#include "action_options.h"
#include <gba_input.h>

bool lockInput;
int page = 0;

enum InputMode
{
    DIALOGUE_MODE,
    COMBAT_MODE,
    OPTION_MODE
};

u16 mode = DIALOGUE_MODE;

void combatInput(const u16);
void optionInput(const u16);

void updateInput()
{
    u16 downKeys = keysDown();

    switch (mode)
    {
        case DIALOGUE_MODE:
            if (downKeys & KEY_A)
            {
                showPageIcons(1);
                loadPage(page=0);
                mode = COMBAT_MODE;      
            }
        break;
        case COMBAT_MODE: 
            combatInput(downKeys);
        break;
        case OPTION_MODE:
            optionInput(downKeys);
        break;
    }
    
    
    
}

void combatInput(const u16 downKeys)
{
    static u8 selected = 0;

    if (downKeys & KEY_R)
    {
        selected = 0;
        loadPage(page<3 ? ++page : (page=0));
    }
    if (downKeys & KEY_L)
    {
        selected = 0;
        loadPage(page>0 ? --page : (page=3));
    }
    if(downKeys & KEY_RIGHT) updateSelection(selected < 5 ? (++selected) : (selected = 0));
    if(downKeys & KEY_LEFT) updateSelection(selected > 0 ? (--selected) : (selected = 5));
    if(downKeys & KEY_UP) updateSelection(selected > 1 ? (selected -= 2) : (selected += 4));
    if(downKeys & KEY_DOWN) updateSelection(selected < 4 ? (selected += 2) : (selected -= 4));
    if(downKeys & KEY_A)
    {
        //selected = 0;
        mode = OPTION_MODE;
        showItemOptions(1);
    }
}

void optionInput(const u16 downKeys)
{
    static u8 selected = 0;
    if(downKeys & KEY_B)
    {
        selected = 0;
        showItemOptions(0);
        mode = COMBAT_MODE;
        return;
    }
    if(downKeys & KEY_A)
    {
        infoItem();
        mode = DIALOGUE_MODE;
        return;
    }
    if(downKeys & KEY_UP) updateOption(selected > 0 ? (--selected) : (selected = 1));
    if(downKeys & KEY_DOWN) updateOption(selected < 1 ? (++selected) : (selected = 0));
}