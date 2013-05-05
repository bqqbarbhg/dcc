#ifndef _DCC_EXCEPT_H
#define _DCC_EXCEPT_H

#include <dcc/source_range.h>
#include <dcc/out/console.h>

namespace dcc {

class Exception {
public:
	virtual void print(out::Console& out) const = 0;
};
class SourceException : public Exception {
public:
	SourceException(const dcc::SourceRange& range)
		: range(range) { }
	dcc::SourceRange range;
};
class SimpleSourceException : public SourceException {
public:
	SimpleSourceException(const dcc::SourceRange& range, const char *msg)
		: SourceException(range), message(msg) { }
	virtual void print(out::Console& out) const;
private:
	const char *message;
};


class BlockCommentNotClosedException : public SimpleSourceException {
public:
	BlockCommentNotClosedException(const dcc::SourceRange& range)
		: SimpleSourceException(range, "Block comment was not closed") { }
};
class UnexpectedCharException : public SourceException {
public:
	UnexpectedCharException(const dcc::SourceRange& range, char c)
		: SourceException(range), ch(c) { }
	virtual void print(out::Console& out) const;
private:
	char ch;
};

}

#endif