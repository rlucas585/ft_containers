/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <ryanl585codam@gmail.com>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/06 12:49:55 by rlucas        #+#    #+#                 */
/*   Updated: 2021/01/29 09:22:20 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>

#include "colors.hpp"
#include "utils.hpp"
#include "test.hpp"

/*
 * @param1 = Boolean to run integer tests
 * @param2 = Boolean to run std::string tests
 * @param3 = Boolean to run Example class tests
*/

int		main(void)
{
	vector_tests(true, false, false);
	// list_tests(true, false, false);

	return (0);
}
