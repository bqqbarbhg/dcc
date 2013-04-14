#include "ansi_color_console.h"

#include <iostream>

namespace dcc { namespace out {

void AnsiColorConsole::set_type(TextType type)
{
	switch (type) {
	case NORMAL:
		std::cout << "\033[0m";
		break;
	case MEDIUM:
		std::cout << "\033[0;4m";
		break;
	case IMPORTANT:
		std::cout << "\033[0;4;7m";
		break;
	}
}
void AnsiColorConsole::write_string(const char * s)
{
	std::cout << s;
}
void AnsiColorConsole::write(const char *s, unsigned int n)
{
	std::cout.write(s, n);
}

} }