#ifndef RANGE_HPP_
#define RANGE_HPP_

#include <boost/iterator/counting_iterator.hpp>

namespace nls {

template <typename Incrementable>
class range {
public:
	typedef typename boost::counting_iterator<Incrementable> Iterator;

	explicit range(const Incrementable& _end);
	range(const Incrementable& _begin, const Incrementable& _end);

	range() = default;

	Iterator begin() noexcept;
	Iterator end() noexcept;

private:
	Iterator m_begin;
	Iterator m_end;
};

} /* namespace nls */

////////////////////////////////////////////////////////////////////////////////////////////////////

namespace nls {

template <typename Incrementable>
range<Incrementable>::range(const Incrementable& _end) : m_begin(Incrementable()), m_end(_end) {}

template <typename Incrementable>
range<Incrementable>::range(const Incrementable& _begin, const Incrementable& _end) : m_begin(_begin), m_end(_end) {}

template <typename Incrementable>
typename range<Incrementable>::Iterator range<Incrementable>::begin() noexcept {
	return m_begin;
}

template <typename Incrementable>
typename range<Incrementable>::Iterator range<Incrementable>::end() noexcept {
	return m_end;
}

}

#endif /* RANGE_HPP_ */
