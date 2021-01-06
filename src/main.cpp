/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <ryanl585codam@gmail.com>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/06 12:49:55 by rlucas        #+#    #+#                 */
/*   Updated: 2021/01/06 14:56:40 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "colors.hpp"
#include "utils.hpp"

void	example_test_function(void)
{
	print_divider(CYAN, "Test name");

	// Tests can go here.

	print_line(CYAN);
}

int		main(void)
{
	example_test_function();

	return (0);
}
