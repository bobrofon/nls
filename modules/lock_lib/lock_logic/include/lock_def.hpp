#ifndef LOCK_DEF_HPP_
#define LOCK_DEF_HPP_

namespace LockLib {
namespace LockLogic {

enum LockResult {
	LOCKED = 0,  // lock/try lock successful
	CANNOT_LOCK, // try lock faled
	UNLOCKED,    // unlock successful
	NOT_LOCKED   // unlock called on not locked object
};

typedef /*unsigned*/ int lock_count_t; // For lock count in LockTypeSet.

} /* namespace LockLogic */
} /* namespace LockLib */

#endif /* LOCK_DEF_HPP_ */ 
