#pragma once

struct SDL_Keysym;
struct SdlKeyboardEventData;
struct SDL_CommonEvent;

namespace VulkanSimplified
{
    enum SdlScancode : int32_t
    {
        SDL_SCANCODE_MODULE_UNKNOWN = 0,

        /**
         *  \name Usage page 0x07
         *
         *  These values are from usage page 0x07 (USB keyboard page).
         */
         /* @{ */

        SDL_SCANCODE_MODULE_A = 4,
        SDL_SCANCODE_MODULE_B = 5,
        SDL_SCANCODE_MODULE_C = 6,
        SDL_SCANCODE_MODULE_D = 7,
        SDL_SCANCODE_MODULE_E = 8,
        SDL_SCANCODE_MODULE_F = 9,
        SDL_SCANCODE_MODULE_G = 10,
        SDL_SCANCODE_MODULE_H = 11,
        SDL_SCANCODE_MODULE_I = 12,
        SDL_SCANCODE_MODULE_J = 13,
        SDL_SCANCODE_MODULE_K = 14,
        SDL_SCANCODE_MODULE_L = 15,
        SDL_SCANCODE_MODULE_M = 16,
        SDL_SCANCODE_MODULE_N = 17,
        SDL_SCANCODE_MODULE_O = 18,
        SDL_SCANCODE_MODULE_P = 19,
        SDL_SCANCODE_MODULE_Q = 20,
        SDL_SCANCODE_MODULE_R = 21,
        SDL_SCANCODE_MODULE_S = 22,
        SDL_SCANCODE_MODULE_T = 23,
        SDL_SCANCODE_MODULE_U = 24,
        SDL_SCANCODE_MODULE_V = 25,
        SDL_SCANCODE_MODULE_W = 26,
        SDL_SCANCODE_MODULE_X = 27,
        SDL_SCANCODE_MODULE_Y = 28,
        SDL_SCANCODE_MODULE_Z = 29,

        SDL_SCANCODE_MODULE_1 = 30,
        SDL_SCANCODE_MODULE_2 = 31,
        SDL_SCANCODE_MODULE_3 = 32,
        SDL_SCANCODE_MODULE_4 = 33,
        SDL_SCANCODE_MODULE_5 = 34,
        SDL_SCANCODE_MODULE_6 = 35,
        SDL_SCANCODE_MODULE_7 = 36,
        SDL_SCANCODE_MODULE_8 = 37,
        SDL_SCANCODE_MODULE_9 = 38,
        SDL_SCANCODE_MODULE_0 = 39,

        SDL_SCANCODE_MODULE_RETURN = 40,
        SDL_SCANCODE_MODULE_ESCAPE = 41,
        SDL_SCANCODE_MODULE_BACKSPACE = 42,
        SDL_SCANCODE_MODULE_TAB = 43,
        SDL_SCANCODE_MODULE_SPACE = 44,

        SDL_SCANCODE_MODULE_MINUS = 45,
        SDL_SCANCODE_MODULE_EQUALS = 46,
        SDL_SCANCODE_MODULE_LEFTBRACKET = 47,
        SDL_SCANCODE_MODULE_RIGHTBRACKET = 48,
        SDL_SCANCODE_MODULE_BACKSLASH = 49, /**< Located at the lower left of the return
                                      *   key on ISO keyboards and at the right end
                                      *   of the QWERTY row on ANSI keyboards.
                                      *   Produces REVERSE SOLIDUS (backslash) and
                                      *   VERTICAL LINE in a US layout, REVERSE
                                      *   SOLIDUS and VERTICAL LINE in a UK Mac
                                      *   layout, NUMBER SIGN and TILDE in a UK
                                      *   Windows layout, DOLLAR SIGN and POUND SIGN
                                      *   in a Swiss German layout, NUMBER SIGN and
                                      *   APOSTROPHE in a German layout, GRAVE
                                      *   ACCENT and POUND SIGN in a French Mac
                                      *   layout, and ASTERISK and MICRO SIGN in a
                                      *   French Windows layout.
                                      */
        SDL_SCANCODE_MODULE_NONUSHASH = 50, /**< ISO USB keyboards actually use this code
                                      *   instead of 49 for the same key, but all
                                      *   OSes I've seen treat the two codes
                                      *   identically. So, as an implementor, unless
                                      *   your keyboard generates both of those
                                      *   codes and your OS treats them differently,
                                      *   you should generate SDL_SCANCODE_MODULE_BACKSLASH
                                      *   instead of this code. As a user, you
                                      *   should not rely on this code because SDL
                                      *   will never generate it with most (all?)
                                      *   keyboards.
                                      */
        SDL_SCANCODE_MODULE_SEMICOLON = 51,
        SDL_SCANCODE_MODULE_APOSTROPHE = 52,
        SDL_SCANCODE_MODULE_GRAVE = 53, /**< Located in the top left corner (on both ANSI
                                  *   and ISO keyboards). Produces GRAVE ACCENT and
                                  *   TILDE in a US Windows layout and in US and UK
                                  *   Mac layouts on ANSI keyboards, GRAVE ACCENT
                                  *   and NOT SIGN in a UK Windows layout, SECTION
                                  *   SIGN and PLUS-MINUS SIGN in US and UK Mac
                                  *   layouts on ISO keyboards, SECTION SIGN and
                                  *   DEGREE SIGN in a Swiss German layout (Mac:
                                  *   only on ISO keyboards), CIRCUMFLEX ACCENT and
                                  *   DEGREE SIGN in a German layout (Mac: only on
                                  *   ISO keyboards), SUPERSCRIPT TWO and TILDE in a
                                  *   French Windows layout, COMMERCIAL AT and
                                  *   NUMBER SIGN in a French Mac layout on ISO
                                  *   keyboards, and LESS-THAN SIGN and GREATER-THAN
                                  *   SIGN in a Swiss German, German, or French Mac
                                  *   layout on ANSI keyboards.
                                  */
        SDL_SCANCODE_MODULE_COMMA = 54,
        SDL_SCANCODE_MODULE_PERIOD = 55,
        SDL_SCANCODE_MODULE_SLASH = 56,

