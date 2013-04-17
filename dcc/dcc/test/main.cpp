#include <iostream>
#include <fstream>
#include <dcc/file.h>
#include <dcc/io/file_reader.h>
#include <dcc/source_range.h>
#include <dcc/out/output/windows_output.h>
#include <dcc/out/console/clang_console.h>

int main(int argc, char** argv)
{
	dcc::File file("test/test.txt");
	dcc::io::FileReader reader(file);
	char c;
	while (c = reader.get())
		;
	dcc::SourceRange range(file, 28, 80);
	dcc::SourceRange inner(file, 28, 29);

	dcc::out::WindowsOutput winout;
	dcc::out::ClangConsole console(winout);

	range.print(console);
	console.write_string("\n");
	range.print_long(console, inner);
	console.write_string("\n");
}