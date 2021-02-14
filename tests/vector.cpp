/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/13 17:58:24 by rlucas        #+#    #+#                 */
/*   Updated: 2021/02/14 22:34:31 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <gtest/gtest.h>

#include <stdexcept>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

#include "../src/vector.hpp"
#include "test_fixture_classes.hpp"

#define ON true
#define OFF false

#define PRINTED_OUTPUT OFF

void	initialise_default_vector(ft::vector<int>& vec, std::vector<int>& realvec) {
	for (unsigned int i = 5; i <= 30; i += 5) {
		vec.push_back(i);
		realvec.push_back(i);
	}
}

void	initialise_scrap_vector(std::vector<int>& vec) {
	for (unsigned int i = 7; i <= 77; i += 6) {
		vec.push_back(i);
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

void	initialise_scrap_vector(std::vector<std::string>& vec) {
	for (unsigned int i = 0; i <= 3; i++) {
		vec.push_back("hello");
		vec.push_back("there");
		vec.push_back("vector");
		vec.push_back("container");
	}
}

void	addition_func(int &val) {
	val += 2;
}

void	addition_func(std::string &s) {
	s[0] += 2;
}

void	subtraction_func(int &val) {
	val -= 1;
}

void	subtraction_func(std::string &s) {
	s[0] -= 1;
}

void	multiplication_func(int &val) {
	val *= 3;
}

void	multiplication_func(std::string &s) {
	s[0] += 8;
	if (s[0] > 125)
		s[0] = 65;
}

void	addition_to_vector(ft::vector<int>& vec, std::vector<int>& realvec) {
	vec.front() += 1;
	realvec.front() += 1;
}

void	addition_to_vector(ft::vector<std::string>& vec, std::vector<std::string>& realvec) {
	std::string&	s = vec.front();
	std::string&	reals = realvec.front();
	s[0] += 1;
	reals[0] += 1;
}

void	subtraction_to_vector(ft::vector<int>& vec, std::vector<int>& realvec) {
	vec.front() -= 1;
	realvec.front() -= 1;
}

void	subtraction_to_vector(ft::vector<std::string>& vec, std::vector<std::string>& realvec) {
	std::string&	s = vec.front();
	std::string&	reals = realvec.front();
	s[0] -= 1;
	reals[0] -= 1;
}

template <typename Vec>
std::string	vec_to_str(Vec const& vec) {
	std::stringstream	ss;

	ss << "[";
	for (unsigned int i = 0; i < vec.size(); i++) {
		if (i == vec.size() - 1)
			ss << vec[i];
		else
			ss << vec[i] << ", ";
	}
	ss << "]";
	return ss.str();
}

template <typename Vec>
void	print_vec_info(Vec const& vec, const char *name) {
	std::string		vecStr = vec_to_str(vec);
	if (vecStr.size() >= 30)
		vecStr.erase(vecStr.begin() + 30, vecStr.end());

	std::cout << std::setw(10) << std::right << std::setfill(' ')
		<< name;
	std::cout << "|";
	std::cout << std::setw(10) << std::right << std::setfill(' ')
		<< vec.size();
	std::cout << "|";
	std::cout << std::setw(10) << std::right << std::setfill(' ')
		<< vec.capacity();
	std::cout << "|";
	std::cout << std::setw(30) << std::right << std::setfill(' ')
		<< vecStr;
	std::cout << "|";
	std::cout << std::endl;
}

template <typename T>
void	print_table(ft::vector<T> const& vec, std::vector<T> const& realvec) {
	std::cout <<
		"----------------------------------------------------------------"
		<< std::endl;
	std::cout << std::setw(10) << std::right << std::setfill(' ')
		<< "name";
	std::cout << "|";
	std::cout << std::setw(10) << std::right << std::setfill(' ')
		<< "size";
	std::cout << "|";
	std::cout << std::setw(10) << std::right << std::setfill(' ')
		<< "capacity";
	std::cout << "|";
	std::cout << std::setw(30) << std::right << std::setfill(' ')
		<< "content";
	std::cout << "|";
	std::cout << std::endl;
	std::cout << "----------------------------------------------------------------" << std::endl;
	print_vec_info(vec, "vec");
	print_vec_info(realvec, "realvec");
	std::cout << "----------------------------------------------------------------" << std::endl;
}

template <typename T>
void	testSizeAndContent(ft::vector<T>const& vec, std::vector<T>const& realvec) {
	if (PRINTED_OUTPUT)
		print_table(vec, realvec);
	ASSERT_EQ(vec.size(), realvec.size());
	ASSERT_EQ(vec.capacity(), realvec.capacity());
	for (size_t i = 0; i != vec.size(); i++)
		ASSERT_EQ(vec[i], realvec[i]);
}

TYPED_TEST_CASE(vector_tester, Implementations);

TYPED_TEST(vector_tester, empty_test) {
	ft::vector<TypeParam>	vec;
	std::vector<TypeParam>	realvec;

	ASSERT_TRUE(vec.empty());
	ASSERT_TRUE(realvec.empty());
	ASSERT_EQ(vec.empty(), realvec.empty());

	initialise_default_vector(vec, realvec);

	ASSERT_EQ(vec.empty(), realvec.empty());
	ASSERT_FALSE(vec.empty());
	ASSERT_FALSE(realvec.empty());
}

TYPED_TEST(vector_tester, push_back_test) {
	ft::vector<TypeParam>	vec;
	std::vector<TypeParam>	realvec;
	initialise_default_vector(vec, realvec);

	for (size_t i = 0; i != vec.size(); i++)
		ASSERT_EQ(vec[i], realvec[i]);
}

TYPED_TEST(vector_tester, size_test) {
	ft::vector<TypeParam>	vec;
	std::vector<TypeParam>	realvec;
	initialise_default_vector(vec, realvec);

	ASSERT_EQ(vec.size(), realvec.size());
}

TYPED_TEST(vector_tester, max_size_test) {
	ft::vector<TypeParam>	vec;
	std::vector<TypeParam>	realvec;
	initialise_default_vector(vec, realvec);

	ASSERT_EQ(vec.max_size(), realvec.max_size());
}

TYPED_TEST(vector_tester, element_access_test) {
	ft::vector<TypeParam>	vec;
	std::vector<TypeParam>	realvec;
	initialise_default_vector(vec, realvec);

	for (size_t i = 0; i != vec.size(); i++)
		ASSERT_EQ(vec[i], realvec[i]);
}

TYPED_TEST(vector_tester, resize_test) {
	ft::vector<TypeParam>	vec;
	std::vector<TypeParam>	realvec;
	std::vector<TypeParam>	scrapVec;
	initialise_default_vector(vec, realvec);
	initialise_scrap_vector(scrapVec);

	testSizeAndContent(vec, realvec);

	vec.resize(vec.size() + 3);
	realvec.resize(realvec.size() + 3);

	testSizeAndContent(vec, realvec);

	vec.resize(vec.size() + 3, scrapVec[3]);
	realvec.resize(realvec.size() + 3, scrapVec[3]);

	testSizeAndContent(vec, realvec);
}

TYPED_TEST(vector_tester, capacity_test) {
	ft::vector<TypeParam>	vec;
	std::vector<TypeParam>	realvec;
	std::vector<TypeParam>	scrapVec;
	initialise_default_vector(vec, realvec);
	initialise_scrap_vector(scrapVec);

	ASSERT_EQ(vec.capacity(), realvec.capacity());
	vec.resize(vec.size() + 20);
	realvec.resize(realvec.size() + 20);
	ASSERT_EQ(vec.capacity(), realvec.capacity());
}

TYPED_TEST(vector_tester, at_test) {
	ft::vector<TypeParam>	vec;
	std::vector<TypeParam>	realvec;
	initialise_default_vector(vec, realvec);

	ASSERT_THROW(vec.at(12), std::exception);
	ASSERT_THROW(realvec.at(12), std::exception);
	ASSERT_NO_THROW(vec.at(3));
	ASSERT_NO_THROW(realvec.at(3));

	for (size_t i = 0; i != vec.size(); i++)
		ASSERT_EQ(vec.at(i), realvec.at(i));
}

TYPED_TEST(vector_tester, front_back_test) {
	ft::vector<TypeParam>	vec;
	std::vector<TypeParam>	realvec;

	initialise_default_vector(vec, realvec);
	ASSERT_EQ(vec.front(), realvec.front());
	ASSERT_EQ(vec.back(), realvec.back());
}

TYPED_TEST(vector_tester, pop_back_test) {
	ft::vector<TypeParam>	vec;
	std::vector<TypeParam>	realvec;
	initialise_default_vector(vec, realvec);

	testSizeAndContent(vec, realvec);
	vec.pop_back();
	realvec.pop_back();
	testSizeAndContent(vec, realvec);
	while (!vec.empty()) {
		vec.pop_back();
		realvec.pop_back();
	}
	testSizeAndContent(vec, realvec);
	ASSERT_TRUE(vec.empty());
	ASSERT_TRUE(realvec.empty());
}

TYPED_TEST(vector_tester, assign_iterator_test) {
	ft::vector<TypeParam>	vec;
	std::vector<TypeParam>	realvec;
	std::vector<TypeParam>	scrapVec;
	initialise_default_vector(vec, realvec);
	initialise_scrap_vector(scrapVec);

	testSizeAndContent(vec, realvec);

	vec.assign(scrapVec.begin(), scrapVec.end());
	realvec.assign(scrapVec.begin(), scrapVec.end());

	testSizeAndContent(vec, realvec);

	vec.clear();
	realvec.clear();
	ASSERT_EQ(vec.empty(), realvec.empty());

	vec.assign(scrapVec.begin(), scrapVec.end());
	realvec.assign(scrapVec.begin(), scrapVec.end());

	testSizeAndContent(vec, realvec);
}

TYPED_TEST(vector_tester, assign_fill_test) {
	ft::vector<TypeParam>	vec;
	std::vector<TypeParam>	realvec;
	std::vector<TypeParam>	scrapVec;
	initialise_default_vector(vec, realvec);
	initialise_scrap_vector(scrapVec);

	testSizeAndContent(vec, realvec);

	vec.assign(15, scrapVec[3]);
	realvec.assign(15, scrapVec[3]);
	ASSERT_EQ(vec.size(), 15);
	ASSERT_EQ(realvec.size(), 15);

	testSizeAndContent(vec, realvec);
}

TYPED_TEST(vector_tester, insert_single_element_test) {
	ft::vector<TypeParam>	vec;
	std::vector<TypeParam>	realvec;
	std::vector<TypeParam>	scrapVec;
	initialise_default_vector(vec, realvec);
	initialise_scrap_vector(scrapVec);

	testSizeAndContent(vec, realvec);

	ASSERT_EQ(
			*vec.insert(vec.begin() + 2, scrapVec[2]),
			*realvec.insert(realvec.begin() + 2, scrapVec[2])
			);

	testSizeAndContent(vec, realvec);

	ASSERT_EQ(
			*vec.insert(vec.end() - 3, scrapVec[scrapVec.size() - 1]),
			*realvec.insert(realvec.end() - 3, scrapVec[scrapVec.size() - 1])
			);

	testSizeAndContent(vec, realvec);
}

TYPED_TEST(vector_tester, insert_fill_test) {
	ft::vector<TypeParam>	vec;
	std::vector<TypeParam>	realvec;
	std::vector<TypeParam>	scrapVec;
	initialise_default_vector(vec, realvec);
	initialise_scrap_vector(scrapVec);

	testSizeAndContent(vec, realvec);

	vec.insert(vec.begin() + 3, 8, scrapVec[0]);
	realvec.insert(realvec.begin() + 3, 8, scrapVec[0]);

	testSizeAndContent(vec, realvec);
}

TYPED_TEST(vector_tester, insert_range_test) {
	ft::vector<TypeParam>	vec;
	std::vector<TypeParam>	realvec;
	std::vector<TypeParam>	scrapVec;
	initialise_default_vector(vec, realvec);
	initialise_scrap_vector(scrapVec);

	testSizeAndContent(vec, realvec);

	vec.insert(vec.begin() + 3, scrapVec.begin(), scrapVec.end());
	realvec.insert(realvec.begin() + 3, scrapVec.begin(), scrapVec.end());

	testSizeAndContent(vec, realvec);

	vec.insert(vec.begin(), scrapVec.begin() + 4, scrapVec.end() - 2);
	realvec.insert(realvec.begin(), scrapVec.begin() + 4, scrapVec.end() - 2);

	testSizeAndContent(vec, realvec);
}

TYPED_TEST(vector_tester, erase_single_test) {
	ft::vector<TypeParam>	vec;
	std::vector<TypeParam>	realvec;
	initialise_default_vector(vec, realvec);

	testSizeAndContent(vec, realvec);

	ASSERT_EQ(
			*vec.erase(vec.begin()),
			*realvec.erase(realvec.begin())
			);

	testSizeAndContent(vec, realvec);

	ASSERT_EQ(
			*vec.erase(vec.begin() + (vec.size() / 2)),
			*realvec.erase(realvec.begin() + (realvec.size() / 2))
			);

	testSizeAndContent(vec, realvec);
}

TYPED_TEST(vector_tester, erase_range_test) {
	ft::vector<TypeParam>	vec;
	std::vector<TypeParam>	realvec;
	initialise_default_vector(vec, realvec);

	testSizeAndContent(vec, realvec);

	ASSERT_EQ(
			*vec.erase(vec.begin(), vec.end() - 2),
			*realvec.erase(realvec.begin(), realvec.end() - 2)
			);

	testSizeAndContent(vec, realvec);
}

TYPED_TEST(vector_tester, swap_member_test) {
	ft::vector<TypeParam>	vec;
	std::vector<TypeParam>	realvec;
	std::vector<TypeParam>	scrapVec;
	initialise_default_vector(vec, realvec);
	initialise_scrap_vector(scrapVec);

	ft::vector<TypeParam>	vec2;
	std::vector<TypeParam>	realvec2;
	vec2.assign(scrapVec.begin(), scrapVec.end());
	realvec2.assign(scrapVec.begin(), scrapVec.end());

	testSizeAndContent(vec, realvec);
	testSizeAndContent(vec2, realvec2);

	vec.swap(vec2);
	realvec.swap(realvec2);

	testSizeAndContent(vec, realvec);
	testSizeAndContent(vec2, realvec2);
}

TYPED_TEST(vector_tester, swap_non_member_test) {
	ft::vector<TypeParam>	vec;
	std::vector<TypeParam>	realvec;
	std::vector<TypeParam>	scrapVec;
	initialise_default_vector(vec, realvec);
	initialise_scrap_vector(scrapVec);

	ft::vector<TypeParam>	vec2;
	std::vector<TypeParam>	realvec2;
	vec2.assign(scrapVec.begin(), scrapVec.end());
	realvec2.assign(scrapVec.begin(), scrapVec.end());

	testSizeAndContent(vec, realvec);
	testSizeAndContent(vec2, realvec2);

	ft::swap(vec, vec2);
	std::swap(realvec, realvec2);

	testSizeAndContent(vec, realvec);
	testSizeAndContent(vec2, realvec2);
}

TYPED_TEST(vector_tester, clear_test) {
	ft::vector<TypeParam>	vec;
	std::vector<TypeParam>	realvec;
	initialise_default_vector(vec, realvec);

	ASSERT_FALSE(vec.empty());
	ASSERT_FALSE(realvec.empty());
	vec.clear();
	realvec.clear();
	ASSERT_EQ(vec.size(), 0);
	ASSERT_EQ(realvec.size(), 0);
	ASSERT_TRUE(vec.empty());
	ASSERT_TRUE(realvec.empty());
}

TYPED_TEST(vector_tester, fill_constructor_test) {
	std::vector<TypeParam>	scrapVec;
	initialise_scrap_vector(scrapVec);

	ft::vector<TypeParam>	vec(20, scrapVec.front());
	std::vector<TypeParam>	realvec(20, scrapVec.front());

	testSizeAndContent(vec, realvec);
}

TYPED_TEST(vector_tester, range_constructor_test) {
	std::vector<TypeParam>	scrapVec;
	initialise_scrap_vector(scrapVec);

	ft::vector<TypeParam>	vec(scrapVec.begin(), scrapVec.end());
	std::vector<TypeParam>	realvec(scrapVec.begin(), scrapVec.end());

	testSizeAndContent(vec, realvec);
}

TYPED_TEST(vector_tester, relational_operators_test) {
	ft::vector<TypeParam>	vec;
	std::vector<TypeParam>	realvec;
	initialise_default_vector(vec, realvec);

	ft::vector<TypeParam>	vecCopy(vec);
	std::vector<TypeParam>	realvecCopy(realvec);

	ASSERT_EQ((vec == vecCopy), (realvec == realvecCopy));
	ASSERT_EQ((vec != vecCopy), (realvec != realvecCopy));
	ASSERT_EQ((vec < vecCopy), (realvec < realvecCopy));
	ASSERT_EQ((vecCopy < vec), (realvecCopy < realvec));
	ASSERT_EQ((vec <= vecCopy), (realvec <= realvecCopy));
	ASSERT_EQ((vecCopy <= vec), (realvecCopy <= realvec));
	ASSERT_EQ((vec >= vecCopy), (realvec >= realvecCopy));
	ASSERT_EQ((vecCopy >= vec), (realvecCopy >= realvec));
	ASSERT_EQ((vec > vecCopy), (realvec > realvecCopy));
	ASSERT_EQ((vecCopy > vec), (realvecCopy > realvec));
	addition_to_vector(vec, realvec);
	ASSERT_EQ((vec == vecCopy), (realvec == realvecCopy));
	ASSERT_EQ((vec != vecCopy), (realvec != realvecCopy));
	ASSERT_EQ((vec < vecCopy), (realvec < realvecCopy));
	ASSERT_EQ((vecCopy < vec), (realvecCopy < realvec));
	ASSERT_EQ((vec <= vecCopy), (realvec <= realvecCopy));
	ASSERT_EQ((vecCopy <= vec), (realvecCopy <= realvec));
	ASSERT_EQ((vec >= vecCopy), (realvec >= realvecCopy));
	ASSERT_EQ((vecCopy >= vec), (realvecCopy >= realvec));
	ASSERT_EQ((vec > vecCopy), (realvec > realvecCopy));
	ASSERT_EQ((vecCopy > vec), (realvecCopy > realvec));
}

TYPED_TEST(vector_tester, iterator_dereference_tests) {
	ft::vector<TypeParam>	vec;
	std::vector<TypeParam>	realvec;
	initialise_default_vector(vec, realvec);

	typename ft::vector<TypeParam>::const_iterator	it = vec.begin();
	typename std::vector<TypeParam>::const_iterator	real_it = realvec.begin();

	for (size_t i = 0; i < realvec.size(); i++)
		ASSERT_EQ(it[i], real_it[i]);
}

TYPED_TEST(vector_tester, iterator_increment_tests) {
	ft::vector<TypeParam>	vec;
	std::vector<TypeParam>	realvec;
	initialise_default_vector(vec, realvec);

	typename ft::vector<TypeParam>::const_iterator	it = vec.begin();
	typename std::vector<TypeParam>::const_iterator	real_it = realvec.begin();

	for (; it != vec.end(); it++, real_it++)
		ASSERT_EQ(*it, *real_it);
}

TYPED_TEST(vector_tester, iterator_decrement_tests) {
	ft::vector<TypeParam>	vec;
	std::vector<TypeParam>	realvec;
	initialise_default_vector(vec, realvec);

	typename ft::vector<TypeParam>::const_iterator	it = vec.end() - 1;
	typename std::vector<TypeParam>::const_iterator	real_it = realvec.end() - 1;

	for (; it >= vec.begin(); it--, real_it--)
		ASSERT_EQ(*it, *real_it);
}

TYPED_TEST(vector_tester, iterator_operation_tests) {
	ft::vector<TypeParam>	vec;
	std::vector<TypeParam>	realvec;
	initialise_default_vector(vec, realvec);

	typename ft::vector<TypeParam>::const_iterator	it = vec.begin();
	typename std::vector<TypeParam>::const_iterator	real_it = realvec.begin();

	ASSERT_EQ(*(it + 3), *(real_it + 3));
	ASSERT_EQ(*(it + vec.size() - 1), *(real_it + realvec.size() - 1));
	it += 2;
	real_it += 2;
	ASSERT_EQ(*it, *real_it);
	it -= 1;
	real_it -= 1;
	ASSERT_EQ(*it, *real_it);
	ASSERT_EQ(*(2 + it), *(2 + real_it));
	ASSERT_EQ(*(1 + it + 1), *(1 + real_it + 1));

	typename ft::vector<TypeParam>::const_iterator	it2 = vec.begin() + 4;
	typename std::vector<TypeParam>::const_iterator	real_it2 = realvec.begin() + 4;

	ASSERT_EQ((it2 - it), (real_it2 - real_it));
	it2 = it;
	real_it2 = real_it;
	ASSERT_EQ(*it2, *real_it);
	ASSERT_EQ(*it, *real_it2);
}

TYPED_TEST(vector_tester, iterator_relational_operators_tests) {
	ft::vector<TypeParam>	vec;
	std::vector<TypeParam>	realvec;
	initialise_default_vector(vec, realvec);

	typename ft::vector<TypeParam>::const_iterator	it = vec.begin();
	typename std::vector<TypeParam>::const_iterator	real_it = realvec.begin();

	typename ft::vector<TypeParam>::const_iterator	it2 = it;
	typename std::vector<TypeParam>::const_iterator	real_it2 = real_it;

	ASSERT_EQ((it == it2), (real_it == real_it2));
	it += 1;
	real_it += 1;
	ASSERT_EQ((it == it2), (real_it == real_it2));
	ASSERT_EQ((it != it2), (real_it != real_it2));
	ASSERT_EQ((it >= it2), (real_it >= real_it2));
	ASSERT_EQ((it <= it2), (real_it <= real_it2));
	ASSERT_EQ((it > it2), (real_it > real_it2));
	ASSERT_EQ((it < it2), (real_it < real_it2));

	/* compare non-const to const iterators */
	typename ft::vector<TypeParam>::iterator	nc_it = vec.begin() + 1;
	typename std::vector<TypeParam>::iterator	nc_real_it = realvec.begin() + 1;

	ASSERT_EQ((it == nc_it), (real_it == nc_real_it));
	ASSERT_EQ((it != nc_it), (real_it != nc_real_it));
	ASSERT_EQ((it >= nc_it), (real_it >= nc_real_it));
	ASSERT_EQ((it <= nc_it), (real_it <= nc_real_it));
	ASSERT_EQ((it > nc_it), (real_it > nc_real_it));
	ASSERT_EQ((it < nc_it), (real_it < nc_real_it));
	nc_it += 1;
	nc_real_it += 1;
	ASSERT_EQ((it == nc_it), (real_it == nc_real_it));
	ASSERT_EQ((it != nc_it), (real_it != nc_real_it));
	ASSERT_EQ((it >= nc_it), (real_it >= nc_real_it));
	ASSERT_EQ((it <= nc_it), (real_it <= nc_real_it));
	ASSERT_EQ((it > nc_it), (real_it > nc_real_it));
	ASSERT_EQ((it < nc_it), (real_it < nc_real_it));
}

