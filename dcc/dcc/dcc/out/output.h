#ifndef _DCC_OUT_OUTPUT_H
#define _DCC_OUT_OUTPUT_H

#include <string>

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

class Output
{
public:
	virtual ~Output() { }

	// Flush the output stream
	virtual void flush() = 0;

	// Set the text highlighting type
	virtual void set_type(TextType type) = 0;

	// Write a string to the output
	virtual void write_string(const char* s) = 0;

	// Write `n` characters of `s` to the output
	virtual void write(const char* s, unsigned int n) = 0;

	// Write a C++ string to the output
	void write_string(const std::string& s) { write(&s[0], s.length()); }

	Output& operator<<(const char *s);
	Output& operator<<(const std::string& s);
	Output& operator<<(TextType text);
	Output& operator<<(unsigned long l);
	Output& operator<<(long l);
};

} }

#endif