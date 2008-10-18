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

#ifndef GUI_H
#define GUI_H

extern struct Hook UI_TabChangeHook;
extern struct Hook UI_ParentDirHook;
extern struct Hook UI_CalcDirInfoHook;
extern struct Hook UI_PanelDCHook;

enum PanelID
{
    PID_None,
    PID_Left,
    PID_Right
};

#endif
