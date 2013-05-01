#include "scanner.h"
#include <dcc/settings.h>
#include <dcc/unicode.h>
#include <dcc/io/file_reader.h>

namespace dcc { namespace pre {

Scanner::Scanner(File& file, StringMap& strmap)
	: file(file)
	, file_reader(file)
	, char_mapper(file_reader)
	, char_pos(file_reader.get_char_index())
	, string_map(strmap)
{
	// Create the keyword lsit
	static struct {
		const char* str;
		TokenType tok;
	} kws[] = {
		{ "auto", KW_AUTO }, { "break", KW_BREAK }, { "case", KW_CASE },
		{ "char", KW_CHAR }, { "const", KW_CONST }, { "continue", KW_CONTINUE },
		{ "default", KW_DEFAULT }, { "do", KW_DO }, { "double", KW_DOUBLE },
		{ "else", KW_ELSE }, { "enum", KW_ENUM }, { "extern", KW_EXTERN },
		{ "float", KW_FLOAT }, { "for", KW_FOR }, { "goto", KW_GOTO },
		{ "if", KW_IF }, { "int", KW_INT }, { "long", KW_LONG },
		{ "register", KW_REGISTER }, { "return", KW_RETURN }, { "short", KW_SHORT },
		{ "signed", KW_SIGNED }, { "sizeof", KW_SIZEOF }, { "static", KW_STATIC },
		{ "struct", KW_STRUCT }, { "switch", KW_SWITCH }, { "typedef", KW_TYPEDEF },
		{ "union", KW_UNION }, { "unsigned", KW_UNSIGNED }, { "void", KW_VOID },
		{ "volatile", KW_VOLATILE }, { "while", KW_WHILE },
	}, *kw_end = kws + sizeof(kws) / sizeof(*kws);

	for (auto kw = kws; kw != kw_end; kw++) {
		keywords[string_map.insert(kw->str)] = kw->tok;
	}
}

void Scanner::output_token(TokenType type)
{
	token.type = type;
	token.str = string_map.insert(buffer.c_str());
	
	src_charpos_t next_char_pos = file_reader.get_char_index();
	token.range = SourceRange(&file, char_pos, next_char_pos);
	char_pos = next_char_pos;

	buffer.clear();
}

char Scanner::get()
{
	char c = char_mapper.get();
	buffer += c;
	return c;
}

void Scanner::advance()
{
	while (get()) ;
	output_token(IDENTIFIER);
}

} }