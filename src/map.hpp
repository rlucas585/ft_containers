/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map.cpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/29 08:56:11 by rlucas        #+#    #+#                 */
/*   Updated: 2021/02/13 15:31:29 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP 

#include <functional>

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
		RED,
	}				t_color;

	template <typename Key,
			 typename T,
			 typename Compare = std::less<Key>,
			 typename A = std::allocator<T> >
				 class map {
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
								 Key		&getKey(void) {
									 return _key;
								 }
								 void		setKey(Key key) {
									 _key = key;
								 }
								 T			&getData(void) {
									 return _data;
								 }
								 const T	&getData(void) const {
									 return _data;
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
									 if (_parent == nullptr)
										 return nullptr;
									 return _parent->_parent;
								 }
								 node		*getSibling(void) {
									 node		*p = _parent;
									 if (p = nullptr)
										 return nullptr;
									 if (this == p->_left)
										 return p->_right;
									 else
										 return p->_left;
								 }
								 node		*getUncle(void) {
									 node		*p = _parent;
									 if (p = nullptr)
										 return nullptr;
									 return p->getSibling();
								 }

								 // Rotations
								 void		rotateLeft(void) {
									 node		*nnew = _right;
									 node		*p = _parent;
									 if (nnew == nullptr)	// Do nothing if leaf is sibling
										 return ;

									 _right = nnew->_left;
									 nnew->left = 
								 }

							 private:
								 node		*_parent;
								 node		*_left;
								 node		*_right;
								 t_color	_color;
								 Key		_key;
								 T			_data;

								 node(void) {}
						 };

				 };
}

#endif
