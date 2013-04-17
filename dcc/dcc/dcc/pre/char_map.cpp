#include "char_map.h"

namespace dcc { namespace pre {

CharMap::CharMap(io::FileReader& in)
	: ls_has_unget(false), in(in)
{
}

char CharMap::trigraph()
{
	char c = in.get();
	if (c == '?') {
		c = in.get();
		if (c == '?') {
			c = in.get();
			switch (c) {
			case '=': return '#';
			case '/': return '\\';
			case '(': return '[';
			case ')': return ']';
			case '\'': return '^';
			case '!': return '|';
			case '<': return '{';
			case '>': return '}';
			case '-': return '~';
			}
			in.unget();
		}
		in.unget();
		return '?';
	} else {
		return c;
	}
}

char CharMap::linesplice()
{
	if (ls_has_unget) {
		ls_has_unget = false;
		return ls_unget;
	}
	while (true) {
		char c = trigraph();
		if (c == '\\') {
			c = trigraph();
			if (c != '\n') {
				ls_has_unget = true;
				ls_unget = c;
				return '\\';
			}
		} else {
			return c;
		}
	}
}

char CharMap::get()
{
	return linesplice();
}

} }