        SDL_SCANCODE_MODULE_CAPSLOCK = 57,

        SDL_SCANCODE_MODULE_F1 = 58,
        SDL_SCANCODE_MODULE_F2 = 59,
        SDL_SCANCODE_MODULE_F3 = 60,
        SDL_SCANCODE_MODULE_F4 = 61,
        SDL_SCANCODE_MODULE_F5 = 62,
        SDL_SCANCODE_MODULE_F6 = 63,
        SDL_SCANCODE_MODULE_F7 = 64,
        SDL_SCANCODE_MODULE_F8 = 65,
        SDL_SCANCODE_MODULE_F9 = 66,
        SDL_SCANCODE_MODULE_F10 = 67,
        SDL_SCANCODE_MODULE_F11 = 68,
        SDL_SCANCODE_MODULE_F12 = 69,

        SDL_SCANCODE_MODULE_PRINTSCREEN = 70,
        SDL_SCANCODE_MODULE_SCROLLLOCK = 71,
        SDL_SCANCODE_MODULE_PAUSE = 72,
        SDL_SCANCODE_MODULE_INSERT = 73, /**< insert on PC, help on some Mac keyboards (but
                                       does send code 73, not 117) */
        SDL_SCANCODE_MODULE_HOME = 74,
        SDL_SCANCODE_MODULE_PAGEUP = 75,
        SDL_SCANCODE_MODULE_DELETE = 76,
        SDL_SCANCODE_MODULE_END = 77,
        SDL_SCANCODE_MODULE_PAGEDOWN = 78,
        SDL_SCANCODE_MODULE_RIGHT = 79,
        SDL_SCANCODE_MODULE_LEFT = 80,
        SDL_SCANCODE_MODULE_DOWN = 81,
        SDL_SCANCODE_MODULE_UP = 82,

        SDL_SCANCODE_MODULE_NUMLOCKCLEAR = 83, /**< num lock on PC, clear on Mac keyboards
                                         */
        SDL_SCANCODE_MODULE_KP_DIVIDE = 84,
        SDL_SCANCODE_MODULE_KP_MULTIPLY = 85,
        SDL_SCANCODE_MODULE_KP_MINUS = 86,
        SDL_SCANCODE_MODULE_KP_PLUS = 87,
        SDL_SCANCODE_MODULE_KP_ENTER = 88,
        SDL_SCANCODE_MODULE_KP_1 = 89,
        SDL_SCANCODE_MODULE_KP_2 = 90,
        SDL_SCANCODE_MODULE_KP_3 = 91,
        SDL_SCANCODE_MODULE_KP_4 = 92,
        SDL_SCANCODE_MODULE_KP_5 = 93,
        SDL_SCANCODE_MODULE_KP_6 = 94,
        SDL_SCANCODE_MODULE_KP_7 = 95,
        SDL_SCANCODE_MODULE_KP_8 = 96,
        SDL_SCANCODE_MODULE_KP_9 = 97,
        SDL_SCANCODE_MODULE_KP_0 = 98,
        SDL_SCANCODE_MODULE_KP_PERIOD = 99,

