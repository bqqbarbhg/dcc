#ifndef _DCC_IO_H
#define _DCC_IO_H

#include <vector>
#include <string>
#include <dcc/file.h>

namespace dcc { namespace io {

// Replaces tabs with spaces
void detab(const std::string& str, std::ostream& o);

// Replaces tabs with spaces and scales column numbers
// cols must be a sorted vector of column numbers
void detab(const std::string& str, std::ostream& o, std::vector<src_charpos_t>& cols);

} }

#endif