#include "input.h"
#include "text.h"
#include "draw.h"
#include "action_options.h"
#include <gba_input.h>
#include <stdlib.h>
#include "player.h"

bool lockInput;
int page = 0;
int availableSelections = 0;
u8 selected = 0;
u8 pageLock;

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
    //static u8 selected = 0;

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
    if(downKeys & KEY_RIGHT) updateSelection(selected < availableSelections ? (++selected) : (selected = 0));
    if(downKeys & KEY_LEFT) updateSelection(selected > 0 ? (--selected) : (selected = availableSelections));
    if(downKeys & KEY_UP) updateSelection(selected = (selected - 2) % (availableSelections+1));
    if(downKeys & KEY_DOWN) updateSelection(selected = (selected + 2) % (availableSelections+1));

    if(downKeys & KEY_A && page == 0)
    {
        pageLock = 1;
    }
    if((downKeys & KEY_A && page == 2) && (selected < itemCount))
    {
        //selected = 0;
        mode = OPTION_MODE;
        showItemOptions(1);
    }
}

void optionInput(const u16 _downKeys)
{
    static u8 _selected = 0;
    if(_downKeys & KEY_B)
    {
        _selected = 0;
        showItemOptions(0);
        mode = COMBAT_MODE;
        return;
    }
    if(_downKeys & KEY_A)
    {
        if((_selected) == 0)
        {
            _selected = 0;
            useItem(&inventory[selected]);
            mode = DIALOGUE_MODE;
            return;
        }
        else if((_selected) == 1)
        {
            _selected = 0;
            infoItem(&inventory[selected]);
            mode = DIALOGUE_MODE;
            return;
        }
        
    }
    if(_downKeys & KEY_UP) updateOption((_selected) > 0 ? (--(_selected)) : ((_selected) = 1));
    if(_downKeys & KEY_DOWN) updateOption((_selected) < 1 ? (++(_selected)) : ((_selected) = 0));
}