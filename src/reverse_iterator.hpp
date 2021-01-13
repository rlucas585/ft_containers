/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   reverse_iterator.hpp                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/13 09:55:05 by rlucas        #+#    #+#                 */
/*   Updated: 2021/01/13 15:00:18 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP 

# include <iterator>
# include "random_access_iterator.hpp"

#include <iostream>
namespace ft {
	template <typename Iter>
		class ReverseIterator {
			private:
				typedef Iter										iterator_type;

			public:
				typedef typename iterator_type::iterator_category	iterator_category;
				typedef typename iterator_type::value_type			value_type;
				typedef typename iterator_type::difference_type		difference_type;
				typedef typename iterator_type::pointer				pointer;
				typedef typename iterator_type::reference			reference;
				typedef ReverseIterator<iterator_type>				this_type;
				typedef ReverseIterator<typename iterator_type::const_type>
					const_type;

			private:
				iterator_type		_it;

			public:
			ReverseIterator(void) : _it(0) {}
			ReverseIterator(pointer p) : _it(iterator_type(p)) {}
			explicit ReverseIterator(iterator_type const &src) : _it(src) {
				_it -= 1;
			}
			ReverseIterator(const ReverseIterator &src) : _it(src._it) {}
			iterator_type	base(void) const {
				return (_it + 1);
			}
			this_type		&operator=(this_type const &rhs) {
				if (this == &rhs) { return *this; }

				_it = rhs._it;
				return *this;
			}
			this_type		&operator++() {
				_it--;
				return *this;
			}
			this_type		operator++(int) {
				this_type	tmp(*this);
				operator++();
				return tmp;
			}
			this_type		&operator--() {
				_it++;
				return *this;
			}
			this_type		operator--(int) {
				this_type	tmp(*this);
				operator--();
				return &*tmp;
			}
			this_type		operator+(difference_type n) const {
				iterator_type	tmp(_it);
				tmp -= n;
				return &*tmp;
			}
			this_type		operator-(difference_type n) const {
				iterator_type	tmp(_it);
				tmp += n;
				return &*tmp;
			}
			// Maybe should be non-member?
			difference_type	operator-(this_type const &rhs) const {
				this_type	tmp(*this);
				return rhs._it - _it;
			}
			this_type		&operator+=(difference_type n) {
				_it -= n;
				return *this;
			}
			this_type		&operator-=(difference_type n) {
				_it += n;
				return *this;
			}
			reference		operator[](difference_type n) {
				return *(_it[- n - 1]);
			}
			reference		operator*() {
				return *_it;
			}
			pointer			operator->() {
				return &(operator*());
			}
			bool			operator==(const this_type &rhs) const {
				return _it == rhs._it;
			}
			bool		operator!=(const this_type &rhs) const {
				return _it != rhs._it;
			}
			bool		operator>(const this_type &rhs) const {
				return _it < rhs._it;
			}
			bool		operator>=(const this_type &rhs) const {
				return _it <= rhs._it;
			}
			bool		operator<(const this_type &rhs) const {
				return _it > rhs._it;
			}
			bool		operator<=(const this_type &rhs) const {
				return _it >= rhs._it;
			}
			operator	const_type() const {
				typename iterator_type::const_type  c_it(_it);

				return (&(*c_it));
			}
		};

	// Allows n + it
	template <typename Iter>
		ReverseIterator<Iter> operator+(
			const typename ReverseIterator<Iter>::difference_type n,
			const ReverseIterator<Iter>& rev_it) {
			return rev_it + n;
		}
		
	// Non-member for it1 - it2
	template <typename Iter>
		ReverseIterator<Iter> operator-(
			const ReverseIterator<Iter>& rev_it1,
			const ReverseIterator<Iter>& rev_it2) {
			return rev_it1 - rev_it2;
		}

	template <typename Iter1, typename Iter2>
				 inline bool operator==(const ReverseIterator<Iter1> &it1,
						 const ReverseIterator<Iter2> &it2) {
					 typename ReverseIterator<Iter1>::const_type	const1 = it1;
					 typename ReverseIterator<Iter2>::const_type	const2 = it2;

					 return (const1 == const2);
				 }
	template <typename Iter1, typename Iter2>
				 inline bool operator!=(const ReverseIterator<Iter1> &it1,
						 const ReverseIterator<Iter2> &it2) {
					 typename ReverseIterator<Iter1>::const_type	const1 = it1;
					 typename ReverseIterator<Iter2>::const_type	const2 = it2;

					 return (const1 != const2);
				 }
	template <typename Iter1, typename Iter2>
				 inline bool operator>=(const ReverseIterator<Iter1> &it1,
						 const ReverseIterator<Iter2> &it2) {
					 typename ReverseIterator<Iter1>::const_type	const1 = it1;
					 typename ReverseIterator<Iter2>::const_type	const2 = it2;

					 return (const1 >= const2);
				 }
	template <typename Iter1, typename Iter2>
				 inline bool operator>(const ReverseIterator<Iter1> &it1,
						 const ReverseIterator<Iter2> &it2) {
					 typename ReverseIterator<Iter1>::const_type	const1 = it1;
					 typename ReverseIterator<Iter2>::const_type	const2 = it2;

					 return (const1 > const2);
				 }
	template <typename Iter1, typename Iter2>
				 inline bool operator<=(const ReverseIterator<Iter1> &it1,
						 const ReverseIterator<Iter2> &it2) {
					 typename ReverseIterator<Iter1>::const_type	const1 = it1;
					 typename ReverseIterator<Iter2>::const_type	const2 = it2;

					 return (const1 <= const2);
				 }
	template <typename Iter1, typename Iter2>
				 inline bool operator<(const ReverseIterator<Iter1> &it1,
						 const ReverseIterator<Iter2> &it2) {
					 typename ReverseIterator<Iter1>::const_type	const1 = it1;
					 typename ReverseIterator<Iter2>::const_type	const2 = it2;

					 return (const1 < const2);
				 }

}

#endif
