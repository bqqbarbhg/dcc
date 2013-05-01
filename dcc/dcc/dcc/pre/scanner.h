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
	Scanner(File& file, StringMap& strmap);

	// Scans one token and updates `token` field
	void advance();

	// The current token
	Token token;
private:
	// Update `token`
	void output_token(TokenType type);

	// Get one character from the reader
	char get();
	
	std::string buffer;
	std::unordered_map<StringRef, TokenType> keywords;

	dcc::File file;
	dcc::io::FileReader file_reader;
	dcc::pre::CharMapper char_mapper;

	src_charpos_t char_pos;
	StringMap& string_map;
};

} }

#endif