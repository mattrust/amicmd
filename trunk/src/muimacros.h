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
#include <proto/exec.h>
#include <clib/alib_protos.h>
#include <exec/types.h>

/* --- ID creation --- */
#ifndef MAKE_ID
#define MAKE_ID(a,b,c,d) ((ULONG) (a)<<24 | (ULONG) (b)<<16 | (ULONG) (c)<<8 | (ULONG) (d))
#endif

/* --- Menu macros --- */
#define MUI_Menu(title,dis)  MUIA_Family_Child, MenuObject, MUIA_Menu_Title, title, MUIA_Menu_Enabled, dis
#define MUI_Menuitem(title,key,udata,dis)  MUIA_Family_Child, MenuitemObject, MUIA_Menuitem_Title, title, MUIA_Menuitem_Shortcut, key, MUIA_UserData, udata, MUIA_Menuitem_Enabled, dis, End
#define MUI_Bar  MUIA_Family_Child, MenuitemObject, MUIA_Menuitem_Title, NM_BARLABEL, End 

/* --- Button macros --- */
#define  NButton(name,disabled) \
        TextObject, \
		ButtonFrame, \
		MUIA_Font, MUIV_Font_Button, \
		MUIA_Text_Contents, name,\
		MUIA_Text_PreParse, "\33c",\
		MUIA_Disabled, disabled,\
		MUIA_InputMode    , MUIV_InputMode_RelVerify,\
		MUIA_Background   , MUII_ButtonBack,\
		End 

#define WButton(name)\
	TextObject,\
		ButtonFrame,\
		MUIA_Font, MUIV_Font_Button,\
		MUIA_Text_Contents, name,\
		MUIA_Text_PreParse, "\33c",\
		MUIA_Weight, 0,\
		MUIA_InputMode    , MUIV_InputMode_RelVerify,\
		MUIA_Background   , MUII_ButtonBack,\
		End
