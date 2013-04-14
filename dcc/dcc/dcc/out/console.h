#ifndef _DCC_OUT_CONSOLE_H
#define _DCC_OUT_CONSOLE_H

#include <string>
#include <dcc/out/output.h>

namespace dcc { namespace out {

// Text highlighting type
enum TextType
{
	// Default
	NORMAL,
	// Error context eg. a + b
	//                   ~~ ~~
	MEDIUM,
	// Error token eg. a + b
	//                   ^
	IMPORTANT,
};

class Console
{
public:
	Console(Output& out)
		: output(out) { }
	virtual ~Console() { }

	// Set the text highlighting type
	virtual void set_type(TextType type) = 0;

	// Write a string to the output
	virtual void write_string(const char* s);

	// Write `n` characters of `s` to the output
	virtual void write(const char* s, unsigned int n);

	// Write a C++ string to the output
	void write_string(const std::string& s) { write(&s[0], s.length()); }

	Console& operator<<(const char *s);
	Console& operator<<(const std::string& s);
	Console& operator<<(TextType text);
	Console& operator<<(unsigned long l);
	Console& operator<<(long l);

	Output& output;
};

} }

#endif