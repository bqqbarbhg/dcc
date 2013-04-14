#include "clang_console.h"

#include <iostream>
#include <dcc/unicode.h>

namespace dcc { namespace out {

ClangConsole::~ClangConsole()
{
	flush();
}
void ClangConsole::set_type(TextType type)
{
	if (under.empty() && !line.empty())
		under = std::string(line.length(), ' ');
	mode = type;
}
void ClangConsole::write(const char *s, unsigned int n)
{
	const char *e = s + n;
	line.reserve(n);
	for (; s != e; s++) {
		if (*s == '\n') {
			flush();
			std::cout << std::endl;
		} else {
			line += *s;
			if ((mode != NORMAL || !under.empty()) && !is_utf8_continuation_byte(*s)) {
				switch (mode) {
				case NORMAL: under += ' '; break;
				case MEDIUM: under += '~'; break;
				case IMPORTANT: under += '^'; break;
				}
			}
		}
	}
}
void ClangConsole::flush()
{
	if (!line.empty())
		output.write(&line[0], line.length());
	if (!under.empty())
	{
		output.write("\n", 1);
		output.write(&under[0], under.length());
	}
	line.clear(); under.clear();
}

} }