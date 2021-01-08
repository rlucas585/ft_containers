/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Vector.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <ryanl585codam@gmail.com>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/06 12:52:13 by rlucas        #+#    #+#                 */
/*   Updated: 2021/01/08 10:32:27 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Vector.hpp"

template <typename T, typename A = std::allocator<T> >
Vector<T, A>::Vector(void) {
	return ;
}

// template <typename T, typename Allocator>
// Vector<T>::Vector(void) {
// 	return ;
// }

void	test(void) {
	std::cout << "Yep, this file is compiled and included" << std::endl;
}

// Vector::Vector(Vector const &src) {
// 	*this = src;
// 	return ;
// }
//
// Vector::~Vector(void) {
// 	return ;
// }
//
// Vector	&Vector::operator=(Vector const &rhs) {
// 	(void)rhs;
//
// 	return (*this);
// }
