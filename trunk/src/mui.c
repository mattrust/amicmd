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
#include <proto/muimaster.h>
#include <proto/exec.h>
#include <clib/alib_protos.h>

#include "muimacros.h"
#include "gui.h"

/* --- Library bases --- */
struct Library *MUIMasterBase,*IntuitionBase;
/* --- Global variables --- */
APTR app,
    wi_main,
    lv_left, lv_right, to_left, to_right, lv_active, lv_inactive, to_active, to_inactive,
    to_leftinfo, to_rightinfo, bt_leftup, bt_rightup,
    bt_exit; 

/* --- Failure handler --- */
void fail(APTR app, char *str)
{
    if (app)
        MUI_DisposeObject(app);

    if (MUIMasterBase)
        CloseLibrary(MUIMasterBase);

    if (IntuitionBase)
        CloseLibrary(IntuitionBase);

    if (str)
    {
        puts(str);
        exit(20);
    }
    exit(0);
}

int main(int argc, char **argv)
{
    ULONG sigs = 0;
        
    if (!(IntuitionBase =(struct Library *) OpenLibrary("intuition.library",39)))
        fail(app,"Cannot open intuition.library v39+\n");

    if (!(MUIMasterBase =(struct Library *) OpenLibrary("muimaster.library",19)))
        fail(app,"Cannot open muimaster.library v19+\n");

    app = ApplicationObject,
        MUIA_Application_Title      , "AmiCommander",
    	MUIA_Application_Version    , "$VER: AmiCommander 0.1 (02.10.08)",
    	MUIA_Application_Copyright  , "GPL",
    	MUIA_Application_Author     , "Miklós Németh",
    	MUIA_Application_Description, "File manager", 
    	MUIA_Application_Base       , "AMICMD", 
        SubWindow, wi_main = WindowObject,
            MUIA_Window_Title, "AmiCommander",
            MUIA_Window_ID, MAKE_ID('W','I','M','A'),
            WindowContents, VGroup,
                Child, HGroup,
                    Child, VGroup,
                        Child, to_left = TextObject,
                            TextFrame, 
                            MUIA_Text_Contents, "DH0:",
                            MUIA_Background, MUII_FILL,
                            MUIA_Text_PreParse, "\0333",
                            MUIA_InputMode, MUIV_InputMode_RelVerify,    
                        End,
                        Child, HGroup,
                            Child, to_leftinfo = TextObject, TextFrame, End,
                            Child, bt_leftup = WButton(".."),
                        End,
    			        Child, lv_left = ListviewObject,
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
                        Child, to_right = TextObject,
                            TextFrame, 
                            MUIA_Text_Contents, "DH0:",     
                            MUIA_InputMode, MUIV_InputMode_RelVerify,      
                        End,
                        Child, HGroup,
                            Child, to_rightinfo = TextObject, TextFrame, End,
                            Child, bt_rightup = WButton(".."),
                        End,
    			        Child, lv_right = ListviewObject,
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
                    Child, NButton("\033bF3\033n View",TRUE),
                    Child, NButton("\033bF4\033n Edit",TRUE),
                    Child, NButton("\033bF5\033n Copy",TRUE),
                    Child, NButton("\033bF6\033n Move",TRUE),
                    Child, NButton("\033bF9\033n Rename",TRUE),
                    Child, NButton("\033bF7\033n MakeDir",TRUE),
                    Child, NButton("\033bF8\033n Delete",TRUE),
                    Child, bt_exit = NButton("\033bF10\033n Exit",FALSE),
                End, 
    		End,
    	End,
    End;
 

    if (!app)
        fail(app,"Failed to create application");

    DoMethod(wi_main, MUIM_Notify, MUIA_Window_CloseRequest, TRUE,
        app, 2, MUIM_Application_ReturnID, MUIV_Application_ReturnID_Quit);

    DoMethod(bt_exit, MUIM_Notify, MUIA_Pressed, FALSE,
        app, 2, MUIM_Application_ReturnID, MUIV_Application_ReturnID_Quit);

    DoMethod(to_left, MUIM_Notify, MUIA_Pressed, FALSE,
        app, 3, MUIM_CallHook, &UI_TabChangeHook, PID_Left);
        
    DoMethod(to_right, MUIM_Notify, MUIA_Pressed, FALSE,
        app, 3, MUIM_CallHook, &UI_TabChangeHook, PID_Right);

    DoMethod(lv_left, MUIM_Notify, MUIA_Dirlist_Directory, MUIV_EveryTime,
        to_left, 3, MUIM_Set, MUIA_Text_Contents, MUIV_TriggerValue);
        
    DoMethod(lv_right, MUIM_Notify, MUIA_Dirlist_Directory, MUIV_EveryTime,
        to_right, 3, MUIM_Set, MUIA_Text_Contents, MUIV_TriggerValue); 


    set(wi_main, MUIA_Window_ActiveObject, lv_left);

    set(wi_main, MUIA_Window_Open, TRUE);

    /* --- Event handling --- */

    while(DoMethod(app, MUIM_Application_NewInput, &sigs) != MUIV_Application_ReturnID_Quit)
    {
        if (sigs)
            sigs = Wait(sigs | SIGBREAKF_CTRL_C);
    }
  
    /* --- Exit --- */
    fail(app, NULL);
}
