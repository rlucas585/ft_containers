/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_iterator.hpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/24 11:00:47 by rlucas        #+#    #+#                 */
/*   Updated: 2021/02/28 11:14:24 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPITERATOR_HPP
#define MAPITERATOR_HPP

#include <iterator>
#include "e_color.hpp"

#include <iostream>

namespace ft {
	template <typename T, typename Diff, typename Point, typename Ref,
			 typename Node>
				 class MapIterator :
					 public std::iterator<
					 std::bidirectional_iterator_tag,
					 T,
					 Diff,
					 Point,
					 Ref>
	{
		private:
			typedef MapIterator<T, Diff, Point, Ref, Node>		this_type;
		public:
			typedef std::bidirectional_iterator_tag				iterator_category;
			typedef T											value_type;
			typedef Point										pointer;
			typedef Ref											reference;
			typedef Diff										difference_type;
			typedef MapIterator<T, Diff, const typename Node::val_type*,
					const typename Node::val_type&,
					const Node>									const_type;
			typedef Node*										node_pointer;

		private:
			node_pointer		_p;

		public:
			MapIterator(void) : _p(0) {}
			explicit MapIterator(node_pointer x) : _p(x) {}
			MapIterator(const this_type &it) : _p(it._p) {}
			this_type	&operator=(this_type const &rhs) {
				if (this == &rhs) { return *this; }
				_p = rhs._p;
				return *this;
			}
			this_type	&operator++() {
				if (_p == 0)
					return *this;
				if (_p->_color == DUMMY) {
					_p = _p->_right;
					return *this;
				}
				if (_p->_parent == 0) { // Root node or Dummy
					// std::cout << "Case 1" << std::endl;
					_p = _p->_right;
					if (_p == 0 || _p->_color == DUMMY)
						return *this;
					while (_p->_left != 0 && _p->_color != DUMMY)
						_p = _p->_left;
				} else if (_p->_right != 0) { // Right node exists - select leftmost of right
					// std::cout << "Case 2" << std::endl;
					_p = _p->_right;
					while (_p->_left != 0 && _p->_color != DUMMY) // If dummy, return
						_p = _p->_left;
				} else if (_p == _p->_parent->_left) { // No right node, _p is left of parent
					// std::cout << "Case 3" << std::endl;
					_p = _p->_parent;
				} else if (_p == _p->_parent->_right) { // No right node, _p is right of parent
					// std::cout << "Case 4" << std::endl;
					while (_p->_parent != 0 && _p == _p->_parent->_right)
						_p = _p->_parent;
					if (_p->_parent == 0)
						_p = 0;
					else
						_p = _p->_parent;
				}
				return *this;
			}
			this_type	operator++(int) {
				this_type	tmp(*this);
				operator++();
				return tmp;
			}
			this_type	&operator--() {
				if (_p == 0)
					return *this;
				if (_p->_color == DUMMY) {
					_p = _p->_left;
					return *this;
				}
				if (_p->_parent == 0) { // Root node or dummy
					// std::cout << "Case 1" << std::endl;
					_p = _p->_left;
					if (_p == 0 || _p->_color == DUMMY)
						return *this;
					while (_p->_right != 0 && _p->_color != DUMMY)
						_p = _p->_right;
				} else if (_p->_left != 0) { // Left node exists - select rightmost of left
					// std::cout << "Case 2" << std::endl;
					_p = _p->_left;
					while (_p->_right != 0 && _p->_color != DUMMY) // If dummy, return
						_p = _p->_right;
				} else if (_p == _p->_parent->_right) { // No left node, _p is right of parent
					// std::cout << "Case 3" << std::endl;
					_p = _p->_parent;
				} else if (_p == _p->_parent->_left) { // No left node, _p is left of parent
					// std::cout << "Case 4" << std::endl;
					while (_p->_parent != 0 && _p == _p->_parent->_left)
						_p = _p->_parent;
					if (_p->_parent == 0)
						_p = 0;
					else
						_p = _p->_parent;
				}
				return *this;
			}
			this_type	operator--(int) {
				this_type	tmp(*this);
				operator--();
				return tmp;
			}
			reference	operator*() {
				return _p->getVal();
			}
			pointer		operator->() {
				return &(_p->getVal());
			}

			bool		operator==(const this_type &rhs) const {
				return _p == rhs._p;
			}
			bool		operator!=(const this_type &rhs) const {
				return _p != rhs._p;
			}

			// Enable implicit casting of non-const iterator to const iterator
			operator	const_type() const {
				return const_type(_p);
			}
	};

	template <typename T, typename Diff, typename P1, typename P2, typename R1,
			 typename R2, typename N1, typename N2>
				 inline bool operator==(const MapIterator<T, Diff, P1, R1, N1> &it1,
						 const MapIterator<T, Diff, P2, R2, N2> &it2) {
					 MapIterator<T, Diff, const typename N1::val_type*,
					 const typename N1::val_type&, const N1>	const1 = it1;
					 MapIterator<T, Diff, const typename N2::val_type*,
					 const typename N2::val_type&, const N2>	const2 = it2;

					 return (const1 == const2);
				 }
	template <typename T, typename Diff, typename P1, typename P2, typename R1,
			 typename R2, typename N1, typename N2>
				 inline bool operator!=(const MapIterator<T, Diff, P1, R1, N1> &it1,
						 const MapIterator<T, Diff, P2, R2, N2> &it2) {
					 MapIterator<T, Diff, const typename N1::val_type*,
					 const typename N1::val_type&, const N1>	const1 = it1;
					 MapIterator<T, Diff, const typename N2::val_type*,
					 const typename N2::val_type&, const N2>	const2 = it2;

					 return (const1 != const2);
				 }
}

#endif
