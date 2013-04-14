#include "standard_output.h"

#include <iostream>

namespace dcc { namespace out {

void StandardOutput::write(const char* str, unsigned int n)
{
	std::cout.write(str, n);
}

} }