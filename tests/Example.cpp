/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Example.cpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/20 11:41:05 by rlucas        #+#    #+#                 */
/*   Updated: 2021/03/10 17:31:24 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Example.hpp"

Example::Example(void) : _name("Default"), _val(0) {
	return ;
}

Example::Example(const char *name, int val) : _name(name), _val(val) {
	return ;
}

Example::Example(Example const &src) {
	*this = src;
}

Example::~Example(void) {
	return ;
}

Example		Example::createWithNameAndValue(const char *name, int val) {
	return Example(name, val);
}

Example	&Example::operator=(Example const &rhs) {
	if (this == &rhs) { return *this; }

	_name = rhs._name;
	_val = rhs._val;
	return *this;
}

std::string const&	Example::getName(void) const {
	return _name;
}

int			const&	Example::getVal(void) const {
	return _val;
}

void				Example::addToName(int n) {
	_name[0] += n;
}

void				Example::subName(int n) {
	_name[0] -= n;
}

void				Example::multName(int n) {
	_name[0] += n;
	if (_name[0] > 125)
		_name[0] = 65;
}

bool				Example::operator==(Example const& other) const {
	return _val == other._val && _name == other._name;
}

bool				Example::operator!=(Example const& other) const {
	return !(*this == other);
}

bool				Example::operator<(Example const& other) const {
	return _name < other._name;
}

bool				Example::operator<=(Example const& other) const {
	return !(other < *this);
}

bool				Example::operator>(Example const& other) const {
	return other < *this;
}

bool				Example::operator>=(Example const& other) const {
	return !(*this < other);
}

void				Example::operator+=(Example const& other) {
	this->_val += other._val;
}

std::ostream	&operator<<(std::ostream &o, Example const &i) {
	o << "{ Name: " << i.getName() << ", Value: " << i.getVal() << " }";
	return o;
}
