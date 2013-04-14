#include <iostream>
#include <fstream>
#include <dcc/file.h>
#include <dcc/pre/scanner.h>
#include <dcc/source_range.h>
#include <dcc/out/windows_console.h>

int main(int argc, char** argv)
{
	dcc::File file("test/test.txt");
	dcc::pre::Scanner scanner(file);
	char c;
	while (c = scanner.get())
		;
	dcc::SourceRange range(file, 28, 36);
	dcc::SourceRange inner(file, 28, 29);

	dcc::out::WindowsConsole winout;

	range.print(winout);
	winout.write_string("\n");
	range.print_long(winout, inner);
	winout.write_string("\n");

	getchar();
}