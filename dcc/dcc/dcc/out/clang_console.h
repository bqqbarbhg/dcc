#ifndef _DCC_OUT_CLANG_CONSOLE_H
#define _DCC_OUT_CLANG_CONSOLE_H

#include <dcc/out/output.h>

namespace dcc { namespace out {

class ClangConsole : public Output
{
public:
	~ClangConsole();
	virtual void set_type(TextType type);
	virtual void write_string(const char * s);
	virtual void write(const char *s, unsigned int n);
	virtual void flush();
private:
	std::string line, under;
	TextType mode;
};

} }

#endif