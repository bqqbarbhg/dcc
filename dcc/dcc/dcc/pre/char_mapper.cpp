#include "char_mapper.h"

#include <dcc/settings.h>

namespace dcc { namespace pre {

CharMapper::CharMapper(io::FileReader& in)
	: ls_has_unget(false)
	, in(in)
	, unget_end(unget_buffer + sizeof(unget_buffer) / sizeof(*unget_buffer))
	, unget_ptr(unget_end)
{
}

char CharMapper::charmap()
{
	if (unget_ptr != unget_end)
		return *unget_ptr++;
	char c;
	while ((c = in.get()) == '\r')
		;
	return c;
}

void CharMapper::unget(char c)
{
	*--unget_ptr = c;
}

char CharMapper::trigraph()
{
	if (settings.trigraph) {
		char c = charmap();
		if (c == '?') {
			c = charmap();
			if (c == '?') {
				c = charmap();
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
				unget(c);
				unget('?');
			} else {
				unget(c);
			}
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