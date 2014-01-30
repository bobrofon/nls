#ifndef LOCK_TYPES_OPERATION_HPP_
#define LOCK_TYPES_OPERATION_HPP_

#include "lock_types_def.hpp"

/**
 * Matrix of lock types compatibility.
 * 
 * Type EX  PW  PR  CW  CR  NL
 * EX   No  No  No  No  No  Yes
 * PW   No  No  No  No  Yes Yes
 * PR   No  No  Yes No  Yes Yes
 * CW   No  No  No  Yes Yes Yes
 * CR   No  Yes Yes Yes Yes Yes
 * NL   Yes Yes Yes Yes Yes Yes
 *
 * Matrix of lock types union.
 *
 * Type EX PW PR CW CR NL
 * EX   EX EX EX EX EX EX
 * PW   EX PW PW PW PW PW
 * PR   EX PW PR PW PR PR
 * CW   EX PW PW CW CW CW
 * CR   EX PW PR CW CR CR
 * NL   EX PW PR CW CR NL
 */
namespace LockLib {
namespace LockTypes {

/**
 * compatible return true if two client can hold locks with types _lhs and _rhs concurrently.
 * See matrix of lock types compatibility.
 */
inline bool compatible(const LockType _lhs, const LockType _rhs) {
	if (_lhs == NL || _rhs == NL) {
		return true;
	} else if (_lhs == EX || _rhs == EX) {
		return false;
	} else if (_lhs == CR || _rhs == CR) {
		return true;
	} else if (_lhs == PW || _rhs == PW) {
		return false;
	} else if (_lhs == _rhs) {
		return true; // (CW and CW) or (PR and PR)
	} else {
		return false;
	}
}

} /* namespace LockTypes */
} /* namespace LockLib */

/**
 * Operators
 */

/**
 * Return union of two lock types.
 * See matrix of lock types union.
 */
inline LockLib::LockTypes::LockType operator+(const LockLib::LockTypes::LockType _lhs, const LockLib::LockTypes::LockType _rhs) {

	if (_lhs == LockLib::LockTypes::EX || _rhs == LockLib::LockTypes::EX) {
		return LockLib::LockTypes::EX;
	} else if (_lhs == LockLib::LockTypes::PW || _rhs == LockLib::LockTypes::PW) {
		return LockLib::LockTypes::PW;
	} else if (
		   (_lhs == LockLib::LockTypes::PR && _rhs == LockLib::LockTypes::CW)
		|| (_lhs == LockLib::LockTypes::CW && _rhs == LockLib::LockTypes::PR)) {

		return LockLib::LockTypes::PW;
	} else if (_lhs == LockLib::LockTypes::PR || _rhs == LockLib::LockTypes::PR) {
		return LockLib::LockTypes::PR;
	} else if (_lhs == LockLib::LockTypes::CW || _rhs == LockLib::LockTypes::CW) {
		return LockLib::LockTypes::CW;
	} else if (_lhs == LockLib::LockTypes::CR || _rhs == LockLib::LockTypes::CR) {
		return LockLib::LockTypes::CR;
	} else {
		return LockLib::LockTypes::NL;
	}
}

/**
 * Return next lock type or COUNT, if end of valid type values.
 */
inline LockLib::LockTypes::LockType &operator++(LockLib::LockTypes::LockType &_type) {
	switch (_type) {
	case LockLib::LockTypes::EX:
		_type = LockLib::LockTypes::PW;
		break;
	case LockLib::LockTypes::PW:
		_type = LockLib::LockTypes::PR;
		break;
	case LockLib::LockTypes::PR:
		_type = LockLib::LockTypes::CW;
		break;
	case LockLib::LockTypes::CW:
		_type = LockLib::LockTypes::CR;
		break;
	case LockLib::LockTypes::CR:
		_type = LockLib::LockTypes::NL;
		break;
	default:
		_type = LockLib::LockTypes::COUNT; // Invalid type.
	}

	return _type;
}

inline LockLib::LockTypes::LockType operator++(const LockLib::LockTypes::LockType _type, int) {
	LockLib::LockTypes::LockType type = _type;
	return ++type;
}

#endif /* LOCK_TYPES_OPERATION_HPP_ */
