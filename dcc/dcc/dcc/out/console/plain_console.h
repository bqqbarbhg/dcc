#ifndef _DCC_OUT_PLAIN_CONSOLE_H
#define _DCC_OUT_PLAIN_CONSOLE_H

#include <dcc/out/console.h>

namespace dcc { namespace out {

// Plain console with no text highlighting
class PlainConsole : public Console
{
public:
	PlainConsole(Output& out)
		: Console(out) { }
	virtual void set_type(TextType type) { }
};

} }

#endif