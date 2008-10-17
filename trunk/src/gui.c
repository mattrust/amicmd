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
#include "amicmd.h"

HOOKPROTONHNO(UI_TabChange, void, int *arg)
{
    
    if (*arg == PID_Left)
        set(app.wi_main, MUIA_Window_ActiveObject, app.lv_left);
    else if (*arg == PID_Right)
        set(app.wi_main, MUIA_Window_ActiveObject, app.lv_right);
        
    get(app.wi_main, MUIA_Window_ActiveObject, &(app).lv_active);
    
    if (app.lv_active == app.lv_right)
    {
        app.to_active = app.to_right;
        app.to_inactive = app.to_left;
        app.lv_inactive = app.lv_left;
    }
    else if (app.lv_active == app.lv_left)
    {
        app.to_active = app.to_left;
        app.to_inactive = app.to_right;
        app.lv_inactive = app.lv_right;
    }
    else
        return;
    
    set(app.to_inactive, MUIA_Background, MUII_BACKGROUND);
    set(app.to_inactive, MUIA_Text_PreParse, "\0332");
    set(app.to_active, MUIA_Background,MUII_FILL);
    set(app.to_active, MUIA_Text_PreParse, "\0333"); 
    
}

MakeHook(UI_TabChangeHook, UI_TabChange);
