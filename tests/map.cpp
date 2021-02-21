/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map.cpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/21 15:01:14 by rlucas        #+#    #+#                 */
/*   Updated: 2021/02/21 17:30:55 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <gtest/gtest.h>

#include <stdexcept>
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <iomanip>

#include "../src/map.hpp"
#include "../src/pair.hpp"
#include "test_fixture_classes.hpp"
#include "Example.hpp"
#include "test.hpp"

TEST(development_test, nodes_test) {
	ft::map<int, std::string>		aMap;

	(void)aMap;
	std::cout << aMap.size() << std::endl;
	ASSERT_EQ(aMap.size(), 0);
}

TEST(development_test, raw_nodes_test) {

}

TEST(development_test, pair_test) {
	ft::pair<int, int>		example;

	std::cout << "(" << example.first << ", " << example.second << ")" << std::endl;

	ft::pair<int, std::string>	example2 = ft::make_pair(5, "Devon");

	std::cout << "(" << example2.first << ", " << example2.second << ")" << std::endl;
}