TYPED_TEST(vector_tester, iterator_modification_tests) {
	ft::vector<TypeParam>	vec;
	std::vector<TypeParam>	realvec;
	initialise_default_vector(vec, realvec);

	testSizeAndContent(vec, realvec);

	typename ft::vector<TypeParam>::iterator	it = vec.begin();
	typename std::vector<TypeParam>::iterator	real_it = realvec.begin();
	for (; it != vec.end(); it++, real_it++) {
		addition_func(*it);
		addition_func(*real_it);
	}
	testSizeAndContent(vec, realvec);

	it = vec.begin();
	real_it = realvec.begin();
	for (; it != vec.end(); it++, real_it++) {
		subtraction_func(*it);
		subtraction_func(*real_it);
	}
	testSizeAndContent(vec, realvec);

	it = vec.begin();
	real_it = realvec.begin();
	for (; it != vec.end(); it++, real_it++) {
		multiplication_func(*it);
		multiplication_func(*real_it);
	}
	testSizeAndContent(vec, realvec);
}

TYPED_TEST(vector_tester, reverse_iterator_increment_tests) {
	ft::vector<TypeParam>	vec;
	std::vector<TypeParam>	realvec;
	initialise_default_vector(vec, realvec);

	typename ft::vector<TypeParam>::const_reverse_iterator	it = vec.rbegin();
	typename std::vector<TypeParam>::const_reverse_iterator	real_it = realvec.rbegin();

	for (; it != vec.rend(); it++, real_it++)
		ASSERT_EQ(*it, *real_it);
}

