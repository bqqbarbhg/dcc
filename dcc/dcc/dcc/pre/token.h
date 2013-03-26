#ifndef _DCC_PRE_TOKEN_H
#define _DCC_PRE_TOKEN_H

#include <dcc/source_range.h>

namespace dcc { namespace pre {

// C Langauge Preprocessing Token
// Standard: $3.1
class Token
{
	// Position in the original source file
	SourceRange range;
};

} }

#endif