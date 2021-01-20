/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list.hpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/20 11:02:05 by rlucas        #+#    #+#                 */
/*   Updated: 2021/01/20 16:10:49 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
# define LIST_HPP 

# include <memory> /* allocator */
# include <stdexcept>

# include "list_iterator.hpp"
# include "reverse_iterator.hpp"

# include <iostream> /* delete later! */

namespace ft {

	template <typename T, typename A = std::allocator<T> >
		class list {
			private:
				// Nested node class (private)
				class node {
					public:
						node(node const &src) {
							*this = src;
						}
						~node(void) {
						}
						// The = operator will NOT destroy data - make sure that is done
						// beforehand.
						node		&operator=(node const &rhs) {
							if (&rhs == this) { return *this; }
							_val = rhs._val;
							_next = rhs._next;
							_prev = rhs._prev;
							return *this;
						}
						node		*getNext(void) const {
							return _next;
						}
						node		*getPrev(void) const {
							return _prev;
						}
						void		setNext(node *next) {
							_next = next;
						}
						void		setPrev(node *prev) {
							_prev = prev;
						}
						T			&getData(void) {
							return _val;
						}
						const T		&getData(void) const {
							return _val;
						}

					protected:
						node		*_prev;
						node		*_next;
						T			_val;

						node(void) { }
				};

			public:
				typedef A											allocator_type;
				typedef T											value_type;
				typedef typename allocator_type::reference			reference;
				typedef typename allocator_type::const_reference	const_reference;
				typedef typename allocator_type::pointer			pointer;
				typedef typename allocator_type::const_pointer		const_pointer;
				typedef typename allocator_type::size_type			size_type;
				typedef typename allocator_type::difference_type	difference_type;
				typedef node*										node_pointer;
				typedef const node*									const_node_pointer;
				typedef ListIterator<T, difference_type, pointer,
						reference, node>							iterator;
				typedef ListIterator<T, difference_type, const_pointer,
						const_reference, const node>				const_iterator;
				typedef ReverseIterator<iterator>					reverse_iterator;
				typedef ReverseIterator<const_iterator>				const_reverse_iterator;
				typedef	std::allocator<node>						node_allocator;

				list(const allocator_type &a = allocator_type())
					: _head(0), _tail(0), _size(0), _a(a), _node_alloc() {

					}
				list(list const &src) : _head(0), _tail(0), _size(0) {
					*this = src;
				}
				~list(void) {
					this->clear();
				}
				list			&operator=(list const &rhs) {
					node		*cur = rhs._head;
					node		*new_node;

					if (&rhs == this) { return *this; }

					_a = rhs._a;
					_node_alloc = rhs._node_alloc;
					this->clear();	// Empty existing list
					while (cur) {
						// new_node = _a.allocate(sizeof(node));
						// _a.construct(new_node.getData(), cur->getData());	// Copy node data
						
						// TODO finish this when I've got more member functions
						// to work with
					}
				}

				// Iterator functions
				iterator	begin(void) {
					iterator	i(_head);
					return i;
				}
				const_iterator	begin(void) const {
					const_iterator	i(_head);
					return i;
				}
				iterator	end(void) {
					iterator	i(0);
					return i;
				}
				const_iterator	end(void) const {
					const_iterator	i(0);
					return i;
				}

				// Capacity
				size_type		size(void) const {
					return _size;
				}
				bool			empty(void) const {
					return _size == 0;
				}

				// Element access
				reference		front(void) {
					return _head->getData();
				}
				const_reference	front(void) const {
					return _head->getData();
				}
				reference		back(void) {
					return _tail->getData();
				}
				const_reference	back(void) const {
					return _tail->getData();
				}

				// Modifiers
				void			push_front(const value_type& val) {
					node		*new_node = _createNewNode(val);

					new_node->setNext(_head);
					if (_head)
						_head->setPrev(new_node);
					_head = new_node;
					if (!_tail)
						_tail = new_node;
					_size += 1;
				}

				void			pop_front(void) {
					node		*next;
					if (!_head)
						return ;
					next = _head->getNext();
					_destroyNode(_head);
					_head = next;
					_size -= 1;
					if (_size == 0) {
						_head = 0;
						_tail = 0;
					}
				}

				void			pop_back(void) {
					node		*next;
					if (!_tail)
						return ;
					next = _tail->getPrev();
					_destroyNode(_tail);
					_tail = next;
					_size -= 1;
					if (_size == 0) {
						_head = 0;
						_tail = 0;
					}
				}

				void			push_back(const value_type& val) {
					node		*new_node = _createNewNode(val);

					new_node->setPrev(_tail);
					if (_tail)
						_tail->setNext(new_node);
					_tail = new_node;
					if (!_head)
						_head = new_node;
					_size += 1;
				}

				void			clear(void) {
					node		*cur = _head;
					node		*next;
					while (cur) {
						next = cur->getNext();
						_destroyNode(cur);
						cur = next;
					}
					_size = 0;
				}
			
			private:
				node			*_head;
				node			*_tail;
				size_type		_size;
				allocator_type	_a;
				node_allocator	_node_alloc;

				node		*_createNewNode(const value_type& val) {
					node		*new_node;

					new_node = _node_alloc.allocate(1);
					_a.construct(&new_node->getData(), val);
					new_node->setPrev(0);
					new_node->setNext(0);
					return new_node;
				}

				void		_destroyNode(node *target) {
					_a.destroy(&target->getData());
					_node_alloc.deallocate(target, 1);
				}
		};
}

#endif
