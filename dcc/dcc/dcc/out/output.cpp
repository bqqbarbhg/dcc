#include "output.h"
#include <sstream>

namespace dcc { namespace out {

template <typename T>
Output& write_any(Output& o, T t)
{
	std::ostringstream oss;
	oss << t;
	o.write_string(oss.str());
	return o;
}

Output& Output::operator<<(const char *s)
{
	write_string(s);
	return *this;
}
Output& Output::operator<<(const std::string& s)
{
	write_string(s);
	return *this;
}
Output& Output::operator<<(TextType text)
{
	set_type(text);
	return *this;
}
Output& Output::operator<<(unsigned long l)
{
	return write_any(*this, l);
}
Output& Output::operator<<(long l)
{
	return write_any(*this, l);
}

} }