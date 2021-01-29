/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map.cpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/29 08:56:11 by rlucas        #+#    #+#                 */
/*   Updated: 2021/01/29 09:07:51 by rlucas        ########   odam.nl         */
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
						 };

				 };
}

#endif