        SDL_SCANCODE_MODULE_NONUSBACKSLASH = 100, /**< This is the additional key that ISO
                                            *   keyboards have over ANSI ones,
                                            *   located between left shift and Y.
                                            *   Produces GRAVE ACCENT and TILDE in a
                                            *   US or UK Mac layout, REVERSE SOLIDUS
                                            *   (backslash) and VERTICAL LINE in a
                                            *   US or UK Windows layout, and
                                            *   LESS-THAN SIGN and GREATER-THAN SIGN
                                            *   in a Swiss German, German, or French
                                            *   layout. */
        SDL_SCANCODE_MODULE_APPLICATION = 101, /**< windows contextual menu, compose */
        SDL_SCANCODE_MODULE_POWER = 102, /**< The USB document says this is a status flag,
                                   *   not a physical key - but some Mac keyboards
                                   *   do have a power key. */
        SDL_SCANCODE_MODULE_KP_EQUALS = 103,
        SDL_SCANCODE_MODULE_F13 = 104,
        SDL_SCANCODE_MODULE_F14 = 105,
        SDL_SCANCODE_MODULE_F15 = 106,
        SDL_SCANCODE_MODULE_F16 = 107,
        SDL_SCANCODE_MODULE_F17 = 108,
        SDL_SCANCODE_MODULE_F18 = 109,
        SDL_SCANCODE_MODULE_F19 = 110,
        SDL_SCANCODE_MODULE_F20 = 111,
        SDL_SCANCODE_MODULE_F21 = 112,
        SDL_SCANCODE_MODULE_F22 = 113,
        SDL_SCANCODE_MODULE_F23 = 114,
        SDL_SCANCODE_MODULE_F24 = 115,
        SDL_SCANCODE_MODULE_EXECUTE = 116,
        SDL_SCANCODE_MODULE_HELP = 117,    /**< AL Integrated Help Center */
        SDL_SCANCODE_MODULE_MENU = 118,    /**< Menu (show menu) */
        SDL_SCANCODE_MODULE_SELECT = 119,
        SDL_SCANCODE_MODULE_STOP = 120,    /**< AC Stop */
        SDL_SCANCODE_MODULE_AGAIN = 121,   /**< AC Redo/Repeat */
        SDL_SCANCODE_MODULE_UNDO = 122,    /**< AC Undo */
        SDL_SCANCODE_MODULE_CUT = 123,     /**< AC Cut */
        SDL_SCANCODE_MODULE_COPY = 124,    /**< AC Copy */
        SDL_SCANCODE_MODULE_PASTE = 125,   /**< AC Paste */
        SDL_SCANCODE_MODULE_FIND = 126,    /**< AC Find */
        SDL_SCANCODE_MODULE_MUTE = 127,
        SDL_SCANCODE_MODULE_VOLUMEUP = 128,
        SDL_SCANCODE_MODULE_VOLUMEDOWN = 129,
        /* not sure whether there's a reason to enable these */
        /*     SDL_SCANCODE_MODULE_LOCKINGCAPSLOCK = 130,  */
        /*     SDL_SCANCODE_MODULE_LOCKINGNUMLOCK = 131, */
        /*     SDL_SCANCODE_MODULE_LOCKINGSCROLLLOCK = 132, */
        SDL_SCANCODE_MODULE_KP_COMMA = 133,
        SDL_SCANCODE_MODULE_KP_EQUALSAS400 = 134,

        SDL_SCANCODE_MODULE_INTERNATIONAL1 = 135, /**< used on Asian keyboards, see
                                                footnotes in USB doc */
        SDL_SCANCODE_MODULE_INTERNATIONAL2 = 136,
        SDL_SCANCODE_MODULE_INTERNATIONAL3 = 137, /**< Yen */
        SDL_SCANCODE_MODULE_INTERNATIONAL4 = 138,
        SDL_SCANCODE_MODULE_INTERNATIONAL5 = 139,
        SDL_SCANCODE_MODULE_INTERNATIONAL6 = 140,
        SDL_SCANCODE_MODULE_INTERNATIONAL7 = 141,
        SDL_SCANCODE_MODULE_INTERNATIONAL8 = 142,
        SDL_SCANCODE_MODULE_INTERNATIONAL9 = 143,
        SDL_SCANCODE_MODULE_LANG1 = 144, /**< Hangul/English toggle */
        SDL_SCANCODE_MODULE_LANG2 = 145, /**< Hanja conversion */
        SDL_SCANCODE_MODULE_LANG3 = 146, /**< Katakana */
        SDL_SCANCODE_MODULE_LANG4 = 147, /**< Hiragana */
        SDL_SCANCODE_MODULE_LANG5 = 148, /**< Zenkaku/Hankaku */
        SDL_SCANCODE_MODULE_LANG6 = 149, /**< reserved */
        SDL_SCANCODE_MODULE_LANG7 = 150, /**< reserved */
        SDL_SCANCODE_MODULE_LANG8 = 151, /**< reserved */
        SDL_SCANCODE_MODULE_LANG9 = 152, /**< reserved */

        SDL_SCANCODE_MODULE_ALTERASE = 153,    /**< Erase-Eaze */
        SDL_SCANCODE_MODULE_SYSREQ = 154,
        SDL_SCANCODE_MODULE_CANCEL = 155,      /**< AC Cancel */
        SDL_SCANCODE_MODULE_CLEAR = 156,
        SDL_SCANCODE_MODULE_PRIOR = 157,
        SDL_SCANCODE_MODULE_RETURN2 = 158,
        SDL_SCANCODE_MODULE_SEPARATOR = 159,
        SDL_SCANCODE_MODULE_OUT = 160,
        SDL_SCANCODE_MODULE_OPER = 161,
        SDL_SCANCODE_MODULE_CLEARAGAIN = 162,
        SDL_SCANCODE_MODULE_CRSEL = 163,
        SDL_SCANCODE_MODULE_EXSEL = 164,

