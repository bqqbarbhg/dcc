#ifndef _DCC_FILE_H
#define _DCC_FILE_H

#include <string>
#include <set>

namespace dcc {

// Type that can represent indices of all the characters of a file
typedef unsigned long src_charpos_t;

// A File instance in the compilation process
// Must outlive all `SourceRange`s that refer to it
class File
{
public:
	// The full name of the file (including path)
	std::string name;

	// Character indices where the line changes are
	std::set<src_charpos_t> line_changes;
};

}

#endif