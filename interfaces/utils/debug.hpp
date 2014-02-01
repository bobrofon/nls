#ifndef DEBUG_HPP_
#define DEBUG_HPP_

#define NLS_DEBUG always_true_while_develop

#ifdef NLS_DEBUG

#include <assert.h>
#define NLS_ASSERT(expr) assert(expr)

#else

#define NLS_ASSERT(expr)

#endif /* NSL_DEBUG */

#endif /* DEBUG_HPP_ */
