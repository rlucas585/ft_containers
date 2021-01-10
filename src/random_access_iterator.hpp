/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   random_access_iterator.hpp                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/10 14:27:55 by rlucas        #+#    #+#                 */
/*   Updated: 2021/01/10 15:59:35 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iterator>
#include <iostream>
#include <typeinfo>

template <typename T, typename Diff, typename Point, typename Ref>
class RandAccessIterator :
	public std::iterator<
	std::random_access_iterator_tag,
	T,
	Diff,
	Point,
	Ref>
{
	public:
	typedef RandAccessIterator<T, Diff, Point, Ref>			this_type;
	typedef RandAccessIterator<T, Diff, const T*, const T&>	const_type;
	typedef Point											pointer;
	typedef Ref												reference;
	typedef Diff											difference_type;
	typedef const pointer									const_pointer;
	typedef const reference									const_reference;

	private:
	pointer		_p;
	public:
	RandAccessIterator(void) : _p(0) {}
	RandAccessIterator(pointer x) : _p(x) {}
	RandAccessIterator(const this_type &it) : _p(it._p) {}
	this_type	&operator=(this_type const &rhs) {
		if (this == &rhs) { return *this; }
		_p = rhs._p;
		return *this;
	}
	this_type	&operator++() {
		++_p;
		return *this;
	}
	this_type	operator++(int) {
		this_type	tmp(*this);
		operator++();
		return tmp;
	}
	this_type	&operator--() {
		--_p;
		return *this;
	}
	this_type	operator--(int) {
		this_type	tmp(*this);
		operator--();
		return *this;
	}
	this_type	operator+(difference_type n) const {
		return _p + n;
	}
	this_type	operator+(const this_type &rhs) const {
		return _p + rhs._p;
	}
	this_type	operator-(difference_type n) const {
		return _p - n;
	}
	difference_type	operator-(const this_type &rhs) const {
		return _p - rhs._p;
	}
	this_type	&operator+=(difference_type n) {
		_p += n;
		return (*this);
	}
	this_type	&operator-=(difference_type n) {
		_p -= n;
		return (*this);
	}
	reference	operator[](size_t i) {
		return *(_p + i);
	}
	bool		operator==(const this_type &rhs) const {
		return _p == rhs._p;
	}
	bool		operator!=(const this_type &rhs) const {
		return _p != rhs._p;
	}
	bool		operator>(const this_type &rhs) const {
		return _p > rhs._p;
	}
	bool		operator>=(const this_type &rhs) const {
		return _p >= rhs._p;
	}
	bool		operator<(const this_type &rhs) const {
		return _p < rhs._p;
	}
	bool		operator<=(const this_type &rhs) const {
		return _p <= rhs._p;
	}
	reference	operator*() {
		return *_p;
	}
	pointer	operator->() {
		return _p;
	}
	operator	const_type() const {
		return const_type(_p);
	}
};

template <typename T, typename Diff, typename P1, typename P2, typename R1,
		 typename R2>
inline bool operator==(const RandAccessIterator<T, Diff, P1, R1> &it1,
		const RandAccessIterator<T, Diff, P2, R2> &it2) {
	RandAccessIterator<T, Diff, const T*, const T&>		const1 = it1;
	RandAccessIterator<T, Diff, const T*, const T&>		const2 = it2;

	return (const1 == const2);
}

template <typename T, typename Diff, typename P1, typename P2, typename R1,
		 typename R2>
inline bool operator!=(const RandAccessIterator<T, Diff, P1, R1> &it1,
		const RandAccessIterator<T, Diff, P2, R2> &it2) {
	RandAccessIterator<T, Diff, const T*, const T&>		const1 = it1;
	RandAccessIterator<T, Diff, const T*, const T&>		const2 = it2;

	return (const1 != const2);
}

template <typename T, typename Diff, typename P1, typename P2, typename R1,
		 typename R2>
inline bool operator>=(const RandAccessIterator<T, Diff, P1, R1> &it1,
		const RandAccessIterator<T, Diff, P2, R2> &it2) {
	RandAccessIterator<T, Diff, const T*, const T&>		const1 = it1;
	RandAccessIterator<T, Diff, const T*, const T&>		const2 = it2;

	return (const1 >= const2);
}

template <typename T, typename Diff, typename P1, typename P2, typename R1,
		 typename R2>
inline bool operator>(const RandAccessIterator<T, Diff, P1, R1> &it1,
		const RandAccessIterator<T, Diff, P2, R2> &it2) {
	RandAccessIterator<T, Diff, const T*, const T&>		const1 = it1;
	RandAccessIterator<T, Diff, const T*, const T&>		const2 = it2;

	return (const1 > const2);
}

template <typename T, typename Diff, typename P1, typename P2, typename R1,
		 typename R2>
inline bool operator<=(const RandAccessIterator<T, Diff, P1, R1> &it1,
		const RandAccessIterator<T, Diff, P2, R2> &it2) {
	RandAccessIterator<T, Diff, const T*, const T&>		const1 = it1;
	RandAccessIterator<T, Diff, const T*, const T&>		const2 = it2;

	return (const1 <= const2);
}

template <typename T, typename Diff, typename P1, typename P2, typename R1,
		 typename R2>
inline bool operator<(const RandAccessIterator<T, Diff, P1, R1> &it1,
		const RandAccessIterator<T, Diff, P2, R2> &it2) {
	RandAccessIterator<T, Diff, const T*, const T&>		const1 = it1;
	RandAccessIterator<T, Diff, const T*, const T&>		const2 = it2;

	return (const1 < const2);
}
