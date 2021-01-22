/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list.hpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/20 11:02:05 by rlucas        #+#    #+#                 */
/*   Updated: 2021/01/22 13:54:53 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
# define LIST_HPP 

# include <memory> /* allocator */
# include <stdexcept>
# include <algorithm>
# include <cmath>

# include "list_iterator.hpp"
# include "reverse_bi_iterator.hpp"
# include "sfinae.hpp"

# include <iostream> /* delete later! */

# ifndef SYSTEM_BITS
# ifdef __x86_64
# define SYSTEM_BITS 64
# else
# ifdef _M_AMD64
# define SYSTEM_BITS 64
# else
# define SYSTEM_BITS 32
# endif
# endif
# endif

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
				typedef ReverseBiIterator<iterator>					reverse_iterator;
				typedef ReverseBiIterator<const_iterator>			const_reverse_iterator;
				typedef	std::allocator<node>						node_allocator;

				list(const allocator_type &a = allocator_type())
					: _head(0), _size(0), _a(a), _node_alloc() {
						node		*dummy = _createDummyNode();

						_head = dummy;
						_size = 1;
					}
				list(list const &src) : _head(_createDummyNode()), _size(1) {
					*this = src;
				}
				~list(void) {
					this->clear();
					_destroyDummy(_head);
				}
				list			&operator=(list const &rhs) {
					node			*cur = rhs._head->getNext();
					node			*next;
					if (&rhs == this) { return *this; }

					this->clear();	// Empty existing list
					while (_size != rhs._size) {
						next = cur->getNext();
						this->push_back(cur->getData());
						cur = next;
					}
					return *this;
				}

				// Iterator functions
				iterator	begin(void) {
					iterator	i(_head->getNext());
					return i;
				}
				const_iterator	begin(void) const {
					const_iterator	i(_head->getNext());
					return i;
				}
				iterator	end(void) {
					iterator	i(_head);
					return i;
				}
				const_iterator	end(void) const {
					const_iterator	i(_head);
					return i;
				}
				reverse_iterator	rbegin(void) {
					reverse_iterator	ri(_head->getPrev());
					return (ri);
				}
				const_reverse_iterator	rbegin(void) const {
					const_reverse_iterator	ri(_head->getPrev());
					return (ri);
				}
				reverse_iterator	rend(void) {
					reverse_iterator	ri(_head);
					return (ri);
				}
				const_reverse_iterator	rend(void) const {
					const_reverse_iterator	ri(_head);
					return (ri);
				}

				// Capacity
				size_type		size(void) const {
					return _size - 1;
				}
				bool			empty(void) const {
					return _size == 1;
				}
				size_type		max_size(void) const {
					size_type	ans = std::floor(std::pow(2, SYSTEM_BITS) / sizeof(node));

					return (ans - 1);
				}

				// Element access
				reference		front(void) {
					return (_head->getNext())->getData();
				}
				const_reference	front(void) const {
					return (_head->getNext())->getData();
				}
				reference		back(void) {
					return (_head->getPrev())->getData();
				}
				const_reference	back(void) const {
					return (_head->getPrev())->getData();
				}

				// Modifiers
				template <class InputIterator>
					void		assign(InputIterator first, InputIterator last,
							typename ft::enable_if<ft::isIterator<InputIterator>::value, InputIterator>::type* = 0) {
						this->clear();
						for (; first != last; first++)
							this->push_back(*first);
					}

				void			assign(size_type n, const value_type& val) {
					this->clear();
					for (; n > 0; n--)
						this->push_back(val);
				}
				
				void			push_front(const value_type& val) {
					node		*new_node = _createNewNode(val);
					node		*prev_first = _head->getNext();

					new_node->setNext(prev_first);
					new_node->setPrev(_head);
					prev_first->setPrev(new_node);
					_head->setNext(new_node);
					_size += 1;
				}

				void			pop_front(void) {
					node		*first_node;
					node		*new_first;

					if (_size == 1)
						return ;
					first_node = _head->getNext();
					new_first = first_node->getNext();
					_destroyNode(first_node);
					new_first->setPrev(_head);
					_head->setNext(new_first);
					_size -= 1;
				}

				void			push_back(const value_type& val) {
					node		*new_node = _createNewNode(val);
					node		*prev_tail = _head->getPrev();

					new_node->setPrev(prev_tail);
					new_node->setNext(_head);
					prev_tail->setNext(new_node);
					_head->setPrev(new_node);
					_size += 1;
				}

				void			pop_back(void) {
					node		*prev_tail;
					node		*new_tail;

					if (_size == 1)
						return ;
					prev_tail = _head->getPrev();
					new_tail = prev_tail->getPrev();
					_destroyNode(prev_tail);
					new_tail->setNext(_head);
					_head->setPrev(new_tail);
					_size -= 1;
				}

				iterator		insert(iterator position, const value_type& val) {
					node		*new_node = _createNewNode(val);

					_insertNode(position, new_node);

					return iterator(new_node);
				}

				void			insert(iterator position, size_type n, const value_type& val) {
					while (n > 0) {
						this->insert(position, val);
						n -= 1;
					}
				}

				template <class InputIterator>
					void		insert(iterator position, InputIterator first, InputIterator last,
							typename ft::enable_if<ft::isIterator<InputIterator>::value, InputIterator>::type* = 0) {
						for (; first != last; first++)
							this->insert(position, *first);
					}

				iterator		erase(iterator position) {
					node		*cur;
					node		*prev;
					node		*next;

					if (_size == 1)
						return iterator(_head);
					// std::cout << "Erasing (size = " << _size << ")" <<
					// 	"*position = " << *position << std::endl;
					cur = _getPtrFromIterator(position);
					prev = cur->getPrev();
					next = cur->getNext();
					prev->setNext(next);
					next->setPrev(prev);
					_destroyNode(cur);
					_size -= 1;
					return iterator(next);
				}

				iterator		erase(iterator first, iterator last) {
					iterator		tmp;
					while (first != last) {
						tmp = first;
						tmp++;
						this->erase(first);
						first = tmp;
					}
					return last;
				}

				void			swap(list& x) {
					std::swap(_head, x._head);
					std::swap(_size, x._size);
				}

				void			resize(size_type n, value_type val = value_type()) {
					iterator		it = this->begin();
					size_type		new_elem_count;
					if (n < _size - 1) {
						while (n > 0) {
							it++;
							n--;
						}
						this->erase(it, this->end());
					} else if (n > _size - 1) {
						new_elem_count = n - (_size - 1);
						while (new_elem_count > 0) {
							this->push_back(val);
							new_elem_count -= 1;
						}
					}
				}

				void			clear(void) {
					node		*cur = _head->getNext();
					node		*next;

					while (_size > 1) {
						next = cur->getNext();
						_destroyNode(cur);
						cur = next;
						_size -= 1;
					}
					_head->setNext(_head);
					_head->setPrev(_head);
				}

				// Operations
				void			splice(iterator position, list& x) {
					node		*a_node;

					while (x.size() > 0) {
						a_node = x._removeNode(x.begin());
						_insertNode(position, a_node);
					}
				}

				void			splice(iterator position, list& x, iterator i) {
					node		*a_node;

					a_node = x._removeNode(i);
					_insertNode(position, a_node);
				}

				void			splice(iterator position, list& x, iterator first,
						iterator last) {
					iterator		tmp;
					while (first != last) {
						tmp = first;
						tmp++;
						this->splice(position, x, first);
						first = tmp;
					}
				}

				void			reverse(void) {
					node		*cur = _head;
					size_type	i = 0;

					while (i < _size) {
						_swapDirection(cur);
						cur = cur->getNext();
						i += 1;
					}
				}
			
			private:
				node			*_head;
				size_type		_size;
				allocator_type	_a;
				node_allocator	_node_alloc;

				node		*_createDummyNode(void) {
					node	*new_dummy;

					new_dummy = _node_alloc.allocate(1);
					new_dummy->setPrev(new_dummy);
					new_dummy->setNext(new_dummy);
					return new_dummy;
				}

				void		_destroyDummy(node *target) {
					_node_alloc.deallocate(target, 1);
				}

				node		*_createNewNode(const value_type& val) {
					node		*new_node;

					new_node = _node_alloc.allocate(1);
					_a.construct(&new_node->getData(), val);
					new_node->setPrev(0);
					new_node->setNext(0);
					return new_node;
				}

				void		_insertNode(iterator position, node *new_node) {
					node	*cur = _getPtrFromIterator(position);
					node	*prev = cur->getPrev();

					new_node->setNext(cur);
					new_node->setPrev(prev);
					prev->setNext(new_node);
					cur->setPrev(new_node);
					_size += 1;
				}

				node		*_removeNode(node *target) {
					node		*prev = target->getPrev();
					node		*next = target->getNext();

					prev->setNext(next);
					next->setPrev(prev);
					_size -= 1;
					return target;
				}

				node		*_removeNode(iterator i) {
					node		*target = _getPtrFromIterator(i);

					return _removeNode(target);
				}

				void		_destroyNode(node *target) {
					_a.destroy(&target->getData());
					_node_alloc.deallocate(target, 1);
				}

				void		_swapDirection(node *target) {
					node		*tmp = target->getNext();

					target->setNext(target->getPrev());
					target->setPrev(tmp);
				}

				// Use with caution
				node		*_getPtrFromIterator(iterator& position) {
					char	*valptr = reinterpret_cast<char *>(&(*position));

					valptr -= 2 * sizeof (node *);
					return reinterpret_cast<node *>(valptr);
				}
		};
}

#endif
