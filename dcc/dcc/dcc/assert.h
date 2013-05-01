#ifndef _DCC_ASSERT_H
#define _DCC_ASSERT_H

namespace dcc { namespace impl {

void assert(bool val);

} }

#define DCC_ASSERT(x) ::dcc::impl::assert(x);

#endif