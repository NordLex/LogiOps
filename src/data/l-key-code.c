/* l-key-code.c
 *
 * Copyright 26.02.24 NordLex
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "l-key-code.h"

typedef struct {
    const char *kernel;
    const guint gdk;
} KeyCode;

KeyCode codes[] = {
        (KeyCode) {"KEY_RESERVED",          0},
        (KeyCode) {"KEY_ESC",               GDK_KEY_Escape},
        (KeyCode) {"KEY_1",                 GDK_KEY_1},
        (KeyCode) {"KEY_2",                 GDK_KEY_2},
        (KeyCode) {"KEY_3",                 GDK_KEY_3},
        (KeyCode) {"KEY_4",                 GDK_KEY_4},
        (KeyCode) {"KEY_5",                 GDK_KEY_5},
        (KeyCode) {"KEY_6",                 GDK_KEY_6},
        (KeyCode) {"KEY_7",                 GDK_KEY_7},
        (KeyCode) {"KEY_8",                 GDK_KEY_8},
        (KeyCode) {"KEY_9",                 GDK_KEY_9},
        (KeyCode) {"KEY_0",                 GDK_KEY_0},
        (KeyCode) {"KEY_MINUS",             GDK_KEY_minus},
        (KeyCode) {"KEY_EQUAL",             GDK_KEY_equal},
        (KeyCode) {"KEY_BACKSPACE",         GDK_KEY_BackSpace},
        (KeyCode) {"KEY_TAB",               GDK_KEY_Tab},
        (KeyCode) {"KEY_Q",                 GDK_KEY_Q},
        (KeyCode) {"KEY_W",                 GDK_KEY_W},
        (KeyCode) {"KEY_E",                 GDK_KEY_E},
        (KeyCode) {"KEY_R",                 GDK_KEY_R},
        (KeyCode) {"KEY_T",                 GDK_KEY_T},
        (KeyCode) {"KEY_Y",                 GDK_KEY_Y},
        (KeyCode) {"KEY_U",                 GDK_KEY_U},
        (KeyCode) {"KEY_I",                 GDK_KEY_I},
        (KeyCode) {"KEY_O",                 GDK_KEY_O},
        (KeyCode) {"KEY_P",                 GDK_KEY_P},
        (KeyCode) {"KEY_LEFTBRACE",         GDK_KEY_braceleft},
        (KeyCode) {"KEY_RIGHTBRACE",        GDK_KEY_braceright},
        (KeyCode) {"KEY_ENTER",             GDK_KEY_KP_Enter},
        (KeyCode) {"KEY_LEFTCTRL",          GDK_KEY_Control_L},
        (KeyCode) {"KEY_A",                 GDK_KEY_A},
        (KeyCode) {"KEY_S",                 GDK_KEY_S},
        (KeyCode) {"KEY_D",                 GDK_KEY_D},
        (KeyCode) {"KEY_F",                 GDK_KEY_F},
        (KeyCode) {"KEY_G",                 GDK_KEY_G},
        (KeyCode) {"KEY_H",                 GDK_KEY_H},
        (KeyCode) {"KEY_J",                 GDK_KEY_J},
        (KeyCode) {"KEY_K",                 GDK_KEY_K},
        (KeyCode) {"KEY_L",                 GDK_KEY_L},
        (KeyCode) {"KEY_SEMICOLON",         GDK_KEY_semicolon},
        (KeyCode) {"KEY_APOSTROPHE",        GDK_KEY_apostrophe},
        (KeyCode) {"KEY_GRAVE",             GDK_KEY_grave},
        (KeyCode) {"KEY_LEFTSHIFT",         GDK_KEY_Shift_L},
        (KeyCode) {"KEY_BACKSLASH",         GDK_KEY_backslash},
        (KeyCode) {"KEY_Z",                 GDK_KEY_Z},
        (KeyCode) {"KEY_X",                 GDK_KEY_X},
        (KeyCode) {"KEY_C",                 GDK_KEY_C},
        (KeyCode) {"KEY_V",                 GDK_KEY_V},
        (KeyCode) {"KEY_B",                 GDK_KEY_B},
        (KeyCode) {"KEY_N",                 GDK_KEY_N},
        (KeyCode) {"KEY_M",                 GDK_KEY_M},
        (KeyCode) {"KEY_COMMA",             GDK_KEY_comma},
        (KeyCode) {"KEY_DOT",               0},
        (KeyCode) {"KEY_SLASH",             GDK_KEY_slash},
        (KeyCode) {"KEY_RIGHTSHIFT",        GDK_KEY_Shift_R},
        (KeyCode) {"KEY_KPASTERISK",        0},
        (KeyCode) {"KEY_LEFTALT",           GDK_KEY_Alt_L},
        (KeyCode) {"KEY_SPACE",             GDK_KEY_space},
        (KeyCode) {"KEY_CAPSLOCK",          GDK_KEY_Caps_Lock},
        (KeyCode) {"KEY_F1",                GDK_KEY_F1},
        (KeyCode) {"KEY_F2",                GDK_KEY_F2},
        (KeyCode) {"KEY_F3",                GDK_KEY_F3},
        (KeyCode) {"KEY_F4",                GDK_KEY_F4},
        (KeyCode) {"KEY_F5",                GDK_KEY_F5},
        (KeyCode) {"KEY_F6",                GDK_KEY_F6},
        (KeyCode) {"KEY_F7",                GDK_KEY_F7},
        (KeyCode) {"KEY_F8",                GDK_KEY_F8},
        (KeyCode) {"KEY_F9",                GDK_KEY_F9},
        (KeyCode) {"KEY_F10",               GDK_KEY_F10},
        (KeyCode) {"KEY_NUMLOCK",           GDK_KEY_Num_Lock},
        (KeyCode) {"KEY_SCROLLLOCK",        GDK_KEY_Scroll_Lock},
        (KeyCode) {"KEY_KP7",               GDK_KEY_KP_7},
        (KeyCode) {"KEY_KP8",               GDK_KEY_KP_8},
        (KeyCode) {"KEY_KP9",               GDK_KEY_KP_9},
        (KeyCode) {"KEY_KPMINUS",           0},
        (KeyCode) {"KEY_KP4",               GDK_KEY_KP_4},
        (KeyCode) {"KEY_KP5",               GDK_KEY_KP_5},
        (KeyCode) {"KEY_KP6",               GDK_KEY_KP_6},
        (KeyCode) {"KEY_KPPLUS",            0},
        (KeyCode) {"KEY_KP1",               GDK_KEY_KP_1},
        (KeyCode) {"KEY_KP2",               GDK_KEY_KP_2},
        (KeyCode) {"KEY_KP3",               GDK_KEY_KP_3},
        (KeyCode) {"KEY_KP0",               GDK_KEY_KP_0},
        (KeyCode) {"KEY_KPDOT",             0},
        (KeyCode) {"KEY_ZENKAKUHANKAKU",    GDK_KEY_Zenkaku_Hankaku},
        (KeyCode) {"KEY_102ND",             0},
        (KeyCode) {"KEY_F11",               GDK_KEY_F11},
        (KeyCode) {"KEY_F12",               GDK_KEY_F12},
        (KeyCode) {"KEY_RO",                0},
        (KeyCode) {"KEY_KATAKANA",          GDK_KEY_Katakana},
        (KeyCode) {"KEY_HIRAGANA",          GDK_KEY_Hiragana},
        (KeyCode) {"KEY_HENKAN",            GDK_KEY_Henkan},
        (KeyCode) {"KEY_KATAKANAHIRAGANA",  GDK_KEY_Hiragana_Katakana},
        (KeyCode) {"KEY_MUHENKAN",          GDK_KEY_Muhenkan},
        (KeyCode) {"KEY_KPJPCOMMA",         0},
        (KeyCode) {"KEY_KPENTER",           GDK_KEY_KP_Enter},
        (KeyCode) {"KEY_RIGHTCTRL",         GDK_KEY_Control_R},
        (KeyCode) {"KEY_KPSLASH",           0},
        (KeyCode) {"KEY_SYSRQ",             GDK_KEY_Sys_Req},
        (KeyCode) {"KEY_RIGHTALT",          GDK_KEY_Alt_R},
        (KeyCode) {"KEY_LINEFEED",          GDK_KEY_Linefeed},
        (KeyCode) {"KEY_HOME",              GDK_KEY_Home},
        (KeyCode) {"KEY_UP",                GDK_KEY_Up},
        (KeyCode) {"KEY_PAGEUP",            GDK_KEY_Page_Up},
        (KeyCode) {"KEY_LEFT",              GDK_KEY_Left},
        (KeyCode) {"KEY_RIGHT",             GDK_KEY_Right},
        (KeyCode) {"KEY_END",               GDK_KEY_End},
        (KeyCode) {"KEY_DOWN",              GDK_KEY_Down},
        (KeyCode) {"KEY_PAGEDOWN",          GDK_KEY_Page_Down},
        (KeyCode) {"KEY_INSERT",            GDK_KEY_Insert},
        (KeyCode) {"KEY_DELETE",            GDK_KEY_Delete},
        (KeyCode) {"KEY_MACRO",             0},
        (KeyCode) {"KEY_MUTE",              GDK_KEY_AudioMute},
        (KeyCode) {"KEY_VOLUMEDOWN",        0},
        (KeyCode) {"KEY_VOLUMEUP",          0},
        (KeyCode) {"KEY_POWER",             GDK_KEY_PowerOff},
        (KeyCode) {"KEY_KPEQUAL",           GDK_KEY_KP_Equal},
        (KeyCode) {"KEY_KPPLUSMINUS",       0},
        (KeyCode) {"KEY_PAUSE",             GDK_KEY_Pause},
        (KeyCode) {"KEY_SCALE",             0},
        (KeyCode) {"KEY_KPCOMMA",           0},
        (KeyCode) {"KEY_HANGEUL",           GDK_KEY_Hangul},
        (KeyCode) {"KEY_HANJA",             GDK_KEY_Hangul_Hanja},
        (KeyCode) {"KEY_YEN",               GDK_KEY_yen},
        (KeyCode) {"KEY_LEFTMETA",          GDK_KEY_Meta_L},
        (KeyCode) {"KEY_RIGHTMETA",         GDK_KEY_Meta_R},
        (KeyCode) {"KEY_COMPOSE",           0},
        (KeyCode) {"KEY_STOP",              GDK_KEY_Stop},
        (KeyCode) {"KEY_AGAIN",             0},
        (KeyCode) {"KEY_PROPS",             0},
        (KeyCode) {"KEY_UNDO",              GDK_KEY_Undo},
        (KeyCode) {"KEY_FRONT",             0},
        (KeyCode) {"KEY_COPY",              GDK_KEY_Copy},
        (KeyCode) {"KEY_OPEN",              GDK_KEY_Open},
        (KeyCode) {"KEY_PASTE",             GDK_KEY_Paste},
        (KeyCode) {"KEY_FIND",              GDK_KEY_Find},
        (KeyCode) {"KEY_CUT",               GDK_KEY_Cut},
        (KeyCode) {"KEY_HELP",              GDK_KEY_Help},
        (KeyCode) {"KEY_MENU",              GDK_KEY_Menu},
        (KeyCode) {"KEY_CALC",              GDK_KEY_Calculator},
        (KeyCode) {"KEY_SETUP",             0},
        (KeyCode) {"KEY_SLEEP",             GDK_KEY_Sleep},
        (KeyCode) {"KEY_WAKEUP",            GDK_KEY_WakeUp},
        (KeyCode) {"KEY_FILE",              0},
        (KeyCode) {"KEY_SENDFILE",          GDK_KEY_Send},
        (KeyCode) {"KEY_DELETEFILE",        0},
        (KeyCode) {"KEY_XFER",              GDK_KEY_Xfer},
        (KeyCode) {"KEY_PROG1",             0},
        (KeyCode) {"KEY_PROG2",             0},
        (KeyCode) {"KEY_WWW",               GDK_KEY_WWW},
        (KeyCode) {"KEY_MSDOS",             GDK_KEY_DOS},
        (KeyCode) {"KEY_COFFEE",            0},
        (KeyCode) {"KEY_ROTATE_DISPLAY",    0},
        (KeyCode) {"KEY_CYCLEWINDOWS",      0},
        (KeyCode) {"KEY_MAIL",              GDK_KEY_Mail},
        (KeyCode) {"KEY_BOOKMARKS",         0},
        (KeyCode) {"KEY_COMPUTER",          GDK_KEY_MyComputer},
        (KeyCode) {"KEY_BACK",              GDK_KEY_Back},
        (KeyCode) {"KEY_FORWARD",           GDK_KEY_Forward},
        (KeyCode) {"KEY_CLOSECD",           0},
        (KeyCode) {"KEY_EJECTCD",           0},
        (KeyCode) {"KEY_EJECTCLOSECD",      0},
        (KeyCode) {"KEY_NEXTSONG",          GDK_KEY_AudioNext},
        (KeyCode) {"KEY_PLAYPAUSE",         GDK_KEY_AudioPlay},
        (KeyCode) {"KEY_PREVIOUSSONG",      GDK_KEY_AudioPrev},
        (KeyCode) {"KEY_STOPCD",            GDK_KEY_AudioStop},
        (KeyCode) {"KEY_RECORD",            GDK_KEY_AudioRecord},
        (KeyCode) {"KEY_REWIND",            GDK_KEY_AudioRewind},
        (KeyCode) {"KEY_PHONE",             GDK_KEY_Phone},
        (KeyCode) {"KEY_ISO",               0},
        (KeyCode) {"KEY_CONFIG",            0},
        (KeyCode) {"KEY_HOMEPAGE",          GDK_KEY_HomePage},
        (KeyCode) {"KEY_REFRESH",           GDK_KEY_Refresh},
        (KeyCode) {"KEY_EXIT",              0},
        (KeyCode) {"KEY_MOVE",              0},
        (KeyCode) {"KEY_EDIT",              0},
        (KeyCode) {"KEY_SCROLLUP",          GDK_KEY_ScrollUp},
        (KeyCode) {"KEY_SCROLLDOWN",        GDK_KEY_ScrollDown},
        (KeyCode) {"KEY_KPLEFTPAREN",       0},
        (KeyCode) {"KEY_KPRIGHTPAREN",      0},
        (KeyCode) {"KEY_NEW",               GDK_KEY_New},
        (KeyCode) {"KEY_REDO",              GDK_KEY_Redo},
        (KeyCode) {"KEY_F13",               GDK_KEY_F13},
        (KeyCode) {"KEY_F14",               GDK_KEY_F14},
        (KeyCode) {"KEY_F15",               GDK_KEY_F15},
        (KeyCode) {"KEY_F16",               GDK_KEY_F16},
        (KeyCode) {"KEY_F17",               GDK_KEY_F17},
        (KeyCode) {"KEY_F18",               GDK_KEY_F18},
        (KeyCode) {"KEY_F19",               GDK_KEY_F19},
        (KeyCode) {"KEY_F20",               GDK_KEY_F20},
        (KeyCode) {"KEY_F21",               GDK_KEY_F21},
        (KeyCode) {"KEY_F22",               GDK_KEY_F22},
        (KeyCode) {"KEY_F23",               GDK_KEY_F23},
        (KeyCode) {"KEY_F24",               GDK_KEY_F24},
        (KeyCode) {"KEY_HANGUEL",           GDK_KEY_Hangul},
        (KeyCode) {"KEY_SCREENLOCK",        0},
        (KeyCode) {"KEY_DIRECTION",         0},
        (KeyCode) {"KEY_DASHBOARD",         0},
        (KeyCode) {"KEY_WIMAX",             0},
        (KeyCode) {"KEY_PLAYCD",            0},
        (KeyCode) {"KEY_PAUSECD",           0},
        (KeyCode) {"KEY_PROG3",             0},
        (KeyCode) {"KEY_PROG4",             0},
        (KeyCode) {"KEY_ALL_APPLICATIONS",  0},
        (KeyCode) {"KEY_SUSPEND",           GDK_KEY_Suspend},
        (KeyCode) {"KEY_CLOSE",             GDK_KEY_Close},
        (KeyCode) {"KEY_PLAY",              GDK_KEY_AudioPlay},
        (KeyCode) {"KEY_FASTFORWARD",       0},
        (KeyCode) {"KEY_BASSBOOST",         0},
        (KeyCode) {"KEY_PRINT",             GDK_KEY_Print},
        (KeyCode) {"KEY_HP",                0},
        (KeyCode) {"KEY_CAMERA",            GDK_KEY_WebCam},
        (KeyCode) {"KEY_SOUND",             0},
        (KeyCode) {"KEY_QUESTION",          GDK_KEY_question},
        (KeyCode) {"KEY_EMAIL",             0},
        (KeyCode) {"KEY_CHAT",              0},
        (KeyCode) {"KEY_SEARCH",            GDK_KEY_Search},
        (KeyCode) {"KEY_CONNECT",           0},
        (KeyCode) {"KEY_FINANCE",           GDK_KEY_Finance},
        (KeyCode) {"KEY_SPORT",             0},
        (KeyCode) {"KEY_SHOP",              GDK_KEY_Shop},
        (KeyCode) {"KEY_ALTERASE",          0},
        (KeyCode) {"KEY_CANCEL",            GDK_KEY_Cancel},
        (KeyCode) {"KEY_BRIGHTNESSDOWN",    GDK_KEY_MonBrightnessDown},
        (KeyCode) {"KEY_BRIGHTNESSUP",      GDK_KEY_MonBrightnessUp},
        (KeyCode) {"KEY_MEDIA",             GDK_KEY_AudioMedia},
        (KeyCode) {"KEY_SWITCHVIDEOMODE",   0},
        (KeyCode) {"KEY_KBDILLUMTOGGLE",    0},
        (KeyCode) {"KEY_KBDILLUMDOWN",      0},
        (KeyCode) {"KEY_KBDILLUMUP",        0},
        (KeyCode) {"KEY_SEND",              GDK_KEY_Send},
        (KeyCode) {"KEY_REPLY",             GDK_KEY_Reply},
        (KeyCode) {"KEY_FORWARDMAIL",       GDK_KEY_MailForward},
        (KeyCode) {"KEY_SAVE",              GDK_KEY_Save},
        (KeyCode) {"KEY_DOCUMENTS",         GDK_KEY_Documents},
        (KeyCode) {"KEY_BATTERY",           GDK_KEY_Battery},
        (KeyCode) {"KEY_BLUETOOTH",         GDK_KEY_Bluetooth},
        (KeyCode) {"KEY_WLAN",              GDK_KEY_WLAN},
        (KeyCode) {"KEY_UWB",               GDK_KEY_UWB},
        (KeyCode) {"KEY_UNKNOWN",           0},
        (KeyCode) {"KEY_VIDEO_NEXT",        0},
        (KeyCode) {"KEY_VIDEO_PREV",        0},
        (KeyCode) {"KEY_BRIGHTNESS_CYCLE",  0},
        (KeyCode) {"KEY_BRIGHTNESS_AUTO",   0},
        (KeyCode) {"KEY_DISPLAY_OFF",       0},
        (KeyCode) {"KEY_WWAN",              GDK_KEY_WWAN},
        (KeyCode) {"KEY_RFKILL",            GDK_KEY_RFKill},
        (KeyCode) {"KEY_MICMUTE",           GDK_KEY_AudioMicMute},
        (KeyCode) {"KEY_BRIGHTNESS_ZERO",   0},
};

struct _LKeyCode {
    GObject parent_instance;

    GHashTable *kernel_to_gdk;
    GHashTable *gdk_to_kernel;
};

G_DEFINE_FINAL_TYPE(LKeyCode, l_key_code, G_TYPE_OBJECT)


static void
init_codes_tables(LKeyCode *self) {
    int iter = 0;

    while (iter < (sizeof codes / sizeof(KeyCode))) {
        char **kernel = (char **) &codes[iter].kernel;
        guint *gdk = (guint *) &codes[iter].gdk;

        g_hash_table_insert(self->kernel_to_gdk,*kernel,gdk);
        g_hash_table_insert(self->gdk_to_kernel,gdk,kernel);

        iter++;
    }
}

void *
l_key_code_kernel_to_gdk(LKeyCode *self, char *key) {
    guint *gdk_key = g_hash_table_lookup(self->kernel_to_gdk, key);
    return gdk_key;
}

void *
l_key_code_gdk_to_kernel(LKeyCode *self, guint key) {
    char **kernel_key = g_hash_table_lookup(self->gdk_to_kernel, &key);
    return kernel_key;
}

LKeyCode *
l_key_code_new(void) {
    return g_object_new(L_TYPE_KEY_CODE, NULL);
}

static void
l_key_code_class_init(LKeyCodeClass *klass) {}

static void
l_key_code_init(LKeyCode *self) {
    self->kernel_to_gdk = g_hash_table_new(g_str_hash, g_str_equal);
    self->gdk_to_kernel = g_hash_table_new(g_int_hash, g_int_equal);
    init_codes_tables(self);
}
