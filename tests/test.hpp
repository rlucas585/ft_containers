/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.hpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/20 13:51:08 by rlucas        #+#    #+#                 */
/*   Updated: 2021/02/21 11:11:34 by rlucas        ########   odam.nl         */
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

#endif
