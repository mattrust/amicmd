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
#include <libraries/dos.h>
#include <proto/muimaster.h>
#include <proto/dos.h>

#include "SDI_hook.h"
#include "gui.h"
#include "amicmd.h"

HOOKPROTONHNO(UI_TabChange, void, int *arg)
{
    if (app.ActivePanel == PID_Left)
    {
        set(app.wi_main, MUIA_Window_ActiveObject, app.lv_right);
        app.ActivePanel = PID_Right;
    }
    else if (app.ActivePanel == PID_Right)
    {
        set(app.wi_main, MUIA_Window_ActiveObject, app.lv_left);
        app.ActivePanel = PID_Left;
    }
}

MakeHook(UI_TabChangeHook, UI_TabChange);

HOOKPROTONHNONP(UI_ActiveObject, void)
{
    APTR lv_active, to_active, to_inactive;
    
    lv_active = (APTR)xget(app.wi_main, MUIA_Window_ActiveObject);
    
    if (lv_active == app.lv_left)
    {
        to_active = app.to_left;
        to_inactive = app.to_right;
    }
    else if (lv_active == app.lv_right)
    {
        to_active = app.to_right;
        to_inactive = app.to_left;
    }
    else
    {
        return;
    }
    
    set(to_active, MUIA_Background, MUII_FILL);    
    set(to_active, MUIA_Text_PreParse, "\0333");
    set(to_inactive, MUIA_Background, MUII_BACKGROUND);
    set(to_inactive, MUIA_Text_PreParse, "\0330");
    
}

MakeHook(UI_ActiveObjectHook, UI_ActiveObject);


HOOKPROTONHNO(UI_RootVolume, void, int *arg)
{
    APTR lv_active;
    char oldpath[512];
    char newpath[128];
    ULONG i = 0;
    
    if (*arg == PID_Left)
        lv_active = app.lv_left;
    else if (*arg == PID_Right)
        lv_active = app.lv_right;
    else
        return;
        
    strcpy(oldpath, (char *)xget(lv_active, MUIA_Dirlist_Directory));
    
    while(oldpath[i-1] != ':')
    {
        newpath[i] = oldpath[i];
        i++;
    }
        
    newpath[i] = '\0';
        
    set(lv_active, MUIA_Dirlist_Directory, newpath);
    set(app.wi_main, MUIA_Window_ActiveObject, lv_active);
}
MakeHook(UI_RootVolumeHook, UI_RootVolume);

HOOKPROTONHNO(UI_ParentDir, void, int *arg)
{
    char path[512];
    char npath[512];
    size_t len;
    APTR lv_active;
    
    if (*arg == PID_Left)
        lv_active = app.lv_left;
    else if (*arg == PID_Right)
        lv_active = app.lv_right;
    else
        return;
    
    strcpy(path, (char *)xget(lv_active, MUIA_Dirlist_Directory));
    
    len = strlen(path) - strlen((char *)PathPart(path));
    
    strncpy(npath, path, len);
    npath[len] = '\0';
    
    set(lv_active, MUIA_Dirlist_Directory, npath);
    set(app.wi_main, MUIA_Window_ActiveObject, lv_active);
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
    APTR lv_active;
    
    if (*arg == PID_Left)
        lv_active = app.lv_left;
    else if (*arg == PID_Right)
        lv_active = app.lv_right;
    else
        return;
    
    DoMethod(lv_active, MUIM_List_GetEntry, MUIV_List_GetEntry_Active, &fib);
    
    if (!fib)
        return;    
    
    if (fib->fib_DirEntryType > 0)
        set(lv_active, MUIA_Dirlist_Directory,xget(lv_active, MUIA_Dirlist_Path));

    set(app.wi_main, MUIA_Window_ActiveObject, lv_active);    
}

MakeHook(UI_PanelDCHook, UI_PanelDC);


HOOKPROTONHNO(UI_VolumeDC, void, int *arg)
{
    char *str;
    APTR lv_apop, pop_active, lv_active;


    if (*arg == PID_Left)
    {
        lv_apop = app.lv_leftpop;
        pop_active = app.pop_left;
        lv_active = app.lv_left;
    }
    else if (*arg == PID_Right)
    {
        lv_apop = app.lv_rightpop;
        pop_active = app.pop_right;
        lv_active = app.lv_right;
    }
    else
        return;

    DoMethod(lv_apop, MUIM_List_GetEntry, MUIV_List_GetEntry_Active, &str);

    set(lv_active, MUIA_Dirlist_Directory,str);
    DoMethod(pop_active, MUIM_Popstring_Close, TRUE);
    set(app.wi_main, MUIA_Window_ActiveObject, lv_active);

}

MakeHook(UI_VolumeDCHook, UI_VolumeDC);