        SDL_SCANCODE_MODULE_KP_00 = 176,
        SDL_SCANCODE_MODULE_KP_000 = 177,
        SDL_SCANCODE_MODULE_THOUSANDSSEPARATOR = 178,
        SDL_SCANCODE_MODULE_DECIMALSEPARATOR = 179,
        SDL_SCANCODE_MODULE_CURRENCYUNIT = 180,
        SDL_SCANCODE_MODULE_CURRENCYSUBUNIT = 181,
        SDL_SCANCODE_MODULE_KP_LEFTPAREN = 182,
        SDL_SCANCODE_MODULE_KP_RIGHTPAREN = 183,
        SDL_SCANCODE_MODULE_KP_LEFTBRACE = 184,
        SDL_SCANCODE_MODULE_KP_RIGHTBRACE = 185,
        SDL_SCANCODE_MODULE_KP_TAB = 186,
        SDL_SCANCODE_MODULE_KP_BACKSPACE = 187,
        SDL_SCANCODE_MODULE_KP_A = 188,
        SDL_SCANCODE_MODULE_KP_B = 189,
        SDL_SCANCODE_MODULE_KP_C = 190,
        SDL_SCANCODE_MODULE_KP_D = 191,
        SDL_SCANCODE_MODULE_KP_E = 192,
        SDL_SCANCODE_MODULE_KP_F = 193,
        SDL_SCANCODE_MODULE_KP_XOR = 194,
        SDL_SCANCODE_MODULE_KP_POWER = 195,
        SDL_SCANCODE_MODULE_KP_PERCENT = 196,
        SDL_SCANCODE_MODULE_KP_LESS = 197,
        SDL_SCANCODE_MODULE_KP_GREATER = 198,
        SDL_SCANCODE_MODULE_KP_AMPERSAND = 199,
        SDL_SCANCODE_MODULE_KP_DBLAMPERSAND = 200,
        SDL_SCANCODE_MODULE_KP_VERTICALBAR = 201,
        SDL_SCANCODE_MODULE_KP_DBLVERTICALBAR = 202,
        SDL_SCANCODE_MODULE_KP_COLON = 203,
        SDL_SCANCODE_MODULE_KP_HASH = 204,
        SDL_SCANCODE_MODULE_KP_SPACE = 205,
        SDL_SCANCODE_MODULE_KP_AT = 206,
        SDL_SCANCODE_MODULE_KP_EXCLAM = 207,
        SDL_SCANCODE_MODULE_KP_MEMSTORE = 208,
        SDL_SCANCODE_MODULE_KP_MEMRECALL = 209,
        SDL_SCANCODE_MODULE_KP_MEMCLEAR = 210,
        SDL_SCANCODE_MODULE_KP_MEMADD = 211,
        SDL_SCANCODE_MODULE_KP_MEMSUBTRACT = 212,
        SDL_SCANCODE_MODULE_KP_MEMMULTIPLY = 213,
        SDL_SCANCODE_MODULE_KP_MEMDIVIDE = 214,
        SDL_SCANCODE_MODULE_KP_PLUSMINUS = 215,
        SDL_SCANCODE_MODULE_KP_CLEAR = 216,
        SDL_SCANCODE_MODULE_KP_CLEARENTRY = 217,
        SDL_SCANCODE_MODULE_KP_BINARY = 218,
        SDL_SCANCODE_MODULE_KP_OCTAL = 219,
        SDL_SCANCODE_MODULE_KP_DECIMAL = 220,
        SDL_SCANCODE_MODULE_KP_HEXADECIMAL = 221,

        SDL_SCANCODE_MODULE_LCTRL = 224,
        SDL_SCANCODE_MODULE_LSHIFT = 225,
        SDL_SCANCODE_MODULE_LALT = 226, /**< alt, option */
        SDL_SCANCODE_MODULE_LGUI = 227, /**< windows, command (apple), meta */
        SDL_SCANCODE_MODULE_RCTRL = 228,
        SDL_SCANCODE_MODULE_RSHIFT = 229,
        SDL_SCANCODE_MODULE_RALT = 230, /**< alt gr, option */
        SDL_SCANCODE_MODULE_RGUI = 231, /**< windows, command (apple), meta */

        SDL_SCANCODE_MODULE_MODE = 257,    /**< I'm not sure if this is really not covered
                                     *   by any of the above, but since there's a
                                     *   special KMOD_DATA_MODE for it I'm adding it here
                                     */

                                     /* @} *//* Usage page 0x07 */

                                     /**
                                      *  \name Usage page 0x0C
                                      *
                                      *  These values are mapped from usage page 0x0C (USB consumer page).
                                      *  See https://usb.org/sites/default/files/hut1_2.pdf
                                      *
                                      *  There are way more keys in the spec than we can represent in the
                                      *  current scancode range, so pick the ones that commonly come up in
                                      *  real world usage.
                                      */
                                      /* @{ */

        SDL_SCANCODE_MODULE_AUDIONEXT = 258,
        SDL_SCANCODE_MODULE_AUDIOPREV = 259,
        SDL_SCANCODE_MODULE_AUDIOSTOP = 260,
        SDL_SCANCODE_MODULE_AUDIOPLAY = 261,
        SDL_SCANCODE_MODULE_AUDIOMUTE = 262,
        SDL_SCANCODE_MODULE_MEDIASELECT = 263,
        SDL_SCANCODE_MODULE_WWW = 264,             /**< AL Internet Browser */
        SDL_SCANCODE_MODULE_MAIL = 265,
        SDL_SCANCODE_MODULE_CALCULATOR = 266,      /**< AL Calculator */
        SDL_SCANCODE_MODULE_COMPUTER = 267,
        SDL_SCANCODE_MODULE_AC_SEARCH = 268,       /**< AC Search */
        SDL_SCANCODE_MODULE_AC_HOME = 269,         /**< AC Home */
        SDL_SCANCODE_MODULE_AC_BACK = 270,         /**< AC Back */
        SDL_SCANCODE_MODULE_AC_FORWARD = 271,      /**< AC Forward */
        SDL_SCANCODE_MODULE_AC_STOP = 272,         /**< AC Stop */
        SDL_SCANCODE_MODULE_AC_REFRESH = 273,      /**< AC Refresh */
        SDL_SCANCODE_MODULE_AC_BOOKMARKS = 274,    /**< AC Bookmarks */

