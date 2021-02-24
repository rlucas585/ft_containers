/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_iterator.hpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/24 11:00:47 by rlucas        #+#    #+#                 */
/*   Updated: 2021/02/24 13:07:26 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPITERATOR_HPP
# define MAPITERATOR_HPP

# include <iterator>

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
			node_pointer		_previous;

		public:
			MapIterator(void) : _p(0), _previous(0) {}
			explicit MapIterator(node_pointer x) : _p(x), _previous(0) {}
			MapIterator(const this_type &it) : _p(it._p), _previous(it._previous) {}
			this_type	&operator=(this_type const &rhs) {
				if (this == &rhs) { return *this; }
				_p = rhs._p;
				_previous = rhs._previous;
				return *this;
			}
			this_type	&operator++() {
				if (_previous == _p->_left) { // Select leftmost of _p->_right
					_previous = _p;
					if (_p->_right == NULL) // No _p->_right, select parent
						_p = _p->_parent;
					else
						_p = _p->_right->selectLeftMost();
				} else if (_p->_parent == NULL) {
						_previous = _p;
						_p = NULL;
				} else if (_p == _p->_parent->_left) {
					_previous = _p;
					_p = _p->_parent;
					
				} else if (_p->_right != NULL) {
					_previous = _p;
					_p = _p->_right->selectLeftMost();
				} else if (_p == _p->_parent->_right) {
					_previous = _p;
					while (_p->_parent != NULL && _p == _p->_parent->_right) {
						_previous = _p;
						_p = _p->_parent;
					}
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
				return &(_p->getData());
			}

			bool		operator==(const this_type &rhs) const {
				return _p == rhs._p;
			}
			bool		operator!=(const this_type &rhs) const {
				return _p != rhs._p;
			}
	};
}

#endif
