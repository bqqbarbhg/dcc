#ifndef _DCC_OUT_CLANG_CONSOLE_H
#define _DCC_OUT_CLANG_CONSOLE_H

#include <dcc/out/console.h>

namespace dcc { namespace out {

// A Clang error diagnostics type console with ascii underlining
class ClangConsole : public Console
{
public:
	ClangConsole(Output& out)
		: Console(out) { }
	~ClangConsole();
	virtual void set_type(TextType type);
	virtual void write(const char *s, unsigned int n);
	void flush();
private:
	std::string line, under;
	TextType mode;
};

} }

#endif