#ifndef _DCC_PRE_CHAR_MAP_H
#define _DCC_PRE_CHAR_MAP_H

#include <dcc/io/file_reader.h>

namespace dcc { namespace pre {

// Processes translation phases 1 and 2 ($2.1.1.2)
class CharMap
{
public:
	CharMap(io::FileReader& in);

	// Reads a character from the file and applies trigraph replacement and
	// removes newlines followed by backslashes
	char get();

private:
	char trigraph();
	char linesplice();

	bool ls_has_unget;
	char ls_unget;

	io::FileReader& in;
};

} }

#endif