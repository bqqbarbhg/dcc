#ifndef _DCC_FILE_H
#define _DCC_FILE_H

#include <fstream>
#include <string>
#include <map>

namespace dcc {

// Type that can represent indices of all the characters of a file
typedef unsigned long src_charpos_t;

// Type that can represent all the line numbers of a file
typedef unsigned long src_line_t;

// A File instance in the compilation process
// Must outlive all `SourceRange`s that refer to it
class File
{
public:
	File(const std::string& path);

	// The full name of the file (including path)
	std::string name;

	// Character indices where the line changes are
	std::map<src_charpos_t, src_line_t> line_changes;

	// Returns { Index of last newline character, Line number }
	// Column can be calculated as `i - return->first`
	std::map<src_charpos_t, src_line_t>::const_iterator get_line(src_charpos_t i) const;

	// Opens the file for reading
	std::ifstream open() const;
};

}

#endif