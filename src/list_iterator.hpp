/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bidirectional_iterator.hpp                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/20 11:23:00 by rlucas        #+#    #+#                 */
/*   Updated: 2021/01/20 16:28:17 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LISTITERATOR_HPP
# define LISTITERATOR_HPP

# include <iterator>

# include <iostream> /* remove this later! */

namespace ft {
	template <typename T, typename Diff, typename Point, typename Ref,
			 typename Node>
		class ListIterator :
			public std::iterator<
			std::bidirectional_iterator_tag,
			T,
			Diff,
			Point,
			Ref>
	{
		private:
			typedef ListIterator<T, Diff, Point, Ref, Node>	this_type;
		public:
			typedef std::bidirectional_iterator_tag					iterator_category;
			typedef T												value_type;
			typedef ListIterator<T, Diff, const T*, const T&,
					const Node>										const_type;
			typedef Point											pointer;
			typedef Ref												reference;
			typedef Diff											difference_type;
			typedef Node*											node_pointer;

		private:
			node_pointer	_p;

		public:
			ListIterator(void) : _p(0) {}
			ListIterator(node_pointer x) : _p(x) {}
			ListIterator(const this_type &it) : _p(it._p) {}
			this_type	&operator=(this_type const &rhs) {
				if (this == &rhs) { return *this; }
				_p = rhs._p;
				return *this;
			}
			this_type	&operator++() {
				_p = _p->getNext();
				return *this;
			}
			this_type	operator++(int) {
				this_type	tmp(*this);
				operator++();
				return tmp;
			}
			this_type	&operator--() {
				_p = _p->getPrev();
				return *this;
			}
			this_type	operator--(int) {
				this_type	tmp(*this);
				operator--();
				return tmp;
			}
			reference	operator*() {
				return _p->getData();
			}
			pointer		operator->() {
				return &(_p->getData());
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
			operator	const_type() const {
				return const_type(_p);
			}
	};

	template <typename T, typename Diff, typename P1, typename P2, typename R1,
			 typename R2, typename N1, typename N2>
				 inline bool operator==(const ListIterator<T, Diff, P1, R1, N1> &it1,
						 const ListIterator<T, Diff, P2, R2, N2> &it2) {
					 ListIterator<T, Diff, const T*, const T&, const N1>	const1 = it1;
					 ListIterator<T, Diff, const T*, const T&, const N2>	const2 = it2;

					 return (const1 == const2);
				 }
	template <typename T, typename Diff, typename P1, typename P2, typename R1,
			 typename R2, typename N1, typename N2>
				 inline bool operator!=(const ListIterator<T, Diff, P1, R1, N1> &it1,
						 const ListIterator<T, Diff, P2, R2, N2> &it2) {
					 ListIterator<T, Diff, const T*, const T&, const N1>	const1 = it1;
					 ListIterator<T, Diff, const T*, const T&, const N2>	const2 = it2;

					 return (const1 != const2);
				 }
}

#endif
