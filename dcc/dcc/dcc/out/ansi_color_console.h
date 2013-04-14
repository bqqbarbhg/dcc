#ifndef _DCC_OUT_ANSI_COLOR_CONSOLE_H
#define _DCC_OUT_ANSI_COLOR_CONSOLE_H

#include <dcc/out/output.h>

namespace dcc { namespace out {

// ANSI color codes
// Doesn't work on windows terminal
class AnsiColorConsole : public Output
{
public:
	virtual void set_type(TextType type);
	virtual void write_string(const char * s);
	virtual void write(const char *s, unsigned int n);
	virtual void flush() { }
};

} }

#endif