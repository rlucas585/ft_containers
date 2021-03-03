/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map.cpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/29 08:56:11 by rlucas        #+#    #+#                 */
/*   Updated: 2021/03/03 14:45:12 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP 

#include <functional>
#include <cmath>

#include "pair.hpp"
#include "e_color.hpp"
#include "map_iterator.hpp"
#include "reverse_bi_iterator.hpp"

#include <iostream>		// TODO remove this

#ifndef SYSTEM_BITS
#ifdef __x86_64
#define SYSTEM_BITS 64
#else
#ifdef _M_AMD64
#define SYSTEM_BITS 64
#else
#define SYSTEM_BITS 32
#endif
#endif
#endif

std::string		color_converter(ft::e_color color) {
	switch (color) {
		case ft::RED: 
			return "RED";
		case ft::BLACK:
			return "BLACK";
		case ft::DUMMY:
			return "DUMMY";
	}
	return "RED";
}

template <typename Node>
void			print_node(Node *n) {
	if (n->_color == ft::DUMMY) {
		std::cout << "Dummy node: ";
		if (n->getLeft() != n) {
			std::cout << "Left: " << n->getLeft()->getKey() << ", ";
		} else {
			std::cout << "No Left node.";
		}
		if (n->getRight() != n)
			std::cout << "Right: " << n->getRight()->getKey() << ", ";
		else
			std::cout << "No Right node.";
		std::cout << std::endl;
		return ;
	}
	if (n->_parent == NULL)
		std::cout << "Head node: ";
	else
		std::cout << "node: ";
	std::cout << "Key: " << n->getKey(); std::cout << ", Value: " << n->getData();
	std::cout << ", Color: " << color_converter(n->_color);
	std::cout << std::endl;
}

template <typename Node>
void		print_map(Node *root, size_t depth) {
	if (root->_color == ft::DUMMY)
		return ;
	for (size_t i = 0; i < depth; i++)
		std::cout << "-";
	print_node(root);
	if (root->getLeft())
		print_map(root->getLeft(), depth + 1);
	if (root->getRight())
		print_map(root->getRight(), depth + 1);
}

namespace ft {
	template <typename Key,
			 typename T,
			 typename Compare = std::less<Key>,
			 typename A = std::allocator<pair<const Key, T> > 
				 >
				 class map {
					 public:
						 class node;
					 public:
						 typedef Key								key_type;
						 typedef T									mapped_type;
						 typedef pair<const key_type, mapped_type>	value_type;
						 typedef A									allocator_type;
						 typedef Compare							key_compare;
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

					 public:
						 class node {
							 public:
								 typedef pair<const Key, T>					val_type;
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
								 void		swap(node *other) {
									 node		*tmpParent = other->_parent;
									 node		*tmpLeft = other->_left;
									 node		*tmpRight = other->_right;

									 other->_left = _left;
									 other->_right = _right;
									 other->_parent = _parent;
									 if (tmpParent) {
										 if (other == tmpParent->_left)
											 tmpParent->_left = this;
										 else
											 tmpParent->_right = this;
									 }
									 if (tmpLeft)
										 tmpLeft->_parent = this;
									 if (tmpRight)
										 tmpRight->_parent = this;
									 if (_parent) {
										 if (this == _parent->_left)
											 _parent->_left = other;
										 else
											 _parent->_right = other;
									 }
									 if (_right)
										 _right->_parent = other;
									 if (_left)
										 _left->_parent = other;
									 _parent = tmpParent;
									 _left = tmpLeft;
									 _right = tmpRight;
								 }
								 bool		hasRedChild(void) {
									 if (_left != NULL && _left->_color == RED)
										 return true;
									 if (_right != NULL && _right->_color == RED)
										 return true;
									 return false;
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
								 e_color	_color;

								 node(void) {}
						 };

					 public:
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
								 _dummy = _createDummyNode();
						 }

						 template <class InputIterator>
							 map (InputIterator first, InputIterator last,
									 const key_compare& comp = key_compare(),
									 const allocator_type& alloc = allocator_type()) 
							 : _head(NULL), _size(0), _comp(comp), _a(alloc), _node_alloc() {
								 _dummy = _createDummyNode();
								 this->insert(first, last);
							 }
						 
						 map(const map& other)
							 : _head(NULL), _size(0), _comp(other._comp),
							 _a(other._a), _node_alloc(other._node_alloc), _dummy(_createDummyNode()) {
							 *this = other;
						 }
						 map	&operator=(const map& rhs) {
							 if (this == &rhs) { return *this; }
							 const_iterator	start = rhs.begin();
							 const_iterator	end = rhs.end();

							 this->clear();
							 this->insert(start, end);
							 return *this;
						 }

						 ~map(void) {
							 this->clear();
							 std::cout << "Clear successful" << std::endl;
							 _destroyDummy(_dummy);
							 std::cout << "dummy destruction successful" << std::endl;
						 }

						 // Iterators
						 iterator	begin(void) {
							 iterator		it;

							 if (_head)
								 it = iterator(_dummy->_right);
							 else
								 it = iterator(_dummy);
							 return it;
						 }
						 const_iterator	begin(void) const {
							 const_iterator		it;

							 if (_head)
								 it = iterator(_dummy->_right);
							 else
								 it = iterator(_dummy);

							 return it;
						 }
						 iterator	end(void) {
							 return iterator(_dummy);
						 }
						 const_iterator	end(void) const {
							 return const_iterator(_dummy);
						 }
						 reverse_iterator	rbegin(void) {
							 // reverse_iterator	ri(_head->selectRightMost());
							 reverse_iterator	ri(_dummy->_left);

							 return ri;
						 }
						 const_reverse_iterator	rbegin(void) const {
							 const_reverse_iterator	ri(_dummy->_left);

							 return ri;
						 }
						 reverse_iterator	rend(void) {
							 return reverse_iterator(_dummy);
						 }
						 const_reverse_iterator	rend(void) const {
							 return const_reverse_iterator(_dummy);
						 }

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
						 mapped_type&	operator[] (const key_type& k) {
							 _disconnectDummy();
							 mapped_type&		ret = _atRecurse(_head, k);
							 _reconnectDummy();
							 return ret;
						 }

						 // Modifiers
						 ft::pair<iterator, bool>	insert(const value_type& val) {
							 ft::pair<node *, bool>	ret;
							 node		*newNode = _createNewNode(val);

							 _disconnectDummy();
							 ret = _insertInternal(_head, newNode);
							 if (ret.second == false) { // Key existed
								 _destroyNode(newNode);
							 }
							 if (ret.second) // new element added
								 _size += 1;
							 _reconnectDummy();
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
							 _disconnectDummy();
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

							 if (ret.second == false) { // Key existed already
								 _destroyNode(newNode);
								 _reconnectDummy();
								 return iterator(ret.first);
							 }
							 _insertRepairTree(newNode);
							 _reconnectDummy();

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

						 node		*getHead(void) {
							 return _head;
						 }

						 node		*getDummy(void) {
							 return _dummy;
						 }

						 void		erase(iterator position) {
							 if (_size == 0)
								 return ;
							 _disconnectDummy();
							 node		*deleted = _deleteInternal(position);
							 _destroyNode(deleted);
							 std::cout << "hello" << std::endl;
							 _reconnectDummy();

							 _size -= 1;
						 }

						 void		clear(void) {
							 std::cout << "clear() called, head = " << _head << std::endl;
							 _disconnectDummy();
							 std::cout << "dummy disconnected successfully" << std::endl;
							 _destroyNodeRecurse(_head);
							 std::cout << "destroy node recurse successful" << std::endl;
							 _reinitializeDummy();
							 std::cout << "clear successful" << std::endl;
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
						 node			*_dummy;

						 node	*_createNewNode(const value_type& val) {
							 node		*new_node;

							 new_node = _node_alloc.allocate(1);
							 _a.construct(&new_node->getVal(), val);
							 new_node->_parent = NULL;
							 new_node->_left = NULL;
							 new_node->_right = NULL;
							 return new_node;
						 }

						 node	*_createDefaultNode(const key_type& k) {
							 node		*new_node;
							 value_type	defaultVal(k, mapped_type());

							 new_node = _node_alloc.allocate(1);
							 _a.construct(&new_node->getVal(), defaultVal);
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

						 mapped_type&	_atRecurse(node *root, const key_type& k) {
							 if (root != NULL) {
								 if (k == root->getKey())
									 return root->getData();
								 else if (_comp(k, root->getKey())) {
									 if (root->_left != NULL) {
										 return this->_atRecurse(root->_left, k);
									 } else {
										 return _insertNewDefaultNodeLeft(root, k);
									 }
								 } else {
									 if (root->_right != NULL) {
										 return this->_atRecurse(root->_right, k);
									 } else {
										 return _insertNewDefaultNodeRight(root, k);
									 }
								 }
							 }

							 node		*newNode = _createDefaultNode(k);
							 newNode->_parent = root;
							 newNode->_left = NULL;
							 newNode->_right = NULL;
							 newNode->_color = RED;
							 _size += 1;
							 _head = newNode;
							 return newNode->getData();
						 }

						 mapped_type&	_insertNewDefaultNodeLeft(node *root, const key_type& k) {
							 node	*newNode = _createDefaultNode(k);

							 root->_left = newNode;

							 newNode->_parent = root;
							 newNode->_left = NULL;
							 newNode->_right = NULL;
							 newNode->_color = RED;
							 _insertRepairTree(newNode);
							 _size += 1;

							 _head = newNode;
							 while (_head->_parent != NULL) {
								 _head = _head->_parent;
							 }
							 return newNode->getData();
						 }

						 mapped_type&	_insertNewDefaultNodeRight(node *root, const key_type& k) {
							 node	*newNode = _createDefaultNode(k);

							 root->_right = newNode;

							 newNode->_parent = root;
							 newNode->_left = NULL;
							 newNode->_right = NULL;
							 newNode->_color = RED;
							 _insertRepairTree(newNode);
							 _size += 1;

							 _head = newNode;
							 while (_head->_parent != NULL) {
								 _head = _head->_parent;
							 }
							 return newNode->getData();
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

						 node		*_findReplacementNode(node *nodeToDelete) {
							 // node has 2 children
							 if (nodeToDelete->_left != NULL && nodeToDelete->_right != NULL)
								 return nodeToDelete->_right->selectLeftMost();

							 // node is leaf
							 if (nodeToDelete->_left == NULL && nodeToDelete->_right == NULL)
								 return NULL;

							 // node has single child
							 if (nodeToDelete->_left != NULL)
								 return nodeToDelete->_left;
							 else
								 return nodeToDelete->_right;
						 }

						 node		*_deleteInternal(iterator position) {
							 node		*nodeToDelete = _getPtrFromIterator(position);
							 node		*replacementNode = _findReplacementNode(nodeToDelete);
							 node		*parent = nodeToDelete->_parent;

							 bool		bothNodesBlack =
								 (replacementNode == NULL || replacementNode->_color == BLACK) &&
								 nodeToDelete->_color == BLACK;

							 _modifyDummy(position);

							 if (replacementNode == NULL) {
								 return _targetNodeIsLeaf(nodeToDelete, parent, bothNodesBlack);
							 }
							 if (nodeToDelete->_left == NULL || nodeToDelete->_right == NULL) {
								 return _targetNodeHasOneChild(nodeToDelete, replacementNode, parent, bothNodesBlack);
							 }

							 // nodeToDelete has two children, take value with successor and recurse
							 nodeToDelete->swap(replacementNode);
							 return _deleteInternal(iterator(replacementNode));
						 }

						 node			*_targetNodeHasOneChild(node *nodeToDelete, node *replacementNode,
								 node *parent, bool bothNodesBlack) {
							 if (nodeToDelete == _head) {
								 // if target node is root, assign value of replacementNode to
								 // root, delete replacementNode instead.
								 std::cout << "About to swap values of root with replacement node" << std::endl;
								 nodeToDelete->swap(replacementNode);
								 std::cout << "replacementNode, which should now be head: " << std::endl;
								 print_node(replacementNode);
								 _head = replacementNode;
								 replacementNode->_right = NULL;
								 replacementNode->_left = NULL;
								 return nodeToDelete;
							 } else {
								 if (nodeToDelete == parent->_left)
									 parent->_left = replacementNode;
								 else
									 parent->_right = replacementNode;
								 replacementNode->_parent = parent;
								 if (bothNodesBlack)
									 _fixDoubleBlack(replacementNode);
								 else
									 replacementNode->_color = BLACK;
								 return nodeToDelete;
							 }
						 }

						 node			*_targetNodeIsLeaf(node *nodeToDelete, node *parent, bool bothNodesBlack) {
							 if (nodeToDelete == _head) {
								 std::cout << "Target node is head." << std::endl;
								 _head = NULL;
								 return nodeToDelete;
							 }
							 if (bothNodesBlack) {
								 _fixDoubleBlack(nodeToDelete);
							 }
							 else {
								 // if nodeToDelete is red, make sibling red
								 if (nodeToDelete->getSibling() != NULL)
									 nodeToDelete->getSibling()->_color = RED;
							 }
							 if (nodeToDelete == parent->_left)
								 parent->_left = NULL;
							 else
								 parent->_right = NULL;
							 return nodeToDelete;
						 }

						 void			_fixDoubleBlack(node *n) {
							 if (n == _head)
								 return ;
							 node		*sibling = n->getSibling();
							 node		*parent = n->_parent;
							 if (sibling == NULL)
								 _fixDoubleBlack(parent);
							 else {
								 if (sibling->_color == RED)
									 _siblingIsRed(n, sibling, parent);
								 else if (sibling->_color == BLACK)
									 _siblingIsBlack(sibling, parent);
							 }
						 }

						 void			_siblingIsRed(node *n, node *sibling, node *parent) {
							 parent->_color = RED;
							 sibling->_color = BLACK;
							 if (sibling == parent->_left) {
								 parent->rotateRight();
								 if (parent == _head)
									 _head = sibling;
							 }
							 else {
								 parent->rotateLeft();
								 if (parent == _head)
									 _head = sibling;
							 }
							 _fixDoubleBlack(n);
						 }

						 void			_siblingIsBlack(node *sibling, node *parent) {
							 if (sibling->hasRedChild())
								 _blackSiblingWithRedChild(sibling, parent);
							 else
								 _blackSiblingWithTwoBlackChildren(sibling, parent);
						 }

						 void		_blackSiblingWithRedChild(node *sibling, node *parent) {
							 if (sibling->_left != NULL && sibling->_left->_color == RED) {
								 // left child is red
								 if (sibling == parent->_left) {
									 sibling->_left->_color = sibling->_color;
									 sibling->_color = parent->_color;
									 parent->rotateRight();
									 if (parent == _head)
										 _head = sibling;
								 } else {
									 sibling->_left->_color = parent->_color;
									 sibling->rotateRight();
									 parent->rotateLeft();
									 if (parent == _head) {
										 while (_head->_parent != NULL)
											 _head = _head->_parent;
									 }
								 }
							 } else {
								 // right child is red
								 if (sibling == parent->_left) {
									 sibling->_right->_color = parent->_color;
									 sibling->rotateLeft();
									 parent->rotateRight();
									 if (parent == _head) {
										 while (_head->_parent != NULL)
											 _head = _head->_parent;
									 }
								 } else {
									 sibling->_right->_color = sibling->_color;
									 sibling->_color = parent->_color;
									 parent->rotateLeft();
									 if (parent == _head)
										 _head = sibling;
								 }
							 }
							 parent->_color = BLACK;
						 }

						 void		_blackSiblingWithTwoBlackChildren(node *sibling, node *parent) {
							 sibling->_color = RED;
							 if (parent->_color == BLACK)
								 _fixDoubleBlack(parent);
							 else
								 parent->_color = BLACK;
						 }

						 // node		*_deleteTargetNode(node *n) {
							//  if (n->_left == NULL && n->_right == NULL)
							// 	 return _targetNodeIsLeaf(n);
							//  else if (n->_left == NULL)
							// 	 return _targetNodeHasRightChild(n);
							//  else if (n->_right == NULL)
							// 	 return _targetNodeHasLeftChild(n);
							//  else
							// 	 return _targetNodeHasTwoChildren(n);
						 // }
                         //
						 // node		*_targetNodeIsLeaf(node *n) {
							//  if (n->_parent == NULL)
							// 	 return n;
							//  if (n == n->_parent->_left)
							// 	 n->_parent->_left = NULL;
							//  else if (n == n->_parent->_right)
							// 	 n->_parent->_right = NULL;
							//  return n;
						 // }
                         //
						 // node		*_targetNodeHasLeftChild(node *n) {
							//  if (n->_parent != NULL) {
							// 	 if (n->_parent->_right == n)
							// 		 n->_parent->_right = n->_left;
							// 	 else if (n->_parent->_left == n)
							// 		 n->_parent->_left = n->_left;
							//  }
							//  return n;
						 // }
                         //
						 // node		*_targetNodeHasRightChild(node *n) {
							//  if (n->_parent != NULL) {
							// 	 if (n->_parent->_right == n)
							// 		 n->_parent->_right = n->_right;
							// 	 else if (n->_parent->_left == n)
							// 		 n->_parent->_left = n->_right;
							//  }
							//  return n;
						 // }

						 // node		*_targetNodeHasTwoChildren(node *n) {
							//  node		*successor = n->_right->selectLeftMost();
                         //
							//  n->getVal() = successor->getVal();
							//  return _deleteTargetNode(successor);
						 // }

						 // If the node to be deleted is leftmost or rightmost, we
						 // have to modify the dummy so that it doesn't point at a
						 // node that's about to freed
						 void		_modifyDummy(iterator position) {
							 node		*n = _getPtrFromIterator(position);

							 if (_size == 1) { // Last node is about to be deleted
								 _dummy->_right = _dummy;
								 _dummy->_left = _dummy;
							 }
							 if (n == _dummy->_right) {
								 iterator 	tmp = position;
								 tmp++;
								 node		*nextNodeRight = _getPtrFromIterator(tmp);
								 _dummy->_right = nextNodeRight;
							 }
							 if (n == _dummy->_left) {
								 iterator	tmp = position;
								 tmp--;
								 node		*nextNodeLeft = _getPtrFromIterator(tmp);
								 _dummy->_left = nextNodeLeft;
							 }
							 std::cout << "Modified dummy: ";
							 print_node(_dummy);
						 }

						 node		*_createDummyNode(void) {
							 node	*new_dummy;

							 new_dummy = _node_alloc.allocate(1);
							 new_dummy->_parent = 0;
							 new_dummy->_left = new_dummy;
							 new_dummy->_right = new_dummy;
							 new_dummy->_color = DUMMY;
							 return new_dummy;
						 }

						 void		_destroyDummy(node *target) {
							 _node_alloc.deallocate(target, 1);
						 }

						 void		_reinitializeDummy(void) {
							 _dummy->_left = _dummy;
							 _dummy->_right = _dummy;
						 }

						 void		_disconnectDummy(void) {
							 if (_dummy->_right == _dummy && _dummy->_left == _dummy)
								 return ;
							 std::cout << "dummy->_right = " << _dummy->_right << 
								 ", dummy->_left = " << _dummy->_left << std::endl;
							 _dummy->_right->_left = NULL;
							 _dummy->_left->_right = NULL;
						 }

						 void		_reconnectDummy(void) {
							 if (_size == 1) {
								 if (_head == NULL) {
									 _dummy->_left = _dummy;
									 _dummy->_right = _dummy;
								 } else {
									 _dummy->_left = _head;
									 _dummy->_right = _head;
								 }
								 return ;
							 }
							 if (_dummy->_right->_left != NULL) {
								 _dummy->_right = _dummy->_right->_left; // Connect dummy to new leftmost
							 }
							 _dummy->_right->_left = _dummy;
							 if (_dummy->_left->_right != NULL) {
								 _dummy->_left = _dummy->_left->_right; // Connect dummy to new rightmost
							 }
							 _dummy->_left->_right = _dummy;
						 }
				 };
}

#endif
