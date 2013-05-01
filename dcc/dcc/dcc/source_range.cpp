#include "source_range.h"

#include <iostream>
#include <sstream>
#include <algorithm>
#include <dcc/io.h>
#include <dcc/assert.h>

namespace dcc {

SourceRange::SourceRange(const File *f, src_charpos_t b, src_charpos_t e)
	: file(f), begin(b), end(e)
{
}

void SourceRange::print(out::Console& o) const
{
	DCC_ASSERT(file != nullptr);

	auto p = file->get_line(begin);
	auto q = file->get_line(end);
	o << file->name << ": (" << p->second << ":" << begin - p->first << " - " << q->second << ":" << end - q->first << ")";
}

void SourceRange::print_long(out::Console& o) const
{
	DCC_ASSERT(file != nullptr);

	auto beginline = file->get_line(begin);
	auto endline = file->get_line(end);
	auto in = file->open();

	auto nextline = std::next(endline);
	src_charpos_t len = nextline->first - beginline->first;
		
	// Read the relevant line
	std::string str; str.resize(len);
	in.seekg(beginline->first, std::ios::beg);
	in.read(&str[0], len);

	// Store the begin and end columns
	std::vector<src_charpos_t> cols;
	cols.push_back(begin - beginline->first);
	cols.push_back(end - beginline->first);

	// Detab and print the line
	std::ostringstream oss;
	io::detab(str, oss, cols);
	std::string st = oss.str();
		
	o.write(&st[0], cols[0]);
	o.set_type(out::IMPORTANT);
	o.write(&st[cols[0]], cols[1] - cols[0]);
	o.set_type(out::NORMAL);
	o.write_string(&st[cols[1]]);
}

void SourceRange::print_long(out::Console& o, const SourceRange& inner) const
{
	DCC_ASSERT(file != nullptr);

	auto beginline = file->get_line(begin);
	auto endline = file->get_line(end);
	auto in = file->open();

	auto nextline = std::next(endline);
	src_charpos_t len = nextline->first - beginline->first;
		
	// Read the relevant line
	std::string str; str.resize(len);
	in.seekg(beginline->first, std::ios::beg);
	in.read(&str[0], len);

	// Store the begin and end columns
	std::vector<src_charpos_t> cols;
	cols.push_back(begin - beginline->first);
	cols.push_back(inner.begin - beginline->first);
	cols.push_back(inner.end - beginline->first);
	cols.push_back(end - beginline->first);

	// Detab and print the line
	std::ostringstream oss;
	io::detab(str, oss, cols);
	std::string st = oss.str();
		
	o.write(&st[0], cols[0]);
	o.set_type(out::MEDIUM);
	o.write(&st[cols[0]], cols[1] - cols[0]);
	o.set_type(out::IMPORTANT);
	o.write(&st[cols[1]], cols[2] - cols[1]);
	o.set_type(out::MEDIUM);
	o.write(&st[cols[2]], cols[3] - cols[2]);
	o.set_type(out::NORMAL);
	o.write_string(&st[cols[3]]);
}

}