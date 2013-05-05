#include "console.h"
#include <sstream>

namespace dcc { namespace out {

template <typename T>
Console& write_any(Console& o, T t)
{
	std::ostringstream oss;
	oss << t;
	o.write_string(oss.str());
	return o;
}

void Console::write_string(const char* s)
{
	write(s, strlen(s));
}

void Console::write(const char* s, unsigned int n)
{
	output.write(s, n);
}

Console& Console::operator<<(const char *s)
{
	write_string(s);
	return *this;
}
Console& Console::operator<<(const std::string& s)
{
	write_string(s);
	return *this;
}
Console& Console::operator<<(TextType text)
{
	set_type(text);
	return *this;
}
Console& Console::operator<<(unsigned long l)
{
	return write_any(*this, l);
}
Console& Console::operator<<(long l)
{
	return write_any(*this, l);
}
Console& Console::operator<<(char c)
{
	return write_any(*this, c);
}

} }