        /* @} *//* Usage page 0x0C */

        /**
         *  \name Walther keys
         *
         *  These are values that Christian Walther added (for mac keyboard?).
         */
         /* @{ */

        SDL_SCANCODE_MODULE_BRIGHTNESSDOWN = 275,
        SDL_SCANCODE_MODULE_BRIGHTNESSUP = 276,
        SDL_SCANCODE_MODULE_DISPLAYSWITCH = 277, /**< display mirroring/dual display
                                               switch, video mode switch */
        SDL_SCANCODE_MODULE_KBDILLUMTOGGLE = 278,
        SDL_SCANCODE_MODULE_KBDILLUMDOWN = 279,
        SDL_SCANCODE_MODULE_KBDILLUMUP = 280,
        SDL_SCANCODE_MODULE_EJECT = 281,
        SDL_SCANCODE_MODULE_SLEEP = 282,           /**< SC System Sleep */

        SDL_SCANCODE_MODULE_APP1 = 283,
        SDL_SCANCODE_MODULE_APP2 = 284,

        /* @} *//* Walther keys */

        /**
         *  \name Usage page 0x0C (additional media keys)
         *
         *  These values are mapped from usage page 0x0C (USB consumer page).
         */
         /* @{ */

        SDL_SCANCODE_MODULE_AUDIOREWIND = 285,
        SDL_SCANCODE_MODULE_AUDIOFASTFORWARD = 286,

        /* @} *//* Usage page 0x0C (additional media keys) */

        /**
         *  \name Mobile keys
         *
         *  These are values that are often used on mobile phones.
         */
         /* @{ */

        SDL_SCANCODE_MODULE_SOFTLEFT = 287, /**< Usually situated below the display on phones and
                                          used as a multi-function feature key for selecting
                                          a software defined function shown on the bottom left
                                          of the display. */
        SDL_SCANCODE_MODULE_SOFTRIGHT = 288, /**< Usually situated below the display on phones and
                                           used as a multi-function feature key for selecting
                                           a software defined function shown on the bottom right
                                           of the display. */
        SDL_SCANCODE_MODULE_CALL = 289, /**< Used for accepting phone calls. */
        SDL_SCANCODE_MODULE_ENDCALL = 290, /**< Used for rejecting phone calls. */

        /* @} *//* Mobile keys */

        /* Add any other keys here. */

        SDL_DATA_NUM_SCANCODES = 512 /**< not a key, just marks the number of scancodes
                                     for array bounds */
    };

#define SDLK_DATA_SCANCODE_MASK (1<<30)
#define SDL_DATA_SCANCODE_TO_KEYCODE(X)  (X | SDLK_DATA_SCANCODE_MASK)

    enum SdlKeycode : int32_t
    {
        SDLK_DATA_UNKNOWN = 0,

        SDLK_DATA_RETURN = '\r',
        SDLK_DATA_ESCAPE = '\x1B',
        SDLK_DATA_BACKSPACE = '\b',
        SDLK_DATA_TAB = '\t',
        SDLK_DATA_SPACE = ' ',
        SDLK_DATA_EXCLAIM = '!',
        SDLK_DATA_QUOTEDBL = '"',
        SDLK_DATA_HASH = '#',
        SDLK_DATA_PERCENT = '%',
        SDLK_DATA_DOLLAR = '$',
        SDLK_DATA_AMPERSAND = '&',
        SDLK_DATA_QUOTE = '\'',
        SDLK_DATA_LEFTPAREN = '(',
        SDLK_DATA_RIGHTPAREN = ')',
        SDLK_DATA_ASTERISK = '*',
        SDLK_DATA_PLUS = '+',
        SDLK_DATA_COMMA = ',',
        SDLK_DATA_MINUS = '-',
        SDLK_DATA_PERIOD = '.',
        SDLK_DATA_SLASH = '/',
        SDLK_DATA_0 = '0',
        SDLK_DATA_1 = '1',
        SDLK_DATA_2 = '2',
        SDLK_DATA_3 = '3',
        SDLK_DATA_4 = '4',
        SDLK_DATA_5 = '5',
        SDLK_DATA_6 = '6',
        SDLK_DATA_7 = '7',
        SDLK_DATA_8 = '8',
        SDLK_DATA_9 = '9',
        SDLK_DATA_COLON = ':',
        SDLK_DATA_SEMICOLON = ';',
        SDLK_DATA_LESS = '<',
        SDLK_DATA_EQUALS = '=',
        SDLK_DATA_GREATER = '>',
        SDLK_DATA_QUESTION = '?',
        SDLK_DATA_AT = '@',

        /*
           Skip uppercase letters
         */

