#ifndef _DCC_PRE_SCANNER_H
#define _DCC_PRE_SCANNER_H

#include <fstream>
#include <dcc/file.h>

namespace dcc { namespace pre {

class Scanner
{
public:
	Scanner(File& file);

	// Reads a sinlge character from the file
	// Updates the files newline indices
	// Returns 0 on EOF
	char get();

private:
	src_charpos_t charpos;
	src_line_t linenum;
	File& file;
	std::ifstream in;
};

} }

#endif