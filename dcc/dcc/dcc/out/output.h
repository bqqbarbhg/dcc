#ifndef _DCC_OUT_OUTPUT_H
#define _DCC_OUT_OUTPUT_H

#include <string>

namespace dcc { namespace out {

enum TextType
{
	NORMAL,
	MEDIUM,
	IMPORTANT,
};

class Output
{
public:
	virtual ~Output() { }
	virtual void flush() = 0;
	virtual void set_type(TextType type) = 0;
	virtual void write_string(const char* s) = 0;
	virtual void write(const char* s, unsigned int n) = 0;
	void write_string(const std::string& s) { write(&s[0], s.length()); }

	Output& operator<<(const char *s);
	Output& operator<<(const std::string& s);
	Output& operator<<(TextType text);
	Output& operator<<(unsigned long l);
	Output& operator<<(long l);
};

} }

#endif