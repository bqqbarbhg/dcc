#ifndef _DCC_PRE_CHAR_MAP_H
#define _DCC_PRE_CHAR_MAP_H

#include <dcc/io/file_reader.h>

namespace dcc { namespace pre {

// Processes translation phases 1 and 2 ($2.1.1.2)
class CharMapper
{
public:
	CharMapper(io::FileReader& in);

	// Reads a character from the file and applies trigraph replacement and
	// removes newlines followed by backslashes
	char get();

private:
	char charmap();
	char trigraph();
	char linesplice();
	void unget(char c);

	bool ls_has_unget;
	char ls_unget;

	char unget_buffer[3], *unget_end, *unget_ptr;

	io::FileReader& in;
};

} }

#endif