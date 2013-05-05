#include "except.h"

namespace dcc {

void SimpleSourceException::print(out::Console& out) const
{
	range.print_long(out);
	out.write_string("\n");
	out.write_string(message);
}

void UnexpectedCharException::print(out::Console& out) const
{
	range.print_long(out);
	out << "\nUnexpected character '" << ch << "'";
}

}