#ifndef _DCC_PRE_SCANNER_H
#define _DCC_PRE_SCANNER_H

#include <dcc/pre/char_mapper.h>
#include <dcc/string_map.h>
#include <dcc/string_ref.h>
#include <dcc/enums.h>
#include <dcc/pre/token.h>
#include <unordered_map>

namespace dcc { namespace pre {

class Scanner
{
public:
	Scanner(CharMapper& chmapper, StringMap& strmap);

	void advance();

	Token token;

private:
	std::unordered_map<StringRef, TokenType> keywords;
	CharMapper& char_mapper;
	StringMap& string_map;
};

} }

#endif