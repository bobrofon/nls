#ifndef LOCK_TYPE_SET_HPP_
#define LOCK_TYPE_SET_HPP_

#include "lock_lib/lock_types/lock_types.hpp"
#include "utils/debug.hpp"

namespace LockLib {
namespace LockLogic {

typedef /*unsigned*/ int lock_count_t; // For lock count in LockTypeSet.

class LockTypeSet {
public:
	typedef LockTypes::LockType LockType;

	LockTypeSet();
	LockTypeSet(const LockType _type);
	LockTypeSet(const LockTypeSet &_src);
	LockTypeSet &operator=(const LockTypeSet &_src);
	~LockTypeSet();

	inline lock_count_t &operator[](const LockType _type);
	inline lock_count_t operator[](const LockType _type) const;
	inline LockTypeSet &operator+=(const LockTypeSet &_src);
	inline LockTypeSet &operator-=(const LockTypeSet &_src);
	inline LockTypeSet operator+(const LockTypeSet &_src) const;
	inline LockTypeSet operator-(const LockTypeSet &_src) const;
	inline bool empty() const;
	inline void clear();

	inline static bool compatible(const LockTypeSet &_lhs, const LockTypeSet &_rhs);

private:
	lock_count_t m_ex;
	lock_count_t m_pw;
	lock_count_t m_pr;
	lock_count_t m_cw;
	lock_count_t m_cr;
	lock_count_t m_nl;
};

} /* namespace LockLogic */
} /* namespace LockLib */

// Implimentation.

namespace LockLib {
namespace LockLogic {

LockTypeSet::LockTypeSet()
	: m_ex(0),
	  m_pw(0),
	  m_pr(0),
	  m_cw(0),
	  m_cr(0),
	  m_nl(0) {}
	
LockTypeSet::LockTypeSet(const LockType _type)
	: m_ex(_type == LockTypes::EX ? 1 : 0),
	  m_pw(_type == LockTypes::PW ? 1 : 0),
	  m_pr(_type == LockTypes::PR ? 1 : 0),
	  m_cw(_type == LockTypes::CW ? 1 : 0),
	  m_cr(_type == LockTypes::CR ? 1 : 0),
	  m_nl(_type == LockTypes::NL ? 1 : 0) {
		NLS_ASSERT(LockTypes::validLockType(_type));
	}

LockTypeSet::LockTypeSet(const LockTypeSet &_src)
	: m_ex(_src.m_ex),
	  m_pw(_src.m_pw),
	  m_pr(_src.m_pr),
	  m_cw(_src.m_cw),
	  m_cr(_src.m_cr),
	  m_nl(_src.m_nl) {}

LockTypeSet &LockTypeSet::operator=(const LockTypeSet &_src) {
	m_ex = _src.m_ex;
	m_pw = _src.m_pw;
	m_pr = _src.m_pr;
	m_cw = _src.m_cw;
	m_cr = _src.m_cr;
	m_nl = _src.m_nl;

	return *this;
}
	
LockTypeSet::~LockTypeSet() {}

inline lock_count_t &LockTypeSet::operator[](const LockType _type) {
	NLS_ASSERT(LockTypes::validLockType(_type));

	switch (_type) {
	case LockTypes::EX:
		return m_ex;
	case LockTypes::PW:
		return m_pw;
	case LockTypes::PR:
		return m_pr;
	case LockTypes::CW:
		return m_cw;
	case LockTypes::CR:
		return m_cr;
	case LockTypes::NL:
		return m_nl;
	default:
		return m_nl; // m_nl is useless anymore
	}
}

inline lock_count_t LockTypeSet::operator[](const LockType _type) const {
	NLS_ASSERT(LockTypes::validLockType(_type));

	switch (_type) {
	case LockTypes::EX:
		return m_ex;
	case LockTypes::PW:
		return m_pw;
	case LockTypes::PR:
		return m_pr;
	case LockTypes::CW:
		return m_cw;
	case LockTypes::CR:
		return m_cr;
	case LockTypes::NL:
		return m_nl;
	default:
		return m_nl; // m_nl is useless anymore
	}
}

inline LockTypeSet &LockTypeSet::operator+=(const LockTypeSet &_src) {
	m_ex += _src.m_ex;
	m_pw += _src.m_pw;
	m_pr += _src.m_pr;
	m_cw += _src.m_cw;
	m_cr += _src.m_cr;
	m_nl += _src.m_nl;

	return *this;
}

inline LockTypeSet &LockTypeSet::operator-=(const LockTypeSet &_src) {
	m_ex -= _src.m_ex;
	m_pw -= _src.m_pw;
	m_pr -= _src.m_pr;
	m_cw -= _src.m_cw;
	m_cr -= _src.m_cr;
	m_nl -= _src.m_nl;

	NLS_ASSERT(
		   m_ex >= 0
		&& m_pw >= 0
		&& m_pr >= 0
		&& m_cw >= 0
		&& m_cr >= 0
		&& m_nl >= 0);

	return *this;
}

inline LockTypeSet LockTypeSet::operator+(const LockTypeSet &_src) const {
	LockTypeSet tmpSet = *this;
	tmpSet += _src;

	return tmpSet;
}

inline LockTypeSet LockTypeSet::operator-(const LockTypeSet &_src) const {
	LockTypeSet tmpSet = *this;
	tmpSet -= _src;

	return tmpSet;
}

inline bool LockTypeSet::empty() const {
	return !m_ex && !m_pw && !m_pr && !m_cw && !m_cr && !m_nl;
}

inline void LockTypeSet::clear() {
	m_ex = 0;
	m_pw = 0;
	m_pr = 0;
	m_cw = 0;
	m_cr = 0;
	m_nl = 0;
}

inline bool LockTypeSet::compatible(const LockTypeSet &_lhs, const LockTypeSet &_rhs) {
	for (LockType lType = LockTypes::EX; LockTypes::validLockType(lType); ++lType) {
		for (LockType rType = LockTypes::EX; LockTypes::validLockType(rType); ++rType) {
			if (_lhs[lType] && _rhs[rType] && !LockTypes::compatible(lType, rType)) {
				return false;
			}
		}
	}

	return true;
}

} /* LockLogic */
} /* namespace LockLib */

#endif /* LOCK_TYPE_SET_HPP_ */
