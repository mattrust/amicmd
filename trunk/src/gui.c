/*                                                                             */
/*   ___ _            _    _            ___       __ _                         */
/*  | _ ) |_  _ ___  | |  (_)___ _ _   / __| ___ / _| |___ __ ____ _ _ _ ___   */
/*  | _ \ | || / -_) | |__| / _ \ ' \  \__ \/ _ \  _|  _\ V  V / _` | '_/ -_)  */
/*  |___/_|\_,_\___| |____|_\___/_||_| |___/\___/_|  \__|\_/\_/\__,_|_| \___|  */
/*                                                                             */
/*             Copyright 2008, Miklós Németh (Blue Lion Software)              */
/*                        email: desco@bluelion.hu                             */
/*                       WWW: http://www.bluelion.hu                           */
/*                                                                             */

#include <libraries/mui.h>
#include <proto/muimaster.h>

#include "SDI_hook.h"
#include "gui.h"


extern APTR wi_main, lv_left, lv_right, to_left, to_right,
            lv_active, lv_inactive, to_active, to_inactive;

HOOKPROTONHNO(UI_TabChange, void, int *arg)
{
    
    if (*arg == PID_Left)
        set(wi_main, MUIA_Window_ActiveObject, lv_left);
    else if (*arg == PID_Right)
        set(wi_main, MUIA_Window_ActiveObject, lv_right);
        
    get(wi_main, MUIA_Window_ActiveObject, &lv_active);
    
    if (lv_active == lv_right)
    {
        to_active = to_right;
        to_inactive = to_left;
        lv_inactive = lv_left;
    }
    else if (lv_active == lv_left)
    {
        to_active = to_left;
        to_inactive = to_right;
        lv_inactive = lv_right;
    }
    else
        return;
    
    set(to_inactive, MUIA_Background, MUII_BACKGROUND);
    set(to_inactive, MUIA_Text_PreParse, "\0332");
    set(to_active, MUIA_Background,MUII_FILL);
    set(to_active, MUIA_Text_PreParse, "\0333"); 
    
}

MakeHook(UI_TabChangeHook, UI_TabChange);
