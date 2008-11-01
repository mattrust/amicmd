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
#include <stdio.h>
#include <string.h>


#include <libraries/mui.h>
#include <proto/muimaster.h>
#include <proto/dos.h>

#include <clib/alib_protos.h>

#include "SDI_hook.h"
#include "gui.h"
#include "tools.h"
#include "amicmd.h"

HOOKPROTONHNONP(TO_NewDrawer, void)
{

    APTR lv_active;
    char newpath[512];
    char dirname[256];
    BPTR lock;
    
    
    strcpy(dirname, (char *)xget(app.st_newdirname, MUIA_String_Contents));
    
    set(app.wi_newdir, MUIA_Window_Open, FALSE);
    
    if (strlen(dirname) <= 0)
        return;
    
    if (app.ActivePanel == PID_Left)
        lv_active = app.lv_left;
    else if (app.ActivePanel == PID_Right)
        lv_active = app.lv_right;
    else
        return;
        
    strcpy(newpath, (char *) xget(lv_active, MUIA_Dirlist_Directory));
    
    AddPart(newpath, dirname, 500);
    
    if ((lock = CreateDir(newpath)) != NULL)
        UnLock(lock);
    
    DoMethod(lv_active, MUIM_Dirlist_ReRead);

}

MakeHook(TO_NewDrawerHook, TO_NewDrawer);
