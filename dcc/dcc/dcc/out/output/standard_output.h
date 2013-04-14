#ifndef _DCC_OUT_STANDARD_OUTPUT_H
#define _DCC_OUT_STANDARD_OUTPUT_H

#include <dcc/out/output.h>

namespace dcc { namespace out {

class StandardOutput : public Output {
public:
	virtual void write(const char* str, unsigned int n);
};

} }

#endif