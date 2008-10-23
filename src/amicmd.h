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

typedef struct
{
    APTR app,
    wi_main,
    lv_left, lv_right, to_left, to_right, lv_active, lv_inactive, to_active, to_inactive,
    to_leftinfo, to_rightinfo, bt_leftup, bt_rightup,
    pop_left, pop_right, lv_leftpop, lv_rightpop,
    bt_view, bt_edit, bt_copy, bt_rename, bt_move,bt_makedir, bt_delete, bt_exit;
} TheApp;

extern TheApp app;

LONG xget(Object *, ULONG);
