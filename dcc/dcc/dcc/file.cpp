
#include "file.h"

namespace dcc {

File::File(const std::string& path)
	: name(path)
{
}

std::map<src_charpos_t, src_line_t>::const_iterator File::get_line(src_charpos_t i) const
{
	return --line_changes.upper_bound(i);
}

std::ifstream File::open() const
{
	return std::ifstream(name, std::ios::binary);
}

}