/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.hpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/20 13:51:08 by rlucas        #+#    #+#                 */
/*   Updated: 2021/02/26 19:26:02 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_HPP
#define TEST_HPP

#define ON true
#define OFF false

#define PRINTED_OUTPUT OFF

#include <string>
#include <vector>
#include "Example.hpp"
#include "../src/vector.hpp"

void	addition_func(int &val);
void	addition_func(std::string &s);
void	addition_func(Example &e);
void	subtraction_func(int &val);
void	subtraction_func(std::string &s);
void	subtraction_func(Example &e);
void	multiplication_func(int &val);
void	multiplication_func(std::string &s);
void	multiplication_func(Example &e);
void	initialise_scrap_vector(std::vector<int>& vec);
void	initialise_scrap_vector(std::vector<std::string>& list);
void	initialise_scrap_vector(std::vector<Example>& list);
bool	predicate_func(int const& n);
bool	predicate_func(std::string const& s);
bool	predicate_func(Example const& e);
bool	binary_predicate_func(int const& n, int const& n2);
bool	binary_predicate_func(std::string const& s, std::string const& s2);
bool	binary_predicate_func(Example const& e, Example const& e2);
bool	moreThanFunc(int const& n, int const& n2);
bool	moreThanFunc(std::string const& s, std::string const& s2);
bool	moreThanFunc(Example const& e, Example const& e2);
void	initialise_default_vector(ft::vector<int>& vec, std::vector<int>& realvec);
void	initialise_default_vector(ft::vector<std::string>& vec, std::vector<std::string>& realvec);
void	initialise_default_vector(ft::vector<Example>& vec, std::vector<Example>& realvec);
void	addition_to_vector(ft::vector<int>& vec, std::vector<int>& realvec);
void	addition_to_vector(ft::vector<std::string>& vec, std::vector<std::string>& realvec);
void	addition_to_vector(ft::vector<Example>& vec, std::vector<Example>& realvec);

#endif
