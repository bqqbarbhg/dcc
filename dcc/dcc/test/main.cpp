#include <iostream>
#include <fstream>
#include <dcc/file.h>
#include <dcc/io/file_reader.h>
#include <dcc/source_range.h>
#include <dcc/out/output/standard_output.h>
#include <dcc/out/console/clang_console.h>
#include <dcc/pre/scanner.h>
#include <dcc/string_map.h>
#include <dcc/settings.h>
#include <dcc/except.h>

int main(int argc, char** argv)
{
	dcc::File file("test/test.txt");
	dcc::out::StandardOutput winout;
	dcc::out::ClangConsole console(winout);

	dcc::settings.trigraph = true;

	dcc::StringMap strmap;
	dcc::pre::Scanner scanner(file, strmap);

	try {
		while (scanner.token.type != dcc::END_OF_FILE) {
			scanner.advance();
			console << "[" << (long)scanner.token.type << ": " << scanner.token.str << "] ";
		}
	} catch (dcc::Exception& e) {
		e.print(console);
	}
	console.flush();
	getchar();
}