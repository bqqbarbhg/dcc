#include <dcc/platform.h>
#if DCC_PLATFORM == DCC_PLATFORM_WINDOWS

#ifndef _DCC_OUT_WINDOWS_CONSOLE_H
#define _DCC_OUT_WINDOWS_CONSOLE_H

#include <Windows.h>

#include <dcc/out/output.h>

namespace dcc { namespace out {

// Windows console API highlighting
class WindowsConsole : public Output
{
public:
	WindowsConsole();
	virtual ~WindowsConsole();
	virtual void set_type(TextType type);
	virtual void write_string(const char * s);
	virtual void write(const char *s, unsigned int n);
	virtual void flush();

private:
	HANDLE handle;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
};

} }

#endif
#endif