#pragma once

namespace Vge
{
	class VGE_API Event
	{
	public:
	};

	class VGE_API MouseEvent
	{
	public:
		enum ButtonState
		{
			BS_LeftDown,
			BS_RightDown,
			BS_LeftDBDown,
			BS_RightDBDown,
			BS_MidDown,
			BS_MidDBDown,
			BS_LeftUp,
			BS_RightUp,
			BS_LeftDBUp,
			BS_RightDBUp,
			BS_MidUp,
			BS_MidDBUp,
			BS_MidDelta
		};

		ButtonState mState;
		int mX, mY;
		float mDeltaX, mDeltaY;
		float mMidDelta;

		MouseEvent(ButtonState state, int x, int y, float middelta = 0.0f,
					float deltax = 0.0f, float deltay = 0.0f)
			: mState(state)
			, mX(x)
			, mY(y)
			, mMidDelta(middelta)
			, mDeltaX(deltax)
			, mDeltaY(deltay)
		{
		}

	};

	class VGE_API KeyboardEvent
	{
	public:
		char mKeyCode;
		char mCtrl : 1;
		char mAlt : 1;
		char mShift : 1;

		KeyboardEvent(char keycode, bool ctrl = false, bool alt = false, bool shift = false)
			: mKeyCode(keycode), mCtrl(ctrl), mAlt(alt), mShift(shift)
		{
		}
	};

/*
** VGE Virtual-key codes
*/
#define VGEK_LBUTTON	0x01
#define VGEK_RBUTTON	0x02
#define VGEK_MBUTTON	0x04

#define VGEK_ESCAPE		0x1B
#define VGEK_BACKSPACE	0x08
#define VGEK_TAB		0x09
#define VGEK_ENTER		0x0D
#define VGEK_SPACE		0x20

#define VGEK_SHIFT		0x10
#define VGEK_CTRL		0x11
#define VGEK_ALT		0x12

#define VGEK_LWIN		0x5B
#define VGEK_RWIN		0x5C
#define VGEK_APPS		0x5D

#define VGEK_PAUSE		0x13
#define VGEK_CAPSLOCK	0x14
#define VGEK_NUMLOCK	0x90
#define VGEK_SCROLLLOCK	0x91

#define VGEK_PGUP		0x21
#define VGEK_PGDN		0x22
#define VGEK_HOME		0x24
#define VGEK_END		0x23
#define VGEK_INSERT		0x2D
#define VGEK_DELETE		0x2E

#define VGEK_LEFT		0x25
#define VGEK_UP			0x26
#define VGEK_RIGHT		0x27
#define VGEK_DOWN		0x28

#define VGEK_0			0x30
#define VGEK_1			0x31
#define VGEK_2			0x32
#define VGEK_3			0x33
#define VGEK_4			0x34
#define VGEK_5			0x35
#define VGEK_6			0x36
#define VGEK_7			0x37
#define VGEK_8			0x38
#define VGEK_9			0x39

#define VGEK_A			0x41
#define VGEK_B			0x42
#define VGEK_C			0x43
#define VGEK_D			0x44
#define VGEK_E			0x45
#define VGEK_F			0x46
#define VGEK_G			0x47
#define VGEK_H			0x48
#define VGEK_I			0x49
#define VGEK_J			0x4A
#define VGEK_K			0x4B
#define VGEK_L			0x4C
#define VGEK_M			0x4D
#define VGEK_N			0x4E
#define VGEK_O			0x4F
#define VGEK_P			0x50
#define VGEK_Q			0x51
#define VGEK_R			0x52
#define VGEK_S			0x53
#define VGEK_T			0x54
#define VGEK_U			0x55
#define VGEK_V			0x56
#define VGEK_W			0x57
#define VGEK_X			0x58
#define VGEK_Y			0x59
#define VGEK_Z			0x5A

#define VGEK_GRAVE		0xC0
#define VGEK_MINUS		0xBD
#define VGEK_EQUALS		0xBB
#define VGEK_BACKSLASH	0xDC
#define VGEK_LBRACKET	0xDB
#define VGEK_RBRACKET	0xDD
#define VGEK_SEMICOLON	0xBA
#define VGEK_APOSTROPHE	0xDE
#define VGEK_COMMA		0xBC
#define VGEK_PERIOD		0xBE
#define VGEK_SLASH		0xBF

#define VGEK_NUMPAD0	0x60
#define VGEK_NUMPAD1	0x61
#define VGEK_NUMPAD2	0x62
#define VGEK_NUMPAD3	0x63
#define VGEK_NUMPAD4	0x64
#define VGEK_NUMPAD5	0x65
#define VGEK_NUMPAD6	0x66
#define VGEK_NUMPAD7	0x67
#define VGEK_NUMPAD8	0x68
#define VGEK_NUMPAD9	0x69

#define VGEK_MULTIPLY	0x6A
#define VGEK_DIVIDE		0x6F
#define VGEK_ADD		0x6B
#define VGEK_SUBTRACT	0x6D
#define VGEK_DECIMAL	0x6E

#define VGEK_F1			0x70
#define VGEK_F2			0x71
#define VGEK_F3			0x72
#define VGEK_F4			0x73
#define VGEK_F5			0x74
#define VGEK_F6			0x75
#define VGEK_F7			0x76
#define VGEK_F8			0x77
#define VGEK_F9			0x78
#define VGEK_F10		0x79
#define VGEK_F11		0x7A
#define VGEK_F12		0x7B

}