        SDLK_DATA_LEFTBRACKET = '[',
        SDLK_DATA_BACKSLASH = '\\',
        SDLK_DATA_RIGHTBRACKET = ']',
        SDLK_DATA_CARET = '^',
        SDLK_DATA_UNDERSCORE = '_',
        SDLK_DATA_BACKQUOTE = '`',
        SDLK_DATA_a = 'a',
        SDLK_DATA_b = 'b',
        SDLK_DATA_c = 'c',
        SDLK_DATA_d = 'd',
        SDLK_DATA_e = 'e',
        SDLK_DATA_f = 'f',
        SDLK_DATA_g = 'g',
        SDLK_DATA_h = 'h',
        SDLK_DATA_i = 'i',
        SDLK_DATA_j = 'j',
        SDLK_DATA_k = 'k',
        SDLK_DATA_l = 'l',
        SDLK_DATA_m = 'm',
        SDLK_DATA_n = 'n',
        SDLK_DATA_o = 'o',
        SDLK_DATA_p = 'p',
        SDLK_DATA_q = 'q',
        SDLK_DATA_r = 'r',
        SDLK_DATA_s = 's',
        SDLK_DATA_t = 't',
        SDLK_DATA_u = 'u',
        SDLK_DATA_v = 'v',
        SDLK_DATA_w = 'w',
        SDLK_DATA_x = 'x',
        SDLK_DATA_y = 'y',
        SDLK_DATA_z = 'z',

        SDLK_DATA_CAPSLOCK = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CAPSLOCK),

