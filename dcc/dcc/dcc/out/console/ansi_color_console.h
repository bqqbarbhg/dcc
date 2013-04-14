#ifndef _DCC_OUT_ANSI_COLOR_CONSOLE_H
#define _DCC_OUT_ANSI_COLOR_CONSOLE_H

#include <dcc/out/console.h>

namespace dcc { namespace out {

// ANSI color codes
// Doesn't work on windows terminal
class AnsiColorConsole : public Console
{
public:
	AnsiColorConsole(Output& out)
		: Console(out) { }
	virtual void set_type(TextType type);
};

} }

#endif