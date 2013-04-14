#include "clang_console.h"

#include <iostream>

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
void ClangConsole::write_string(const char * s)
{
	write(s, strlen(s));
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
			if (mode != NORMAL || !under.empty()) {
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
		std::cout << line;
	if (!under.empty())
		std::cout << std::endl << under;
	line.clear(); under.clear();
}

} }