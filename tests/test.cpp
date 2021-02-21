/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/20 13:51:39 by rlucas        #+#    #+#                 */
/*   Updated: 2021/02/21 14:31:06 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"

void	addition_func(int &val) {
	val += 2;
}

void	addition_func(std::string &s) {
	s[0] += 2;
}

void	addition_func(Example &e) {
	e.addToName(2);
}

void	subtraction_func(int &val) {
	val -= 1;
}

void	subtraction_func(std::string &s) {
	s[0] -= 1;
}

void	subtraction_func(Example &e) {
	e.subName(2);
}

void	multiplication_func(int &val) {
	val *= 3;
}

void	multiplication_func(std::string &s) {
	s[0] += 8;
	if (s[0] > 125)
		s[0] = 65;
}

void	multiplication_func(Example &e) {
	e.multName(8);
}

void	initialise_scrap_vector(std::vector<int>& vec) {
	for (unsigned int i = 7; i <= 77; i += 6) {
		vec.push_back(i);
		if (i == 13)
			vec.push_back(15);
	}
}

void	initialise_scrap_vector(std::vector<std::string>& vec) {
	for (unsigned int i = 0; i <= 3; i++) {
		vec.push_back("container");
		vec.push_back("hello");
		vec.push_back("there");
		vec.push_back("vector");
	}
}

void	initialise_scrap_vector(std::vector<Example>& vec) {
	for (unsigned int i = 0; i <= 3; i++) {
		vec.push_back(Example::createWithNameAndValue("Avdol", 15));
		vec.push_back(Example::createWithNameAndValue("Giorno", 3));
		vec.push_back(Example::createWithNameAndValue("Iggy", 11));
		vec.push_back(Example::createWithNameAndValue("Kakyoin", 8));
		vec.push_back(Example::createWithNameAndValue("Polnareff", 2));
	}
}

bool	predicate_func(int const& n) {
	return n % 2 == 0;
}

bool	predicate_func(std::string const& s) {
	return s.find("n") != std::string::npos;
}

bool	predicate_func(Example const& e) {
	return e.getName().find("n") != std::string::npos;
}

bool	binary_predicate_func(int const& n, int const& n2) {
	return n == n2;
}

bool	binary_predicate_func(std::string const& s, std::string const& s2) {
	return s == s2;
}

bool	binary_predicate_func(Example const& e, Example const& e2) {
	return e == e2;
}

bool	moreThanFunc(int const& n, int const& n2) {
	return n > n2;
}

bool	moreThanFunc(std::string const& s, std::string const& s2) {
	return s > s2;
}

bool	moreThanFunc(Example const& e, Example const& e2) {
	return e > e2;
}
