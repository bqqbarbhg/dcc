#include <iostream>
#include <fstream>
#include <dcc/file.h>
#include <dcc/pre/scanner.h>
#include <dcc/source_range.h>
#include <dcc/out/output/windows_output.h>
#include <dcc/out/console/clang_console.h>

int main(int argc, char** argv)
{
	dcc::File file("test/test.txt");
	dcc::pre::Scanner scanner(file);
	char c;
	while (c = scanner.get())
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