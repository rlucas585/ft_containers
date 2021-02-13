/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/13 17:58:24 by rlucas        #+#    #+#                 */
/*   Updated: 2021/02/13 19:11:31 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <gtest/gtest.h>

#include <stdexcept>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>

#include "../src/vector.hpp"
#include "test_fixture_classes.hpp"

void	initialise_default_vector(ft::vector<int>& vec, std::vector<int>& realvec) {
	for (unsigned int i = 5; i <= 30; i += 5) {
		vec.push_back(i);
		realvec.push_back(i);
	}
}

void	initialise_default_vector(ft::vector<std::string>& vec, std::vector<std::string>& realvec) {
	std::vector<std::string>		newvals;

	newvals.push_back("Lorem");
	newvals.push_back("ipsum");
	newvals.push_back("dolor");
	newvals.push_back("amet,");
	newvals.push_back("sit long long long long long long long long long long long long long long");
	newvals.push_back("adipiscing elit. Donec aliquam tempus orci. Pellentesque "
			"bibendum consequat mauris, id pharetra urna molestie eget. Quisque a vulputate dolor.");
	for (size_t i = 0; i != newvals.size(); i++) {
		vec.push_back(newvals[i]);
		realvec.push_back(newvals[i]);
	}
}

TYPED_TEST_CASE(vector_tester, Implementations);

TYPED_TEST(vector_tester, empty_test) {
	ft::vector<TypeParam>	vec;
	std::vector<TypeParam>	realvec;

	ASSERT_EQ(vec.empty(), realvec.empty());
}

TYPED_TEST(vector_tester, push_back_test) {
	ft::vector<TypeParam>	vec;
	std::vector<TypeParam>	realvec;
	std::vector<TypeParam>	realvec2;

	initialise_default_vector(vec, realvec);

	ASSERT_EQ(vec.size(), realvec.size());
	for (size_t i = 0; i != vec.size(); i++)
		ASSERT_EQ(vec[i], realvec[i]);
}
