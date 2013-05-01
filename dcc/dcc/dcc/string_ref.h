#ifndef _DCC_STRING_REF_H
#define _DCC_STRING_REF_H

namespace dcc {

// Reference to a string
// Comparing equality is O(1)
typedef const char* StringRef;
/*class StringRef
{
public:
	StringRef(const char* p)
		: ptr(p) { }

	operator const char*() const { return ptr; }
private:
	const char* ptr;
};*/
}

#endif