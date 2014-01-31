#ifndef LOCK_TYPES_IO_HPP_
#define LOCK_TYPES_IO_HPP_

#include "lock_types_def.hpp"

#include <ostream>
inline std::ostream &operator<<(std::ostream &_stream, const LockLib::LockTypes::LockType _type) {
	_stream << LockLib::LockTypes::typeToString(_type);
	return _stream;
}

#include <istream>
#include <string>
inline std::istream &operator>>(std::istream &_stream, LockLib::LockTypes::LockType &_type) {
	std::string typeName;
	
	if (! (_stream >> typeName)) {
		return _stream;
	}

	LockLib::LockTypes::LockType tmpType = LockLib::LockTypes::stringToType(typeName);

	if (! LockLib::LockTypes::validLockType(tmpType)) {
		_stream.setstate(_stream.rdstate() | std::ios::failbit);
		return _stream;
	}

	_type = tmpType;
	return _stream;
}

#endif /* LOCK_TYPES_IO_HPP_ */
