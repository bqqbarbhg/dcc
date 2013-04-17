#include "file_reader.h"

namespace dcc { namespace io {

FileReader::FileReader(File& file)
	: file(file), in(file.open()), charpos(0), linenum(0)
{
	file.line_changes[0] = 1;
}

void FileReader::unget()
{
	if (!in.eof())
		in.unget();
	charpos--;
}

char FileReader::get()
{
	charpos++;
	if (in.eof()) {
		file.line_changes[charpos] = ++linenum + 1;
		return 0;
	}

	auto i = in.get();
	
	if (i == '\n')
		file.line_changes[charpos] = ++linenum + 1;
	
	return i;
}

} }