/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map.cpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/29 08:56:11 by rlucas        #+#    #+#                 */
/*   Updated: 2021/02/27 11:36:56 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP 

#include <functional>
# include <cmath>

#include "pair.hpp"
#include "map_iterator.hpp"
#include "reverse_bi_iterator.hpp"

#include <iostream>		// TODO remove this

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
	typedef enum 	e_color {
		BLACK,
		RED
	}				t_color;

	template <typename Key,
			 typename T,
			 typename Compare = std::less<Key>,
			 typename A = std::allocator<pair<const Key, T> > 
				 >
				 class map {
					 private:
						 class node;
					 public:
						 typedef Key								key_type;
						 typedef T									mapped_type;
						 typedef pair<const key_type, mapped_type>	value_type;
						 typedef A									allocator_type;
						 typedef Compare							key_compare;
						 // TODO typedef a value_compare at some point
						 typedef typename allocator_type::reference			reference;
						 typedef typename allocator_type::const_reference	const_reference;
						 typedef typename allocator_type::pointer			pointer;
						 typedef typename allocator_type::const_pointer		const_pointer;
						 typedef typename allocator_type::size_type			size_type;
						 typedef typename allocator_type::difference_type	difference_type;
						 typedef MapIterator<T, difference_type, pointer,
								 reference, node>							iterator;
						 typedef MapIterator<T, difference_type, const_pointer,
								 const_reference, const node>				const_iterator;
						 typedef ReverseBiIterator<iterator>				reverse_iterator;
						 typedef ReverseBiIterator<const_iterator>			const_reverse_iterator;

					 private:
						 class node {
							 public:
								 node(node const &src) {
									 *this = src;
								 }
								 ~node(void) {}
								 node	&operator=(node const &rhs) {
									 if (&rhs == this) { return *this; }
								 }

								 // Access functions
								 Key const	&getKey(void) {
									 return _val.first;
								 }
								 void		setKey(Key key) {
									 _val.first = key;
								 }
								 T			&getData(void) {
									 return _val.second;
								 }
								 const T	&getData(void) const {
									 return _val.second;
								 }
								 reference	getVal(void) {
									 return _val;
								 }
								 const_reference getVal(void) const {
									 return _val;
								 }

								 // Linkage functions
								 node		*getParent(void) {
									 return _parent;
								 }
								 node		*getLeft(void) {
									 return _left;
								 }
								 node		*getRight(void) {
									 return _right;
								 }
								 node		*getGrandParent(void) {
									 if (_parent == NULL)
										 return NULL;
									 return _parent->_parent;
								 }
								 node		*getSibling(void) {
									 node		*p = _parent;
									 if (p == NULL)
										 return NULL;
									 if (this == p->_left)
										 return p->_right;
									 else
										 return p->_left;
								 }
								 node		*getUncle(void) {
									 node		*p = _parent;
									 if (p == NULL)
										 return NULL;
									 return p->getSibling();
								 }
								 node		*selectLeftMost(void) {
									 if (_left == NULL)
										 return this;
									 return _left->selectLeftMost();
								 }
								 node		*selectRightMost(void) {
									 if (_right == NULL)
										 return this;
									 return _right->selectRightMost();
								 }

								 // Rotations
								 void		rotateLeft(void) {
									 node		*nnew = _right;
									 node		*p = _parent;
									 if (nnew == NULL)	// Leaf cannot become internal node
										 return ;

									 _right = nnew->_left;
									 nnew->_left = this;
									 _parent = nnew;
									 if (_right != NULL)
										 _right->_parent = this;

									 if (p != NULL) {
										 if (this == p->_left)
											 p->_left = nnew;
										 else if (this == p->_right)
											 p->_right = nnew;
									 }
									 nnew->_parent = p;
								 }

								 void		rotateRight(void) {
									 node		*nnew = _left;
									 node		*p = _parent;
									 if (nnew == NULL)
										 return ;

									 _left = nnew->_right;
									 nnew->_right = this;
									 _parent = nnew;
									 if (_left != NULL)
										 _left->_parent = this;

									 if (p != NULL) {
										 if (this == p->_left)
											 p->_left = nnew;
										 else if (this == p->_right)
											 p->_right = nnew;
									 }
									 nnew->_parent = p;
								 }

							 public:
								 value_type	_val;
								 node		*_parent;
								 node		*_left;
								 node		*_right;
								 t_color	_color;

								 node(void) {}
						 };

					 private:
						 class value_compare {
							 friend class map;
							 public:
								 typedef bool				result_type;
								 typedef value_type			first_argument_type;
								 typedef value_type			second_argument_type;
								 bool operator() (const value_type& x, const value_type& y) const {
									 return _comp(x.first, y.first);
								 }
							 private:
								 Compare _comp;
								 value_compare(Compare c) : _comp(c) {}
						 };

					 public:
						 typedef typename A::template rebind<node>::other	node_allocator;

					 public:
						 // Constructors
						 explicit map(const key_compare& comp = key_compare(),
								 const allocator_type& alloc = allocator_type())
							 : _head(NULL), _size(0), _comp(comp), _a(alloc), _node_alloc() {
						 }

						 template <class InputIterator>
							 map (InputIterator first, InputIterator last,
									 const key_compare& comp = key_compare(),
									 const allocator_type& alloc = allocator_type()) 
							 : _head(NULL), _size(0), _comp(comp), _a(alloc), _node_alloc() {
								 this->insert(first, last);
							 }

						 ~map(void) {
							 this->clear();
						 }

						 // Iterators
						 iterator	begin(void) {
							 iterator		it;

							 if (_head)
								 it = iterator(_head->selectLeftMost());
							 else
								 it = iterator(NULL);
							 return it;
						 }
						 const_iterator	begin(void) const {
							 const_iterator		it;

							 if (_head)
								 it = const_iterator(_head->selectLeftMost());
							 else
								 it = const_iterator(NULL);

							 return it;
						 }
						 iterator	end(void) {
							 return iterator(NULL);
						 }
						 const_iterator	end(void) const {
							 return const_iterator(NULL);
						 }
						 reverse_iterator	rbegin(void) {
							 reverse_iterator	ri(_head->selectRightMost());

							 return ri;
						 }
						 const_reverse_iterator	rbegin(void) const {
							 const_reverse_iterator	ri(_head->selectRightMost());

							 return ri;
						 }
						 reverse_iterator	rend(void) {
							 return reverse_iterator(NULL);
						 }
						 const_reverse_iterator	rend(void) const {
							 return const_reverse_iterator(NULL);
						 }

						 // TODO Add the reverse iterators

						 // Capacity
						 bool		empty(void) const {
							 return _size == 0;
						 }

						 size_type	size(void) const {
							 return _size;
						 }

						 size_type	max_size(void) const {
							 size_type	ans = std::floor(std::pow(2, SYSTEM_BITS) / sizeof(node));

							 return (ans - 1);
						 }

						 // Element access

						 // Modifiers
						 ft::pair<iterator, bool>	insert(const value_type& val) {
							 ft::pair<node *, bool>	ret;
							 node		*newNode = _createNewNode(val);
							 ret = _insertInternal(_head, newNode);
							 if (ret.second == false) { // Key existed
								 _destroyNode(newNode);
							 }
							 if (ret.second) // new element added
								 _size += 1;
							 return ft::pair<iterator, bool>(iterator(ret.first), ret.second);
						 }

						 iterator	insert(iterator position, const value_type& val) {
							 if (position == this->end())
								 return this->end();
							 node					*root;
							 node					*newNode = _createNewNode(val);
							 node					*curptr = NULL;
							 node					*nextptr = NULL;
							 iterator				next = position;
							 ft::pair<node *, bool>	ret;

							 // Validate position
							 if (position != this->end()) {
								 next++;
								 if (next != this->end()) {
									 curptr = (nextptr) ? nextptr : _getPtrFromIterator(position);
									 nextptr = _getPtrFromIterator(next);
									 while (!(_comp(newNode->getKey(),nextptr->getKey())
												 && _comp(newNode->getKey(), curptr->getKey()))) {
										 position++;
										 next++;
										 if (next == this->end())
											 break ;
									 }
								 }
							 }
							 // Default insert if hint invalid
							 if (position == this->end()) {
								 ret = _insertRecurse(_head, newNode);
							 } else {
								 node		*nodeptr = _getPtrFromIterator(position);
								 // Default insert as hint was incorrect
								 if (_comp(newNode->getKey(),nodeptr->getKey())) {
									 ret = _insertRecurse(_head, newNode);
								 }
								 else
									 ret = _insertRecurse(nodeptr, newNode);
							 }

							 if (ret.second == false) // Key existed already
								 return iterator(ret.first);
							 _insertRepairTree(newNode);

							 root = _head;
							 while (root->_parent != NULL) {
								 root = root->_parent;
							 }
							 _head = root;
							 _size += 1;
							 return iterator(ret.first);
						 }

						 template <typename InputIterator>
							 void	insert(InputIterator first, InputIterator last) {
								 for (; first != last; first++)
									 this->insert(*first);
							 }

						 void		clear(void) {
							 _destroyNodeRecurse(_head);
						 }

						 // Observers
						 key_compare	key_comp(void) const {
							 return _comp;
						 }
						 value_compare	value_comp(void) const {
							 return value_compare(_comp);
						 }

					 private:
						 node			*_head;
						 size_type		_size;
						 key_compare	_comp;
						 allocator_type	_a;
						 node_allocator	_node_alloc;

						 node	*_createNewNode(const value_type& val) {
							 node		*new_node;

							 new_node = _node_alloc.allocate(1);
							 _a.construct(&new_node->getVal(), val);
							 new_node->_parent = NULL;
							 new_node->_left = NULL;
							 new_node->_right = NULL;
							 return new_node;
						 }

						 void	_destroyNode(node *target) {
							 _a.destroy(&target->getVal());
							 _node_alloc.deallocate(target, 1);
						 }

						 void	_destroyNodeRecurse(node *target) {
							 if (target == NULL)
								 return ;
							 node		*left = target->_left;
							 node		*right = target->_right;
							 _destroyNode(target);
							 _destroyNodeRecurse(left);
							 _destroyNodeRecurse(right);
						 }

						 ft::pair<node *, bool>	_insertInternal(node *root, node *n) {
							 ft::pair<node *, bool>	ret = _insertRecurse(root, n);

							 if (ret.second == false) // Key existed already
								 return ft::pair<node *, bool>(ret.first, false);
							 _insertRepairTree(n);
							 
							 root = n;
							 while (root->_parent != NULL) {
								 root = root->_parent;
							 }
							 _head = root;
							 return ft::pair<node *, bool>(n, true);
						 }

						 // Recursively travel through tree to find correct
						 // location for new node
						 ft::pair<node *, bool>	_insertRecurse(node *root, node *n) {
							 if (root != NULL) {
								 if (_comp(n->getKey(), root->getKey())) {
									 if (root->_left != NULL) {
										 return this->_insertRecurse(root->_left, n);
									 } else
										 root->_left = n;
								 } else if (n->getKey() == root->getKey()) { // Key exists
									 return ft::pair<node *, bool>(root, false); // existing iterator
								 } else {
									 if (root->_right != NULL) {
										 return this->_insertRecurse(root->_right, n);
									 } else
										 root->_right = n;
								 }
							 }

							 // Insert new node
							 n->_parent = root;
							 n->_left = NULL;
							 n->_right = NULL;
							 n->_color = RED;
							 return ft::pair<node *, bool>(n, true);
						 }

						 void		_insertRepairTree(node *n) {
							 if (n->_parent == NULL)
								 _nIsNewRootNode(n);
							 else if (n->_parent->_color == BLACK)
								 _nParentIsBlack(n);
							 else if (n->getUncle() != NULL && n->getUncle()->_color == RED)
								 _nParentAndUncleAreRed(n);
							 else
								 _nParentIsRedAndUncleIsBlack(n);
						 }

						 void		_nIsNewRootNode(node *n) {
							 n->_color = BLACK;
						 }

						 void		_nParentIsBlack(node *n) {
							 (void)n;
							 return ;
						 }

						 void		_nParentAndUncleAreRed(node *n) {
							 n->_parent->_color = BLACK;
							 n->getUncle()->_color = BLACK;
							 n->getGrandParent()->_color = RED;
							 _insertRepairTree(n->getGrandParent());
						 }

						 void		_nParentIsRedAndUncleIsBlack(node *n) {
							 node	*p = n->_parent;
							 node	*g = n->getGrandParent();

							 if (n == p->_right && p == g->_left) {
								 p->rotateLeft();
								 n = n->_left;
							 } else if (n == p->_left && p == g->_right) {
								 p->rotateRight();
								 n = n->_right;
							 }
							 _nParentIsBlackAndSiblingIsBlack(n);
						 }

						 void	_nParentIsBlackAndSiblingIsBlack(node *n) {
							 node	*p = n->_parent;
							 node	*g = n->getGrandParent();
							 
							 if (n == p->_left)
								 g->rotateRight();
							 else
								 g->rotateLeft();
							 p->_color = BLACK;
							 g->_color = RED;
						 }

						 node		*_getPtrFromIterator(iterator& position) {
							 char	*valptr = reinterpret_cast<char *>(&(*position));

							 return reinterpret_cast<node *>(valptr);
						 }
				 };
}

#endif
