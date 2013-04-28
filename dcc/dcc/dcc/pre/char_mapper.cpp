#include "char_mapper.h"

#include <dcc/settings.h>

namespace dcc { namespace pre {

CharMapper::CharMapper(io::FileReader& in)
	: ls_has_unget(false), in(in)
{
}

char CharMapper::trigraph()
{
	if (settings.trigraph) {
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
	} else {
		return in.get();
	}
}

char CharMapper::linesplice()
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

char CharMapper::get()
{
	return linesplice();
}

} }