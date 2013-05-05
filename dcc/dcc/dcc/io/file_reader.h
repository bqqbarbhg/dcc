#ifndef _DCC_IO_FILE_READER_H
#define _DCC_IO_FILE_READER_H

#include <fstream>
#include <dcc/file.h>

namespace dcc { namespace io {

class FileReader
{
public:
	FileReader(FileReader&& reader);

	FileReader(File& file);

	// Reads a sinlge character from the file
	// Updates the files newline indices
	// Returns 0 on EOF
	char get();

	// Returns one read character back to the stream
	// Next call to `get` returns the last `get` result
	void unget();

	// Returns the index of the current character in the file
	src_charpos_t get_char_index() const { return charpos; }

private:
	File& file;
	std::ifstream in;
	src_charpos_t charpos, real_charpos;
	src_line_t linenum;
	std::string line;
	std::string::iterator line_it;
};

} }

#endif