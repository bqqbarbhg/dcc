#include "plain_console.h"

#include <iostream>

namespace dcc { namespace out {

void PlainConsole::write_string(const char * s)
{
	std::cout << s;
}
void PlainConsole::write(const char *s, unsigned int n)
{
	std::cout.write(s, n);
}

} }