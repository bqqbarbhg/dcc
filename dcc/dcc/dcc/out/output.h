#ifndef _DCC_OUT_OUTPUT_H
#define _DCC_OUT_OUTPUT_H

namespace dcc { namespace out {

class Output {
public:
	virtual void write(const char* str, unsigned int n) = 0;
};

} }

#endif