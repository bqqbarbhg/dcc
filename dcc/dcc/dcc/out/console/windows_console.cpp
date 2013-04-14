#include "windows_console.h"
#if DCC_PLATFORM == DCC_PLATFORM_WINDOWS

#include <iostream>

namespace dcc { namespace out {

WindowsConsole::WindowsConsole(Output& out)
	: Console(out)
{
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(handle, &csbi);
	set_type(NORMAL);
}

void WindowsConsole::set_type(TextType type)
{
	switch (type)
	{
	case NORMAL:
		SetConsoleTextAttribute(handle, csbi.wAttributes);
		break;
	case MEDIUM:
		SetConsoleTextAttribute(handle, csbi.wAttributes ^ BACKGROUND_INTENSITY ^ FOREGROUND_INTENSITY);
		break;
	case IMPORTANT:
		SetConsoleTextAttribute(handle, csbi.wAttributes >> 4 & 0x0F | csbi.wAttributes << 4 & 0xF0);
		break;
	}
}

} }

#endif