/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   random_access_iterator.hpp                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/10 14:27:55 by rlucas        #+#    #+#                 */
/*   Updated: 2021/01/22 11:36:53 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDACCESSITERATOR_HPP
# define RANDACCESSITERATOR_HPP

# include <iterator>

namespace ft {
	template <typename T, typename Diff, typename Point, typename Ref>
		class RandAccessIterator :
			public std::iterator<
			std::random_access_iterator_tag,
			T,
			Diff,
			Point,
			Ref>
	{
		private:
			typedef RandAccessIterator<T, Diff, Point, Ref>			this_type;

		public:
			typedef std::random_access_iterator_tag					iterator_category;
			typedef T												value_type;
			typedef RandAccessIterator<T, Diff, const T*, const T&>	const_type;
			typedef Point											pointer;
			typedef Ref												reference;
			typedef Diff											difference_type;

		private:
			pointer		_p;
		public:
			RandAccessIterator(void) : _p(0) {}
			explicit RandAccessIterator(pointer x) : _p(x) {}
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
				return tmp;
			}
			this_type	operator+(difference_type n) const {
				return this_type(_p + n);
			}
			this_type	operator-(difference_type n) const {
				return this_type(_p - n);
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
			reference	operator[](difference_type i) {
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
			pointer		operator->() {
				return _p;
			}
			// Enable implicit casting of non-const iterator to const iterator
			operator	const_type() const {
				return const_type(_p);
			}
	};
	// Allows n + it
	template <typename T, typename Diff, typename P, typename R>
		RandAccessIterator<T, Diff, P, R> operator+(
				const typename RandAccessIterator<T, Diff, P, R>::difference_type n,
				const RandAccessIterator<T, Diff, P, R> it) {
			return (it + n);
		}

	// Non-member for it1 - it2
	template <typename T, typename Diff, typename P, typename R>
		RandAccessIterator<T, Diff, P, R> operator-(
				const RandAccessIterator<T, Diff, P, R> it1,
				const RandAccessIterator<T, Diff, P, R> it2) {
			return (it1 - it2);
		}

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
}

#endif
