#ifndef _DCC_SOURCE_RANGE_H
#define _DCC_SOURCE_RANGE_H

#include <iosfwd>
#include <string>
#include <dcc/file.h>
#include <dcc/out/console.h>

namespace dcc {

// A range of characters in a source file
// Defined as [begin, end) in file
class SourceRange
{
public:
	SourceRange() : file(nullptr) { }
	SourceRange(const File *f, src_charpos_t b, src_charpos_t e);

	// File where the range is in
	// Must outlive this range
	const dcc::File *file;

	// First character in the range (inclusive)
	src_charpos_t begin;

	// Last character in the range (exclusive)
	src_charpos_t end;

	// Prints the short form of the range ie. 'file:row:col'
	void print(out::Console& out) const;

	// Prints the long form of the range (if enabled) eg.
	// int main(int argc, char** argv)
	//                    ^^^^^^
	void print_long(out::Console& out) const;

	// Prints the long form of the range with a inner subrange (if enabled) eg.
	// int main(int argc, char** argv)
	//                    ~~~~^^
	void print_long(out::Console& out, const SourceRange& inner) const;
};

}

#endif