TYPED_TEST(vector_tester, reverse_iterator_decrement_tests) {
	ft::vector<TypeParam>	vec;
	std::vector<TypeParam>	realvec;
	initialise_default_vector(vec, realvec);

	typename ft::vector<TypeParam>::const_reverse_iterator	it = vec.rend() - 1;
	typename std::vector<TypeParam>::const_reverse_iterator	real_it = realvec.rend() - 1;

	for (; it >= vec.rbegin(); it--, real_it--)
		ASSERT_EQ(*it, *real_it);
	it = vec.rbegin();
	real_it = realvec.rbegin();
	it += 3;
	real_it += 3;
	ASSERT_EQ(*it, *real_it);
	it -= 2;
	real_it -= 2;
	ASSERT_EQ(*it, *real_it);
	ASSERT_EQ(*(2 + it), *(2 + real_it));
	ASSERT_EQ(*(1 + it + 1), *(1 + real_it + 1));

	typename ft::vector<TypeParam>::const_reverse_iterator	it2 = vec.rbegin() + 4;
	typename std::vector<TypeParam>::const_reverse_iterator	real_it2 = realvec.rbegin() + 4;

	ASSERT_EQ((it2 - it), (real_it2 - real_it));
	it2 = it;
	real_it2 = real_it;
	ASSERT_EQ(*it2, *real_it);
	ASSERT_EQ(*it, *real_it2);
}

