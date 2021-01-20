/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.cpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/06 23:05:51 by rlucas        #+#    #+#                 */
/*   Updated: 2021/01/20 10:53:52 by rlucas        ########   odam.nl         */
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
