#ifndef _DCC_OUT_PLAIN_CONSOLE_H
#define _DCC_OUT_PLAIN_CONSOLE_H

#include <dcc/out/output.h>

namespace dcc { namespace out {

// Plain console with no text highlighting
class PlainConsole : public Output
{
public:
	virtual void set_type(TextType type) { }
	virtual void write_string(const char * s);
	virtual void write(const char *s, unsigned int n);
	virtual void flush() { }
};

} }

#endif