        SDLK_DATA_F1 = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F1),
        SDLK_DATA_F2 = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F2),
        SDLK_DATA_F3 = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F3),
        SDLK_DATA_F4 = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F4),
        SDLK_DATA_F5 = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F5),
        SDLK_DATA_F6 = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F6),
        SDLK_DATA_F7 = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F7),
        SDLK_DATA_F8 = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F8),
        SDLK_DATA_F9 = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F9),
        SDLK_DATA_F10 = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F10),
        SDLK_DATA_F11 = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F11),
        SDLK_DATA_F12 = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F12),

        SDLK_DATA_PRINTSCREEN = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PRINTSCREEN),
        SDLK_DATA_SCROLLLOCK = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SCROLLLOCK),
        SDLK_DATA_PAUSE = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PAUSE),
        SDLK_DATA_INSERT = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_INSERT),
        SDLK_DATA_HOME = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_HOME),
        SDLK_DATA_PAGEUP = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PAGEUP),
        SDLK_DATA_DELETE = '\x7F',
        SDLK_DATA_END = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_END),
        SDLK_DATA_PAGEDOWN = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PAGEDOWN),
        SDLK_DATA_RIGHT = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RIGHT),
        SDLK_DATA_LEFT = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LEFT),
        SDLK_DATA_DOWN = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_DOWN),
        SDLK_DATA_UP = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_UP),

        SDLK_DATA_NUMLOCKCLEAR = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_NUMLOCKCLEAR),
        SDLK_DATA_KP_DIVIDE = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_DIVIDE),
        SDLK_DATA_KP_MULTIPLY = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MULTIPLY),
        SDLK_DATA_KP_MINUS = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MINUS),
        SDLK_DATA_KP_PLUS = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_PLUS),
        SDLK_DATA_KP_ENTER = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_ENTER),
        SDLK_DATA_KP_1 = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_1),
        SDLK_DATA_KP_2 = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_2),
        SDLK_DATA_KP_3 = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_3),
        SDLK_DATA_KP_4 = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_4),
        SDLK_DATA_KP_5 = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_5),
        SDLK_DATA_KP_6 = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_6),
        SDLK_DATA_KP_7 = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_7),
        SDLK_DATA_KP_8 = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_8),
        SDLK_DATA_KP_9 = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_9),
        SDLK_DATA_KP_0 = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_0),
        SDLK_DATA_KP_PERIOD = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_PERIOD),

        SDLK_DATA_APPLICATION = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_APPLICATION),
        SDLK_DATA_POWER = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_POWER),
        SDLK_DATA_KP_EQUALS = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_EQUALS),
        SDLK_DATA_F13 = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F13),
        SDLK_DATA_F14 = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F14),
        SDLK_DATA_F15 = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F15),
        SDLK_DATA_F16 = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F16),
        SDLK_DATA_F17 = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F17),
        SDLK_DATA_F18 = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F18),
        SDLK_DATA_F19 = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F19),
        SDLK_DATA_F20 = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F20),
        SDLK_DATA_F21 = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F21),
        SDLK_DATA_F22 = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F22),
        SDLK_DATA_F23 = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F23),
        SDLK_DATA_F24 = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F24),
        SDLK_DATA_EXECUTE = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_EXECUTE),
        SDLK_DATA_HELP = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_HELP),
        SDLK_DATA_MENU = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MENU),
        SDLK_DATA_SELECT = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SELECT),
        SDLK_DATA_STOP = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_STOP),
        SDLK_DATA_AGAIN = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AGAIN),
        SDLK_DATA_UNDO = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_UNDO),
        SDLK_DATA_CUT = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CUT),
        SDLK_DATA_COPY = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_COPY),
        SDLK_DATA_PASTE = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PASTE),
        SDLK_DATA_FIND = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_FIND),
        SDLK_DATA_MUTE = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MUTE),
        SDLK_DATA_VOLUMEUP = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_VOLUMEUP),
        SDLK_DATA_VOLUMEDOWN = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_VOLUMEDOWN),
        SDLK_DATA_KP_COMMA = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_COMMA),
        SDLK_DATA_KP_EQUALSAS400 =
        SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_EQUALSAS400),

        SDLK_DATA_ALTERASE = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_ALTERASE),
        SDLK_DATA_SYSREQ = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SYSREQ),
        SDLK_DATA_CANCEL = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CANCEL),
        SDLK_DATA_CLEAR = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CLEAR),
        SDLK_DATA_PRIOR = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PRIOR),
        SDLK_DATA_RETURN2 = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RETURN2),
        SDLK_DATA_SEPARATOR = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SEPARATOR),
        SDLK_DATA_OUT = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_OUT),
        SDLK_DATA_OPER = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_OPER),
        SDLK_DATA_CLEARAGAIN = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CLEARAGAIN),
        SDLK_DATA_CRSEL = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CRSEL),
        SDLK_DATA_EXSEL = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_EXSEL),

        SDLK_DATA_KP_00 = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_00),
        SDLK_DATA_KP_000 = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_000),
        SDLK_DATA_THOUSANDSSEPARATOR =
        SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_THOUSANDSSEPARATOR),
        SDLK_DATA_DECIMALSEPARATOR =
        SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_DECIMALSEPARATOR),
        SDLK_DATA_CURRENCYUNIT = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CURRENCYUNIT),
        SDLK_DATA_CURRENCYSUBUNIT =
        SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CURRENCYSUBUNIT),
        SDLK_DATA_KP_LEFTPAREN = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_LEFTPAREN),
        SDLK_DATA_KP_RIGHTPAREN = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_RIGHTPAREN),
        SDLK_DATA_KP_LEFTBRACE = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_LEFTBRACE),
        SDLK_DATA_KP_RIGHTBRACE = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_RIGHTBRACE),
        SDLK_DATA_KP_TAB = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_TAB),
        SDLK_DATA_KP_BACKSPACE = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_BACKSPACE),
        SDLK_DATA_KP_A = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_A),
        SDLK_DATA_KP_B = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_B),
        SDLK_DATA_KP_C = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_C),
        SDLK_DATA_KP_D = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_D),
        SDLK_DATA_KP_E = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_E),
        SDLK_DATA_KP_F = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_F),
        SDLK_DATA_KP_XOR = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_XOR),
        SDLK_DATA_KP_POWER = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_POWER),
        SDLK_DATA_KP_PERCENT = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_PERCENT),
        SDLK_DATA_KP_LESS = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_LESS),
        SDLK_DATA_KP_GREATER = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_GREATER),
        SDLK_DATA_KP_AMPERSAND = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_AMPERSAND),
        SDLK_DATA_KP_DBLAMPERSAND =
        SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_DBLAMPERSAND),
        SDLK_DATA_KP_VERTICALBAR =
        SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_VERTICALBAR),
        SDLK_DATA_KP_DBLVERTICALBAR =
        SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_DBLVERTICALBAR),
        SDLK_DATA_KP_COLON = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_COLON),
        SDLK_DATA_KP_HASH = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_HASH),
        SDLK_DATA_KP_SPACE = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_SPACE),
        SDLK_DATA_KP_AT = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_AT),
        SDLK_DATA_KP_EXCLAM = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_EXCLAM),
        SDLK_DATA_KP_MEMSTORE = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMSTORE),
        SDLK_DATA_KP_MEMRECALL = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMRECALL),
        SDLK_DATA_KP_MEMCLEAR = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMCLEAR),
        SDLK_DATA_KP_MEMADD = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMADD),
        SDLK_DATA_KP_MEMSUBTRACT =
        SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMSUBTRACT),
        SDLK_DATA_KP_MEMMULTIPLY =
        SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMMULTIPLY),
        SDLK_DATA_KP_MEMDIVIDE = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMDIVIDE),
        SDLK_DATA_KP_PLUSMINUS = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_PLUSMINUS),
        SDLK_DATA_KP_CLEAR = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_CLEAR),
        SDLK_DATA_KP_CLEARENTRY = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_CLEARENTRY),
        SDLK_DATA_KP_BINARY = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_BINARY),
        SDLK_DATA_KP_OCTAL = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_OCTAL),
        SDLK_DATA_KP_DECIMAL = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_DECIMAL),
        SDLK_DATA_KP_HEXADECIMAL =
        SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_HEXADECIMAL),

        SDLK_DATA_LCTRL = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LCTRL),
        SDLK_DATA_LSHIFT = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LSHIFT),
        SDLK_DATA_LALT = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LALT),
        SDLK_DATA_LGUI = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LGUI),
        SDLK_DATA_RCTRL = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RCTRL),
        SDLK_DATA_RSHIFT = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RSHIFT),
        SDLK_DATA_RALT = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RALT),
        SDLK_DATA_RGUI = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RGUI),

        SDLK_DATA_MODE = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MODE),

        SDLK_DATA_AUDIONEXT = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIONEXT),
        SDLK_DATA_AUDIOPREV = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIOPREV),
        SDLK_DATA_AUDIOSTOP = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIOSTOP),
        SDLK_DATA_AUDIOPLAY = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIOPLAY),
        SDLK_DATA_AUDIOMUTE = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIOMUTE),
        SDLK_DATA_MEDIASELECT = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MEDIASELECT),
        SDLK_DATA_WWW = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_WWW),
        SDLK_DATA_MAIL = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MAIL),
        SDLK_DATA_CALCULATOR = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CALCULATOR),
        SDLK_DATA_COMPUTER = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_COMPUTER),
        SDLK_DATA_AC_SEARCH = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_SEARCH),
        SDLK_DATA_AC_HOME = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_HOME),
        SDLK_DATA_AC_BACK = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_BACK),
        SDLK_DATA_AC_FORWARD = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_FORWARD),
        SDLK_DATA_AC_STOP = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_STOP),
        SDLK_DATA_AC_REFRESH = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_REFRESH),
        SDLK_DATA_AC_BOOKMARKS = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_BOOKMARKS),

        SDLK_DATA_BRIGHTNESSDOWN =
        SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_BRIGHTNESSDOWN),
        SDLK_DATA_BRIGHTNESSUP = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_BRIGHTNESSUP),
        SDLK_DATA_DISPLAYSWITCH = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_DISPLAYSWITCH),
        SDLK_DATA_KBDILLUMTOGGLE =
        SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KBDILLUMTOGGLE),
        SDLK_DATA_KBDILLUMDOWN = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KBDILLUMDOWN),
        SDLK_DATA_KBDILLUMUP = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KBDILLUMUP),
        SDLK_DATA_EJECT = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_EJECT),
        SDLK_DATA_SLEEP = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SLEEP),
        SDLK_DATA_APP1 = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_APP1),
        SDLK_DATA_APP2 = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_APP2),

        SDLK_DATA_AUDIOREWIND = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIOREWIND),
        SDLK_DATA_AUDIOFASTFORWARD = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIOFASTFORWARD),

        SDLK_DATA_SOFTLEFT = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SOFTLEFT),
        SDLK_DATA_SOFTRIGHT = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SOFTRIGHT),
        SDLK_DATA_CALL = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CALL),
        SDLK_DATA_ENDCALL = SDL_DATA_SCANCODE_TO_KEYCODE(SDL_SCANCODE_ENDCALL)
    };

    /**
     * \brief Enumeration of valid key mods (possibly OR'd together).
     */
    enum SdlModuleKeymod : uint16_t
    {
        KMOD_DATA_NONE = 0x0000,
        KMOD_DATA_LSHIFT = 0x0001,
        KMOD_DATA_RSHIFT = 0x0002,
        KMOD_DATA_LCTRL = 0x0040,
        KMOD_DATA_RCTRL = 0x0080,
        KMOD_DATA_LALT = 0x0100,
        KMOD_DATA_RALT = 0x0200,
        KMOD_DATA_LGUI = 0x0400,
        KMOD_DATA_RGUI = 0x0800,
        KMOD_DATA_NUM = 0x1000,
        KMOD_DATA_CAPS = 0x2000,
        KMOD_DATA_MODE = 0x4000,
        KMOD_DATA_SCROLL = 0x8000,

        KMOD_DATA_CTRL = KMOD_DATA_LCTRL | KMOD_DATA_RCTRL,
        KMOD_DATA_SHIFT = KMOD_DATA_LSHIFT | KMOD_DATA_RSHIFT,
        KMOD_DATA_ALT = KMOD_DATA_LALT | KMOD_DATA_RALT,
        KMOD_DATA_GUI = KMOD_DATA_LGUI | KMOD_DATA_RGUI,

        KMOD_DATA_RESERVED = KMOD_DATA_SCROLL /* This is for source-level compatibility with SDL 2.0.0. */
    };

    struct SdlKeysymData
    {
        SdlScancode scancode;      /**< SDL physical key code - see ::SDL_Scancode for details */
        SdlKeycode sym;            /**< SDL virtual key code - see ::SDL_Keycode for details */
        uint16_t mod;                 /**< current key modifiers */
        uint16_t padding;
        uint32_t unused;

        SdlKeysymData(const SDL_Keysym& keyData);
        ~SdlKeysymData();
    };

    struct SdlKeyboardEventData
    {
        uint32_t timestamp;   /**< In milliseconds, populated using SDL_GetTicks() */
        uint32_t windowID;    /**< The window with keyboard focus, if any */
        uint8_t state;        /**< 1 if pressed or 0 if released */
        uint8_t repeat;       /**< Non-zero if this is a key repeat */
        uint8_t padding2;
        uint8_t padding3;
        uint32_t padding;
        SdlKeysymData keysym;  /**< The key that was pressed or released */

        SdlKeyboardEventData(const SDL_KeyboardEvent& eventData);
        ~SdlKeyboardEventData();
    };

    struct SdlKeymapChangedEventData
    {
        uint32_t timestamp;   /**< In milliseconds, populated using SDL_GetTicks() */

        SdlKeymapChangedEventData(const SDL_CommonEvent& eventData);
        ~SdlKeymapChangedEventData();
    };
}