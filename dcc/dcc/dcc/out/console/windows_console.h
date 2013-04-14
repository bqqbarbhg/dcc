#include <dcc/platform.h>
#if DCC_PLATFORM == DCC_PLATFORM_WINDOWS

#ifndef _DCC_OUT_WINDOWS_CONSOLE_H
#define _DCC_OUT_WINDOWS_CONSOLE_H

#include <Windows.h>

#include <dcc/out/console.h>

namespace dcc { namespace out {

// Windows console API highlighting
class WindowsConsole : public Console
{
public:
	WindowsConsole(Output& out);
	virtual void set_type(TextType type);

private:
	HANDLE handle;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
};

} }

#endif
#endif