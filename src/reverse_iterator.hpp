/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   reverse_iterator.hpp                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/13 09:55:05 by rlucas        #+#    #+#                 */
/*   Updated: 2021/01/13 12:53:58 by rlucas        ########   odam.nl         */
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
			// ReverseIterator(iterator_type const &src) : _it(src) {
			// 	_it -= 1;
			// }
			ReverseIterator(const ReverseIterator &src) : _it(src._it) {}
			iterator_type	base(void) const {
				return _it;
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
				return tmp;
			}
			this_type		operator+(difference_type n) const {
				this_type	tmp(*this);
				tmp._it - n;
				return tmp;
			}
			this_type		operator-(difference_type n) const {
				this_type	tmp(*this);
				tmp._it + n;
				return tmp;
			}
			// Maybe should be non-member?
			this_type		operator-(this_type const &rhs) const {
				this_type	tmp(*this);
				tmp._it - rhs._it;
				return tmp;
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
				typename iterator_type::const_type  c_it = _it;

				const_type		c_rit(&*(c_it));
				return (c_rit);
			}
		};
}

#endif
