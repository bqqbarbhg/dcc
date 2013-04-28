#ifndef _DCC_ENUMS_H
#define _DCC_ENUMS_H

namespace dcc {

enum TokenType
{
	// 0x0XXX Misc tokens
	ERROR          = 0x0000,
	WHITESPACE     = 0x0001,
	IDENTIFIER     = 0x0002,
	NUMBER         = 0x0003,
	END_OF_FILE    = 0x0004,

	// 0x1XXX Operators
	OPERATOR       = 0x1000,
	// 0x10XX Non-assign assignable operators
	OP_ADD         = 0x1001,
	OP_SUB         = 0x1002,
	OP_MUL         = 0x1003,
	OP_DIV         = 0x1004,
	OP_MOD         = 0x1005,
	OP_SHL         = 0x1006,
	OP_SHR         = 0x1007,
	OP_AND         = 0x1008,
	OP_XOR         = 0x1009,
	OP_BOR         = 0x100A,
	// 0x11XX Assign assignable operators
	OP_ADD_SET     = 0x1101,
	OP_SUB_SET     = 0x1102,
	OP_MUL_SET     = 0x1103,
	OP_DIV_SET     = 0x1104,
	OP_MOD_SET     = 0x1105,
	OP_SHL_SET     = 0x1106,
	OP_SHR_SET     = 0x1107,
	OP_AND_SET     = 0x1108,
	OP_XOR_SET     = 0x1109,
	OP_BOR_SET     = 0x110A,
	// 0x12XX Other operators
	OP_COMMA       = 0x1200,
	OP_QUESTION    = 0x1201,
	OP_COLON       = 0x1202,
	OP_BOOL_OR     = 0x1203,
	OP_BOOL_AND    = 0x1204,
	OP_EQUAL       = 0x1205,
	OP_NOT_EQUAL   = 0x1206,
	OP_LESS        = 0x1207,
	OP_LESS_EQ     = 0x1208,
	OP_GREAETER    = 0x1209,
	OP_GREATER_EQ  = 0x120A,
	OP_NOT         = 0x120B,
	OP_BOOL_NOT    = 0x120C,
	OP_DOT         = 0x120D,
	OP_ARROW       = 0x120E,
	OP_SEMICOLON   = 0x120F,
	OP_LPAREN      = 0x1210,
	OP_RPAREN      = 0x1211,
	OP_LBLOCK      = 0x1212,
	OP_RBLOCK      = 0x1213,
	OP_LBRACKET    = 0x1214,
	OP_RBRACKET    = 0x1215,

	// 0x2XXX Keywords
	KEYWORD        = 0x2000,
	KW_AUTO        = 0x2001,
	KW_BREAK       = 0x2002,
	KW_CASE        = 0x2003,
	KW_CHAR        = 0x2004,
	KW_CONST	   = 0x2005,
	KW_CONTINUE	   = 0x2006,
	KW_DEFAULT	   = 0x2007,
	KW_DO		   = 0x2008,
	KW_DOUBLE	   = 0x2009,
	KW_ELSE		   = 0x200A,
	KW_ENUM		   = 0x200B,
	KW_EXTERN	   = 0x200C,
	KW_FLOAT	   = 0x200D,
	KW_FOR		   = 0x200E,
	KW_GOTO		   = 0x200F,
	KW_IF		   = 0x2010,
	KW_INT		   = 0x2011,
	KW_LONG		   = 0x2012,
	KW_REGISTER	   = 0x2013,
	KW_RETURN	   = 0x2014,
	KW_SHORT	   = 0x2015,
	KW_SIGNED	   = 0x2016,
	KW_SIZEOF	   = 0x2017,
	KW_STATIC	   = 0x2018,
	KW_STRUCT	   = 0x2019,
	KW_SWITCH	   = 0x201A,
	KW_TYPEDEF	   = 0x201B,
	KW_UNION	   = 0x201C,
	KW_UNSIGNED	   = 0x201D,
	KW_VOID		   = 0x201E,
	KW_VOLATILE	   = 0x201F,
	KW_WHILE	   = 0x2020,
};

}

#endif