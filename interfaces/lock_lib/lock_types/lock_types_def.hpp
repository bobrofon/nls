#ifndef LOCK_TYPES_DEF_HPP_
#define LOCK_TYPES_DEF_HPP_

/**
 * Definition the types of locks used in lock service.
 * 
 * Lock names and their abbreviations:
 * EX - Exclusive
 * PW - Protected Write
 * PR - Protected Read
 * CW - Concurrent Write
 * CR - Concurrent Read
 * NL - Null Lock
 * 
 */
namespace LockLib {
namespace LockTypes {

enum LockType {
	EX = 0,
	PW,
	PR,
	CW,
	CR,
	NL,

	COUNT // Count of lock types
};

} /* namespace LockTypes */
} /* namespace LockLib */

/**
 * Functions for work with LockType enum.
 */
#include <string>

namespace LockLib {
namespace LockTypes {

/**
 * validLockType return "true" if "_type" may be used as a lock target.
 * Valid types: EX, PW, PR, CW, CR, NL.
 * Invalid types: COUNT and other (2^[log(COUNT)] - COUNT) undefined types.
 */
inline bool validLockType(const LockType _type) {
	return EX <= _type && _type <= NL;
}

/**
 * typeToString return string representation of type name or "UNDEFINED".
 */
inline const char *typeToString(const LockType _type) {
	switch (_type) {
	case EX:
		return "EX";
	case PW:
		return "PW";
	case PR:
		return "PR";
	case CW:
		return "CW";
	case CR:
		return "CR";
	case NL:
		return "NL";
	default:
		return "UNDEFINED";
	}
}

/**
 * stringToType return LockType that name is "_typeName".
 * If LockType with name "_typeName" doesn't exist, return COUNT.
 */
inline LockType stringToType(const std::string &_typeName) {
	if (_typeName == "EX") {
		return EX;
	} else if (_typeName == "PW") {
		return PW;
	} else if (_typeName == "PR") {
		return PR;
	} else if (_typeName == "CW") {
		return CW;
	} else if (_typeName == "CR") {
		return CR;
	} else if (_typeName == "NL") {
		return NL;
	} else {
		return COUNT; // Invalid lock type.
	}
}

} /* namespace LockTypes */
} /* namespace LockLib */

#endif /* LOCK_TYPES_DEF_HPP_ */
