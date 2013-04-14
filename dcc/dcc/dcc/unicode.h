#ifndef _DCC_UNICODE_H
#define _DCC_UNICODE_H

namespace dcc {

inline bool is_utf8_continuation_byte(char ch) {
	return (ch & 0xc0) == 0x80;
}

}

#endif