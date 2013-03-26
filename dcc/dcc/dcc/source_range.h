#ifndef _DCC_SOURCE_RANGE_H
#define _DCC_SOURCE_RANGE_H

#include <string>
#include <dcc/file.h>

namespace dcc {

// A range of characters in a source file
// Defined as [begin, end) in file
class SourceRange
{
	// File where the range is in
	File *file;

	// First character in the range (inclusive)
	src_charpos_t begin;

	// Last character in the range (exclusive)
	src_charpos_t end;
};

}

#endif