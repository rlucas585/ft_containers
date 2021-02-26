/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_iterator.hpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/24 11:00:47 by rlucas        #+#    #+#                 */
/*   Updated: 2021/02/26 16:31:06 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPITERATOR_HPP
# define MAPITERATOR_HPP

# include <iterator>
# include <iostream>

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
			typedef MapIterator<T, Diff, Point, Ref, Node>	this_type;
		public:
			typedef std::bidirectional_iterator_tag				iterator_category;
			typedef T											value_type;
			typedef MapIterator<T, Diff, const T*, const T&,
					const Node>									const_type;
			typedef Point										pointer;
			typedef Ref											reference;
			typedef Diff										difference_type;
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
				if (_p->_parent == 0) { // Root node
					_p = _p->_right;
					if (_p == 0)
						return *this;
					while (_p->_left != 0)
						_p = _p->_left;
				} else if (_p->_right != 0) { // Right node exists - select leftmost of right
					_p = _p->_right;
					while (_p->_left != 0)
						_p = _p->_left;
				} else if (_p == _p->_parent->_left) { // No right node, _p is left of parent
					_p = _p->_parent;
				} else if (_p == _p->_parent->_right) { // No right node, _p is right of parent
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
}

#endif