TYPED_TEST(vector_tester, iterator_reverse_relational_operators_tests) {
	ft::vector<TypeParam>	vec;
	std::vector<TypeParam>	realvec;
	initialise_default_vector(vec, realvec);

	typename ft::vector<TypeParam>::const_reverse_iterator	it = vec.rbegin();
	typename std::vector<TypeParam>::const_reverse_iterator	real_it = realvec.rbegin();

	typename ft::vector<TypeParam>::const_reverse_iterator	it2 = it;
	typename std::vector<TypeParam>::const_reverse_iterator	real_it2 = real_it;

	ASSERT_EQ((it == it2), (real_it == real_it2));
	it += 1;
	real_it += 1;
	ASSERT_EQ((it == it2), (real_it == real_it2));
	ASSERT_EQ((it != it2), (real_it != real_it2));
	ASSERT_EQ((it >= it2), (real_it >= real_it2));
	ASSERT_EQ((it <= it2), (real_it <= real_it2));
	ASSERT_EQ((it > it2), (real_it > real_it2));
	ASSERT_EQ((it < it2), (real_it < real_it2));

	/* compare non-const to const iterators */
	typename ft::vector<TypeParam>::reverse_iterator	nc_it = vec.rbegin() + 1;
	typename std::vector<TypeParam>::reverse_iterator	nc_real_it = realvec.rbegin() + 1;

	ASSERT_EQ((it == nc_it), (real_it == nc_real_it));
	ASSERT_EQ((it != nc_it), (real_it != nc_real_it));
	ASSERT_EQ((it >= nc_it), (real_it >= nc_real_it));
	ASSERT_EQ((it <= nc_it), (real_it <= nc_real_it));
	ASSERT_EQ((it > nc_it), (real_it > nc_real_it));
	ASSERT_EQ((it < nc_it), (real_it < nc_real_it));
	nc_it += 1;
	nc_real_it += 1;
	ASSERT_EQ((it == nc_it), (real_it == nc_real_it));
	ASSERT_EQ((it != nc_it), (real_it != nc_real_it));
	ASSERT_EQ((it >= nc_it), (real_it >= nc_real_it));
	ASSERT_EQ((it <= nc_it), (real_it <= nc_real_it));
	ASSERT_EQ((it > nc_it), (real_it > nc_real_it));
	ASSERT_EQ((it < nc_it), (real_it < nc_real_it));
}

