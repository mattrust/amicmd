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
        
    get(app.wi_main, MUIA_Window_ActiveObject, &app.lv_active);
    
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


HOOKPROTONHNO(UI_ParentDir, void, int *arg)
{
    char path[512];
    char npath[512];
    size_t len;
    
    DoMethod(app.app, MUIM_CallHook, &UI_TabChangeHook, *arg);
    
    strcpy(path, (char *)xget(app.lv_active, MUIA_Dirlist_Directory));
    
    len = strlen(path) - strlen((char *)PathPart(path));
    
    strncpy(npath, path, len);
    npath[len] = '\0';
    
    set(app.lv_active, MUIA_Dirlist_Directory, npath);
}

MakeHook(UI_ParentDirHook, UI_ParentDir);


HOOKPROTONHNONP(UI_CalcDirInfo,void)
{
    char info[256];
    
    sprintf(info,"%d dirs / %d files",xget(app.lv_left,MUIA_Dirlist_NumDrawers),xget(app.lv_left, MUIA_Dirlist_NumFiles));
    set(app.to_leftinfo, MUIA_Text_Contents, info);

    sprintf(info,"%d dirs / %d files",xget(app.lv_right,MUIA_Dirlist_NumDrawers),xget(app.lv_right, MUIA_Dirlist_NumFiles));
    set(app.to_rightinfo, MUIA_Text_Contents, info);
    
}

MakeHook(UI_CalcDirInfoHook, UI_CalcDirInfo);


HOOKPROTONHNO(UI_PanelDC, void, int *arg)
{
    struct FileInfoBlock *fib;
    
    DoMethod(app.app, MUIM_CallHook, &UI_TabChangeHook, *arg);
    
    DoMethod(app.lv_active, MUIM_List_GetEntry, MUIV_List_GetEntry_Active, &fib);
    
    if (!fib)
        return;    
    
    if (fib->fib_DirEntryType > 0)
        set(app.lv_active, MUIA_Dirlist_Directory,xget(app.lv_active, MUIA_Dirlist_Path));
    
}

MakeHook(UI_PanelDCHook, UI_PanelDC);
