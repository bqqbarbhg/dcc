#include "scanner.h"
#include <dcc/settings.h>
#include <dcc/unicode.h>
#include <dcc/io/file_reader.h>
#include <dcc/except.h>

namespace dcc { namespace pre {

Scanner::Scanner(File& file, StringMap& strmap)
	: file(file)
	, file_reader(file)
	, char_mapper(file_reader)
	, char_pos(file_reader.get_char_index())
	, string_map(strmap)
	, last(0)
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

SourceRange Scanner::get_current_source_range() const
{
	src_charpos_t next_char_pos = file_reader.get_char_index();
	return SourceRange(&file, char_pos, next_char_pos);
}

void Scanner::output_token(TokenType type)
{
	token.type = type;
	token.str = string_map.insert(buffer.c_str());
	
	src_charpos_t next_char_pos = file_reader.get_char_index() - 1;
	token.range = SourceRange(&file, char_pos, next_char_pos);
	char_pos = next_char_pos;

	buffer.clear();
}

char Scanner::get()
{
	if (last)
		buffer += last;
	return last = char_mapper.get();
}

void Scanner::advance()
{
	if (!last)
		get();

	char c = last;
	char lookahead;

	bool hitws = false;

	// Whitespace or comment
	while (true) {
		if (c == ' ' || c == '\t' || c == '\n') {
			c = get();
			hitws = true;
		}
		if (c == '/') {
			lookahead = get();
			if (lookahead == '*') {
				hitws = true;
				src_charpos_t comment_start = file_reader.get_char_index() - 2;
				c = get();
				if (!c)
					throw BlockCommentNotClosedException(SourceRange(&file, comment_start, comment_start + 2));
				lookahead = get();
				while (lookahead && !(c == '*' && lookahead == '/'))
					c = lookahead, lookahead = get();
				if (!lookahead)
					throw BlockCommentNotClosedException(SourceRange(&file, comment_start, comment_start + 2));
				c = get();
			}
			continue;
		}
		break;
	}
	if (hitws) {
		output_token(WHITESPACE);
		return;
	}

	// End of file
	if (!c) {
		output_token(END_OF_FILE);
		return;
	}

	// Identifier
	if (c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z' || c == '_') {
		do {
			c = get();
		} while (c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z' || c == '_' || c >= '0' && c <= '9');

		output_token(IDENTIFIER);
		auto it = keywords.find(token.str);
		if (it != keywords.end()) {
			token.type = it->second;
		}
		return;
	}

	throw UnexpectedCharException(get_current_source_range(), c);
}

} }