#include "file_reader.h"

namespace dcc { namespace io {

FileReader::FileReader(FileReader&& reader)
	: file(reader.file)
	, in(std::move(reader.in))
	, charpos(reader.charpos)
	, real_charpos(reader.real_charpos)
	, linenum(reader.linenum)
	, line(std::move(reader.line))
	, line_it(reader.line_it)
{
}

FileReader::FileReader(File& file)
	: file(file)
	, in(file.open())
	, charpos(0)
	, real_charpos(0)
	, linenum(0)
	, line()
	, line_it(line.begin())
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
	while (true) {
		if (line_it == line.end()) {
			if (in.eof())
				return 0;
			while (true) {
				auto i = in.get();
				real_charpos++;
				if (!in.eof())
					line += (char)i;
				if (in.eof() || i == '\n') {
					file.line_changes[real_charpos] = ++linenum + 1;
					break;
				}
			}
			line_it = line.begin();
		} else {
			charpos++;
			return *line_it++;
		}
	}
}

} }