#include "ansi_color_console.h"

#include <iostream>

namespace dcc { namespace out {

void AnsiColorConsole::set_type(TextType type)
{
	switch (type) {
	case NORMAL:
		write_string("\033[0m");
		break;
	case MEDIUM:
		write_string("\033[0;4m");
		break;
	case IMPORTANT:
		write_string("\033[0;4;7m");
		break;
	}
}

} }