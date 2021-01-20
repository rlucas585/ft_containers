/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.cpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/06 23:05:51 by rlucas        #+#    #+#                 */
/*   Updated: 2021/01/20 11:01:33 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "colors.hpp"
#include "vector.hpp"
#include <iostream>
#include <iomanip>
#include <string>

void	print_divider(std::string color, std::string message)
{
	std::cout << BOLD << color << "--------------------------------------" <<
		std::endl << message << std::endl <<
		"--------------------------------------" << NORMAL << std::endl;
}

void	print_info(std::string color, std::string message) {
	std::cout << BOLD << color << message << NORMAL << std::endl;
}

void	print_line(std::string color)
{
	std::cout << BOLD << color << "--------------------------------------"
		<< NORMAL << std::endl;
}

template <typename T>
void	try_index(ft::vector<T> &vec, size_t i) {
	T		val;
	try {
		val = vec[i];
		std::cout << "Index " << i << ": " << val << std::endl;
	} catch (std::exception &e) {
		std::cerr << "Error " << ": " << e.what() << std::endl;
	}
}
