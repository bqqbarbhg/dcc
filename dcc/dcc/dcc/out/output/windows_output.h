#include <dcc/platform.h>
#if DCC_PLATFORM == DCC_PLATFORM_WINDOWS
#include <Windows.h>

#ifndef _DCC_OUT_WINDOWS_OUTPUT_H
#define _DCC_OUT_WINDOWS_OUTPUT_H

#include <dcc/out/output.h>

namespace dcc { namespace out {

class WindowsOutput : public Output {
public:
	WindowsOutput();
	virtual void write(const char* str, unsigned int n);
private:
	HANDLE handle;
};

} }

#endif
#endif