#ifndef _DCC_PRE_TOKEN_H
#define _DCC_PRE_TOKEN_H

#include <dcc/enums.h>
#include <dcc/string_ref.h>
#include <dcc/source_range.h>

namespace dcc { namespace pre {

// C Langauge Preprocessing Token
// Standard: $3.1
class Token
{
public:
	// Type of the token
	TokenType type;

	// Reference to the converted string
	StringRef str;

	// Position in the original source file
	SourceRange range;
};

} }

#endif