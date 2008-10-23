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
#include <stdlib.h>

#include <libraries/mui.h>

#include <proto/exec.h>
#include <proto/intuition.h>
#include <proto/muimaster.h>
#include <clib/alib_protos.h>

#include "muimacros.h"
#include "gui.h"
#include "amicmd.h"

/* --- Library bases --- */
struct Library *MUIMasterBase;
struct IntuitionBase *IntuitionBase;

/* --- Global variables --- */
TheApp app;

/* --- Failure handler --- */
void fail(TheApp app, char *str)
{
    if (app.app)
        MUI_DisposeObject(app.app);

    if (MUIMasterBase)
        CloseLibrary(MUIMasterBase);

    if (IntuitionBase)
        CloseLibrary((struct Library *)IntuitionBase);

    if (str)
    {
        puts(str);
        exit(20);
    }
    exit(0);
}

/* --- Gets the attributes easily --- */
LONG xget(Object *obj,ULONG attribute)
{
	LONG x;
	get(obj,attribute,&x);
	return(x);
} 

/* ---  main --- */
int main(int argc, char **argv)
{
    ULONG sigs = 0;

    if (!(IntuitionBase =(struct IntuitionBase *) OpenLibrary("intuition.library",39)))
      fail(app,"Cannot open intuition.library v39+\n");

    if (!(MUIMasterBase =(struct Library *) OpenLibrary("muimaster.library",19)))
      fail(app,"Cannot open muimaster.library v19+\n");

    app.app = ApplicationObject,
        MUIA_Application_Title      , "AmiCommander",
    	MUIA_Application_Version    , "$VER: AmiCommander 0.1 (02.10.08)",
    	MUIA_Application_Copyright  , "GPL",
    	MUIA_Application_Author     , "Miklós Németh",
    	MUIA_Application_Description, "File manager", 
    	MUIA_Application_Base       , "AMICMD", 
        SubWindow, app.wi_main = WindowObject,
            MUIA_Window_Title, "AmiCommander",
            MUIA_Window_ID, MAKE_ID('W','I','M','A'),
            WindowContents, VGroup,
                Child, HGroup,
                    Child, VGroup,
                        Child, app.to_left = TextObject,
                            TextFrame, 
                            MUIA_Text_Contents, "DH0:",
                            MUIA_Background, MUII_FILL,
                            MUIA_Text_PreParse, "\0333",
                            MUIA_InputMode, MUIV_InputMode_RelVerify,    
                        End,
                        Child, HGroup,
                            Child, app.pop_left = PopobjectObject,
                                MUIA_Popstring_Button, PopButton(MUII_PopDrawer),
                                MUIA_Popobject_Object, app.lv_leftpop = ListviewObject,
                                    MUIA_Listview_List, VolumelistObject,
                                        InputListFrame,
                                        MUIA_List_AdjustWidth, TRUE, 
                                    End,
                                End,
                            End,
                            Child, app.to_leftinfo = TextObject, TextFrame, End,
                            Child, WButton(":"),
                            Child, app.bt_leftup = WButton("/"),
                        End,
    			        Child, app.lv_left = ListviewObject,
                            MUIA_CycleChain, 1,
						    MUIA_Listview_Input, TRUE,
						    //MUIA_Listview_DoubleClick, TRUE,
                   			MUIA_Listview_MultiSelect, MUIV_Listview_MultiSelect_Shifted,
    						MUIA_Listview_List, DirlistObject,
	   							InputListFrame,
	       						MUIA_Dirlist_Directory, "DH0:",
		         				MUIA_List_Title, TRUE,
				      			MUIA_Dirlist_RejectIcons, FALSE,
				      			MUIA_Dirlist_MultiSelDirs, TRUE,
					     	End,
				     	End,
					End,
					Child, BalanceObject, End,
					Child, VGroup,
                        Child, app.to_right = TextObject,
                            TextFrame, 
                            MUIA_Text_Contents, "DH0:",     
                            MUIA_InputMode, MUIV_InputMode_RelVerify,      
                        End,
                        Child, HGroup,
                            Child, app.pop_right = PopobjectObject,
                                MUIA_Popstring_Button, PopButton(MUII_PopDrawer),
                                MUIA_Popobject_Object, app.lv_rightpop = ListviewObject,
                                    MUIA_Listview_List, VolumelistObject,
                                        InputListFrame,
                                        MUIA_List_AdjustWidth, TRUE,
                                    End,
                                End,
                            End,
                            Child, app.to_rightinfo = TextObject, TextFrame, End,
                            Child, WButton(":"),
                            Child, app.bt_rightup = WButton("/"),
                        End,
    			        Child, app.lv_right = ListviewObject,
                            MUIA_CycleChain, 1,
                            MUIA_Listview_Input, TRUE,
                            //MUIA_Listview_DoubleClick, TRUE,
                    		MUIA_Listview_MultiSelect, MUIV_Listview_MultiSelect_Shifted,
    						MUIA_Listview_List, DirlistObject,
	    						InputListFrame,
		       					MUIA_Dirlist_Directory, "DH0:",
			         			MUIA_List_Title, TRUE,
					      		MUIA_Dirlist_RejectIcons, FALSE,
				      			MUIA_Dirlist_MultiSelDirs, TRUE,
						    End,
					    End,
					End,
                End,
                Child, HGroup,
                    Child, app.bt_view = NButton("\033bF3\033n View",TRUE),
                    Child, app.bt_edit = NButton("\033bF4\033n Edit",TRUE),
                    Child, app.bt_copy = NButton("\033bF5\033n Copy",TRUE),
                    Child, app.bt_move = NButton("\033bF6\033n Move",TRUE),
                    Child, app.bt_rename = NButton("\033bF9\033n Rename",TRUE),
                    Child, app.bt_makedir = NButton("\033bF7\033n MakeDir",TRUE),
                    Child, app.bt_delete = NButton("\033bF8\033n Delete",TRUE),
                    Child, app.bt_exit = NButton("\033bF10\033n Exit",FALSE),
                End, 
    		End,
    	End,
    End;
 

    if (!app.app)
        fail(app,"Failed to create application");

    DoMethod(app.wi_main, MUIM_Notify, MUIA_Window_CloseRequest, TRUE,
        app.app, 2, MUIM_Application_ReturnID, MUIV_Application_ReturnID_Quit);

    DoMethod(app.bt_exit, MUIM_Notify, MUIA_Pressed, FALSE,
        app.app, 2, MUIM_Application_ReturnID, MUIV_Application_ReturnID_Quit);

    DoMethod(app.to_left, MUIM_Notify, MUIA_Pressed, FALSE,
        app.app, 3, MUIM_CallHook, &UI_TabChangeHook, PID_Left);
        
    DoMethod(app.to_right, MUIM_Notify, MUIA_Pressed, FALSE,
        app.app, 3, MUIM_CallHook, &UI_TabChangeHook, PID_Right);

    DoMethod(app.lv_left, MUIM_Notify, MUIA_Dirlist_Directory, MUIV_EveryTime,
        app.to_left, 3, MUIM_Set, MUIA_Text_Contents, MUIV_TriggerValue);
        
    DoMethod(app.lv_right, MUIM_Notify, MUIA_Dirlist_Directory, MUIV_EveryTime,
        app.to_right, 3, MUIM_Set, MUIA_Text_Contents, MUIV_TriggerValue); 

    DoMethod(app.lv_left, MUIM_Notify, MUIA_Dirlist_Status, MUIV_Dirlist_Status_Valid,
        app.app, 2, MUIM_CallHook, &UI_CalcDirInfoHook);
    
    DoMethod(app.lv_right, MUIM_Notify, MUIA_Dirlist_Status, MUIV_Dirlist_Status_Valid,
        app.app, 2, MUIM_CallHook, &UI_CalcDirInfoHook);

    DoMethod(app.bt_leftup, MUIM_Notify, MUIA_Pressed, FALSE,
        app.app, 3, MUIM_CallHook, &UI_ParentDirHook, PID_Left);
    
    DoMethod(app.bt_rightup, MUIM_Notify, MUIA_Pressed, FALSE,
        app.app, 3, MUIM_CallHook, &UI_ParentDirHook, PID_Right);

    DoMethod(app.lv_left, MUIM_Notify, MUIA_Listview_DoubleClick, TRUE,
        app.app, 3, MUIM_CallHook, &UI_PanelDCHook, PID_Left);    
    
    DoMethod(app.lv_right, MUIM_Notify, MUIA_Listview_DoubleClick, TRUE,
        app.app, 3, MUIM_CallHook, &UI_PanelDCHook, PID_Right); 
        
    DoMethod(app.lv_leftpop, MUIM_Notify, MUIA_Listview_DoubleClick, TRUE,
        app.app, 3, MUIM_CallHook, &UI_VolumeDCHook, PID_Left);

    DoMethod(app.lv_rightpop, MUIM_Notify, MUIA_Listview_DoubleClick, TRUE,
        app.app, 3, MUIM_CallHook, &UI_VolumeDCHook, PID_Right);   

    DoMethod(app.wi_main, MUIM_Notify, MUIA_Window_InputEvent, "tab",
        app.app, 3, MUIM_CallHook, &UI_TabChangeHook, PID_None);
        
    DoMethod(app.wi_main, MUIM_Notify, MUIA_Window_InputEvent, "f10",
        app.app, 2, MUIM_Application_ReturnID, MUIV_Application_ReturnID_Quit);

    set(app.wi_main, MUIA_Window_ActiveObject, (ULONG)app.lv_left);
    app.lv_active = app.lv_left;

    set(app.wi_main, MUIA_Window_Open, TRUE);

    /* --- Event handling --- */

    while(DoMethod(app.app, MUIM_Application_NewInput, &sigs) != MUIV_Application_ReturnID_Quit)
    {
        if (sigs)
            sigs = Wait(sigs | SIGBREAKF_CTRL_C);
    }
  
    /* --- Exit --- */
    fail(app, NULL);
}
