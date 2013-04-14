#include "windows_output.h"

namespace dcc { namespace out {

WindowsOutput::WindowsOutput()
{
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCP(CP_UTF8);
}

void WindowsOutput::write(const char* str, unsigned int n)
{
	WriteConsoleA(handle, str, n, NULL, NULL);
}

} }