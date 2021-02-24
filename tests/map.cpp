/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map.cpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/21 15:01:14 by rlucas        #+#    #+#                 */
/*   Updated: 2021/02/24 14:18:06 by rlucas        ########   odam.nl         */
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

TEST(development_test, initialisation_test) {
	ft::map<int, std::string>		aMap;

	(void)aMap;
	std::cout << aMap.size() << std::endl;
	ASSERT_EQ(aMap.size(), 0);
}

TEST(development_test, insert_test) {
	ft::map<int, std::string>		aMap;

	aMap.insert(ft::pair<int, std::string>(3, "hello"));
	ASSERT_EQ(aMap.size(), 1);
}

TEST(development_test, basic_iterator_test) {
	ft::map<int, std::string>				aMap;

	aMap.insert(ft::pair<int, std::string>(5, "Leeds"));
	ft::pair<int, std::string>				head = aMap.getHead();
	std::cout << "Head: " << std::endl;
	std::cout << "(" << head.first << ", " << head.second << ")" << std::endl;
	std::cout << "------------" << std::endl;
	aMap.insert(ft::pair<int, std::string>(3, "Arsenal"));
	head = aMap.getHead();
	std::cout << "Head: " << std::endl;
	std::cout << "(" << head.first << ", " << head.second << ")" << std::endl;
	std::cout << "------------" << std::endl;
	aMap.insert(ft::pair<int, std::string>(-1, "Man Utd"));
	head = aMap.getHead();
	std::cout << "Head: " << std::endl;
	std::cout << "(" << head.first << ", " << head.second << ")" << std::endl;
	std::cout << "------------" << std::endl;
	aMap.insert(ft::pair<int, std::string>(15, "Newcastle"));
	head = aMap.getHead();
	std::cout << "Head: " << std::endl;
	std::cout << "(" << head.first << ", " << head.second << ")" << std::endl;
	std::cout << "------------" << std::endl;
	aMap.insert(ft::pair<int, std::string>(12, "Everton"));
	head = aMap.getHead();
	std::cout << "Head: " << std::endl;
	std::cout << "(" << head.first << ", " << head.second << ")" << std::endl;
	std::cout << "------------" << std::endl;
	aMap.insert(ft::pair<int, std::string>(4, "West Brom"));
	ft::map<int, std::string>::iterator		it = aMap.begin();
	aMap.insert(ft::pair<int, std::string>(50, "Netherlands"));
	head = aMap.getHead();
	std::cout << "Head: " << std::endl;
	std::cout << "(" << head.first << ", " << head.second << ")" << std::endl;
	std::cout << "------------" << std::endl;
	aMap.insert(ft::pair<int, std::string>(55, "Germany"));
	head = aMap.getHead();
	std::cout << "Head: " << std::endl;
	std::cout << "(" << head.first << ", " << head.second << ")" << std::endl;
	std::cout << "------------" << std::endl;
	aMap.insert(ft::pair<int, std::string>(45, "France"));
	head = aMap.getHead();
	std::cout << "Head: " << std::endl;
	std::cout << "(" << head.first << ", " << head.second << ")" << std::endl;
	std::cout << "------------" << std::endl;

	ASSERT_TRUE(aMap.validateTree());

	while (it != aMap.end()) {
		std::cout << "(" << (*it).first << ", " << (*it).second << ")" << std::endl;
		it++;
	}
}

TEST(development_test, pair_test) {
	ft::pair<int, int>		example;

	ASSERT_EQ(example.first, 0);
	ASSERT_EQ(example.second, 0);

	ft::pair<int, std::string>	example2 = ft::make_pair(5, "Devon");

	ASSERT_EQ(example2.first, 5);
	ASSERT_EQ(example2.second, "Devon");
}
