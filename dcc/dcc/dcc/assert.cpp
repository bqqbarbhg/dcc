#include "assert.h"
#include <intrin.h>

namespace dcc { namespace impl {

void assert(bool val)
{
	if (!val)
		__debugbreak();
}

} }