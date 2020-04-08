#pragma once

#ifdef LS_PLATFORM_WIN32

#define LS_MOUSE_LEFT	  0x00
#define LS_MOUSE_MIDDLE	  0x01
#define LS_MOUSE_RIGHT    0x02

#define LS_NO_CURSOR	  NULL

#define LS_MODIFIER_LEFT_CONTROL	BIT(0)
#define LS_MODIFIER_LEFT_ALT		BIT(1)
#define LS_MODIFIER_LEFT_SHIFT		BIT(2)
#define LS_MODIFIER_RIGHT_CONTROL	BIT(3)
#define LS_MODIFIER_RIGHT_ALT		BIT(4)
#define LS_MODIFIER_RIGHT_SHIFT		BIT(5)

#define LS_KEY_TAB			  0x09

#define LS_KEY_0			  0x30
#define LS_KEY_1			  0x31
#define LS_KEY_2			  0x32
#define LS_KEY_3			  0x33
#define LS_KEY_4			  0x34
#define LS_KEY_5			  0x35
#define LS_KEY_6			  0x36
#define LS_KEY_7			  0x37
#define LS_KEY_8			  0x38
#define LS_KEY_9			  0x39

#define LS_KEY_A			  0x41
#define LS_KEY_B			  0x42
#define LS_KEY_C			  0x43
#define LS_KEY_D			  0x44
#define LS_KEY_E			  0x45
#define LS_KEY_F			  0x46
#define LS_KEY_G			  0x47
#define LS_KEY_H			  0x48
#define LS_KEY_I			  0x49
#define LS_KEY_J			  0x4A
#define LS_KEY_K			  0x4B
#define LS_KEY_L			  0x4C
#define LS_KEY_M			  0x4D
#define LS_KEY_N			  0x4E
#define LS_KEY_O			  0x4F
#define LS_KEY_P			  0x50
#define LS_KEY_Q			  0x51
#define LS_KEY_R			  0x52
#define LS_KEY_S			  0x53
#define LS_KEY_T			  0x54
#define LS_KEY_U			  0x55
#define LS_KEY_V			  0x56
#define LS_KEY_W			  0x57
#define LS_KEY_X			  0x58
#define LS_KEY_Y			  0x59
#define LS_KEY_Z			  0x5A

#define LS_KEY_LBUTTON        0x01
#define LS_KEY_RBUTTON        0x02
#define LS_KEY_CANCEL         0x03
#define LS_KEY_MBUTTON        0x04

#define LS_KEY_ESCAPE         0x1B
#define LS_KEY_SHIFT          0x10
#define LS_KEY_CONTROL        0x11
#define LS_KEY_MENU           0x12
#define LS_KEY_ALT	          LS_KEY_MENU
#define LS_KEY_PAUSE          0x13
#define LS_KEY_CAPITAL        0x14

#define LS_KEY_SPACE          0x20
#define LS_KEY_PRIOR          0x21
#define LS_KEY_NEXT           0x22
#define LS_KEY_END            0x23
#define LS_KEY_HOME           0x24
#define LS_KEY_LEFT           0x25
#define LS_KEY_UP             0x26
#define LS_KEY_RIGHT          0x27
#define LS_KEY_DOWN           0x28
#define LS_KEY_SELECT         0x29
#define LS_KEY_PRINT          0x2A
#define LS_KEY_EXECUTE        0x2B
#define LS_KEY_SNAPSHOT       0x2C
#define LS_KEY_INSERT         0x2D
#define LS_KEY_DELETE         0x2E
#define LS_KEY_HELP           0x2F

#define LS_KEY_NUMPAD0        0x60
#define LS_KEY_NUMPAD1        0x61
#define LS_KEY_NUMPAD2        0x62
#define LS_KEY_NUMPAD3        0x63
#define LS_KEY_NUMPAD4        0x64
#define LS_KEY_NUMPAD5        0x65
#define LS_KEY_NUMPAD6        0x66
#define LS_KEY_NUMPAD7        0x67
#define LS_KEY_NUMPAD8        0x68
#define LS_KEY_NUMPAD9        0x69
#define LS_KEY_MULTIPLY       0x6A
#define LS_KEY_ADD            0x6B
#define LS_KEY_SEPARATOR      0x6C
#define LS_KEY_SUBTRACT       0x6D
#define LS_KEY_DECIMAL        0x6E
#define LS_KEY_DIVIDE         0x6F
#define LS_KEY_F1             0x70
#define LS_KEY_F2             0x71
#define LS_KEY_F3             0x72
#define LS_KEY_F4             0x73
#define LS_KEY_F5             0x74
#define LS_KEY_F6             0x75
#define LS_KEY_F7             0x76
#define LS_KEY_F8             0x77
#define LS_KEY_F9             0x78
#define LS_KEY_F10            0x79
#define LS_KEY_F11            0x7A
#define LS_KEY_F12            0x7B
#define LS_KEY_F13            0x7C
#define LS_KEY_F14            0x7D
#define LS_KEY_F15            0x7E
#define LS_KEY_F16            0x7F
#define LS_KEY_F17            0x80
#define LS_KEY_F18            0x81
#define LS_KEY_F19            0x82
#define LS_KEY_F20            0x83
#define LS_KEY_F21            0x84
#define LS_KEY_F22            0x85
#define LS_KEY_F23            0x86
#define LS_KEY_F24            0x87

#define LS_KEY_NUMLOCK        0x90
#define LS_KEY_SCROLL         0x91

#define LS_KEY_LSHIFT         0xA0
#define LS_KEY_RSHIFT         0xA1
#define LS_KEY_LCONTROL       0xA2
#define LS_KEY_RCONTROL       0xA3
#define LS_KEY_LMENU          0xA4
#define LS_KEY_RMENU          0xA5

#endif