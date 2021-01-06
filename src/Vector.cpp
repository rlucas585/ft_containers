/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Vector.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <ryanl585codam@gmail.com>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/06 12:52:13 by rlucas        #+#    #+#                 */
/*   Updated: 2021/01/06 16:25:32 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Vector.hpp"

Vector::Vector(void) {
	return ;
}

Vector::Vector(Vector const &src) {
	*this = src;
	return ;
}

Vector::~Vector(void) {
	return ;
}

Vector	&Vector::operator=(Vector const &rhs) {
	// Should be something relevant here

	return (*this);
}