TYPED_TEST(vector_tester, iterator_reverse_construction_tests) {
	ft::vector<TypeParam>	vec;
	std::vector<TypeParam>	realvec;
	initialise_default_vector(vec, realvec);

	typename ft::vector<TypeParam>::const_iterator	it = vec.begin();
	typename std::vector<TypeParam>::const_iterator	real_it = realvec.begin();
	typename ft::vector<TypeParam>::const_reverse_iterator	rit = vec.rbegin();
	typename std::vector<TypeParam>::const_reverse_iterator	real_rit = realvec.rbegin();

	typename ft::vector<TypeParam>::reverse_iterator	nc_rit(vec.rbegin());
	typename std::vector<TypeParam>::reverse_iterator	nc_real_rit(realvec.rbegin());
	typename ft::vector<TypeParam>::const_reverse_iterator	rit2(nc_rit);
	typename std::vector<TypeParam>::const_reverse_iterator	real_rit2(nc_real_rit);

	ASSERT_EQ(*it, *real_it);
	ASSERT_EQ(*rit, *real_rit);
	ASSERT_EQ(*nc_rit, *nc_real_rit);
	ASSERT_EQ(*rit2, *real_rit2);
}

TYPED_TEST(vector_tester, iterator_reverse_modification_tests) {
	ft::vector<TypeParam>	vec;
	std::vector<TypeParam>	realvec;
	initialise_default_vector(vec, realvec);

	testSizeAndContent(vec, realvec);

	typename ft::vector<TypeParam>::reverse_iterator	it = vec.rbegin();
	typename std::vector<TypeParam>::reverse_iterator	real_it = realvec.rbegin();
	for (; it != vec.rend(); it++, real_it++) {
		addition_func(*it);
		addition_func(*real_it);
	}
	testSizeAndContent(vec, realvec);

	it = vec.rbegin();
	real_it = realvec.rbegin();
	for (; it != vec.rend(); it++, real_it++) {
		subtraction_func(*it);
		subtraction_func(*real_it);
	}
	testSizeAndContent(vec, realvec);

	it = vec.rbegin();
	real_it = realvec.rbegin();
	for (; it != vec.rend(); it++, real_it++) {
		multiplication_func(*it);
		multiplication_func(*real_it);
	}
	testSizeAndContent(vec, realvec);
}

TYPED_TEST(vector_tester, iterator_reverse_base_test) {
	ft::vector<TypeParam>	vec;
	std::vector<TypeParam>	realvec;
	initialise_default_vector(vec, realvec);

	typename ft::vector<TypeParam>::reverse_iterator	nc_rit(vec.rbegin() + 1);
	typename std::vector<TypeParam>::reverse_iterator	nc_real_rit(realvec.rbegin() + 1);
	typename ft::vector<TypeParam>::const_reverse_iterator	rit2(nc_rit + 3);
	typename std::vector<TypeParam>::const_reverse_iterator	real_rit2(nc_real_rit + 3);

	ASSERT_EQ(*(nc_rit.base()), *(nc_real_rit.base()));
	ASSERT_EQ(*(rit2.base()), *(real_rit2.base()));
}
