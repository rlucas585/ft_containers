/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map.cpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/29 08:56:11 by rlucas        #+#    #+#                 */
/*   Updated: 2021/02/21 17:30:21 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP 

#include <functional>
#include "pair.hpp"

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
			 typename A = std::allocator<T> >
				 class map {
					 public:
						 typedef Key								key_type;
						 typedef T									mapped_type;
						 typedef pair<const key_type, mapped_type>	value_type;
						 typedef A									allocator_type;
						 typedef Compare							key_compare;
						 // TODO typedef a value_compare at some point
						 // TODO typedef a map iterator once created, and reverse iterator
						 typedef typename allocator_type::reference			reference;
						 typedef typename allocator_type::const_reference	const_reference;
						 typedef typename allocator_type::pointer			pointer;
						 typedef typename allocator_type::const_pointer		const_pointer;
						 typedef typename allocator_type::size_type			size_type;
						 typedef typename allocator_type::difference_type	difference_type;

					 public:
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
								 Key		&getKey(void) {
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
								 value_type	&getVal(void) {
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
									 if (p = NULL)
										 return NULL;
									 if (this == p->_left)
										 return p->_right;
									 else
										 return p->_left;
								 }
								 node		*getUncle(void) {
									 node		*p = _parent;
									 if (p = NULL)
										 return NULL;
									 return p->getSibling();
								 }

								 // Rotations
								 // void		rotateLeft(void) {
								 //  node		*nnew = _right;
								 //  node		*p = _parent;
								 //  if (nnew == NULL)	// Do nothing if leaf is sibling
								 // 	 return ;
								 //
								 //  _right = nnew->_left;
								 // }

							 public:
								 node		*_parent;
								 node		*_left;
								 node		*_right;
								 t_color	_color;
								 value_type	_val;

								 node(void) {}
						 };

					 public:
						 typedef	std::allocator<node>					node_allocator;

					 public:
						 map(const key_compare& comp = key_compare(),
								 const allocator_type& alloc = allocator_type())
							 : _head(NULL), _size(0), _comp(comp), _a(alloc), _node_alloc() {

						 }

						 size_type	size(void) const {
							 return _size;
						 }

						 // TODO change from void to correct return type
						 void	insert(const value_type& val) {
							 if (_head == NULL) {

							 }
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
							 new_node.parent = NULL;
							 new_node.left = NULL;
							 new_node.right = NULL;
							 return new_node;
						 }
				 };
}

#endif
