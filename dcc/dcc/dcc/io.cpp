#include "io.h"

namespace dcc { namespace io {

void detab(const std::string& str, std::ostream& o)
{
	for (auto c = str.begin(); c != str.end(); ++c) {
		char cc;
		if ((cc = *c) == '\t')
			o << "    ";
		else
			o << cc;
	}
}

void detab(const std::string& str, std::ostream& o, std::vector<src_charpos_t>& cols)
{
	auto c = cols.begin(), e = cols.end();
	src_charpos_t pos = 0;
	for (auto ch = str.begin(); ch != str.end(); ++ch) {
		char cc = *ch;
		if (cc == '\t')
		{
			o << "    ", pos += 4;
			for (auto q = c; q != e; ++q)
				*q += 3;
		}	
		else if (cc != '\r')
			o << cc, pos++;
		while (c != e && pos > *c)
			c++;
	}
}

} } 