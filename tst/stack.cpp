/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   stack.cpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/12 12:23:08 by rlucas        #+#    #+#                 */
/*   Updated: 2021/03/13 15:42:58 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <gtest/gtest.h>

#include <stdexcept>
#include <algorithm>
#include <stack>
#include <string>
#include <iostream>
#include <iomanip>

#include "../src/stack.hpp"
#include "test_fixture_classes.hpp"
#include "Example.hpp"
#include "test.hpp"

template <typename Stack>
static std::string	stack_to_str(Stack const& stack) {
	std::stringstream		ss;
	Stack					copy(stack);

	ss << "[";
	while (copy.size()) {
		if (copy.size() == 1)
			ss << copy.top();
		else
			ss << copy.top() << ", ";
		copy.pop();
	}
	ss << "]";
	return ss.str();
}

template <typename Stack>
static void	print_stack_info(Stack const& stack, const char *name) {
	std::string		stackStr = stack_to_str(stack);
	if (stackStr.size() >= 40)
		stackStr.erase(stackStr.begin() + 40, stackStr.end());

	std::cout << std::setw(10) << std::right << std::setfill(' ')
		<< name;
	std::cout << "|";
	std::cout << std::setw(10) << std::right << std::setfill(' ')
		<< stack.size();
	std::cout << "|";
	std::cout << std::setw(40) << std::right << std::setfill(' ')
		<< stackStr;
	std::cout << "|";
	std::cout << std::endl;
}

template <typename T>
static void	print_table(ft::stack<T> const& stack, std::stack<T> const& realstack) {
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
	print_stack_info(stack, "stack");
	print_stack_info(realstack, "realstack");
	std::cout << "----------------------------------------------------------------" << std::endl;
}

template <typename T>
void	initialise_default_stack(ft::stack<T>& s, std::stack<T>& real_s) {
	ft::vector<T>		t_vec1;
	std::vector<T>		t_vec2;
	initialise_default_vector(t_vec1, t_vec2);

	for (size_t i = 0; i != t_vec1.size(); i++) {
		s.push(t_vec1[i]);
		real_s.push(t_vec2[i]);
	}
}

template <typename T>
void	testStacks(ft::stack<T>const& s, std::stack<T>const& real_s) {
	ft::stack<T>		copy(s);
	std::stack<T>		realcopy(real_s);

	if (PRINTED_OUTPUT)
		print_table(s, real_s);
	ASSERT_EQ(copy.size(), realcopy.size());
	while (copy.size()) {
		ASSERT_EQ(copy.top(), realcopy.top());
		copy.pop();
		realcopy.pop();
	}
}

TYPED_TEST_CASE(stack_tester, Implementations);

TYPED_TEST(stack_tester, empty_test) {
	ft::stack<TypeParam>		s;
	std::stack<TypeParam>		real_s;

	ASSERT_TRUE(s.empty());
	ASSERT_TRUE(real_s.empty());
	ASSERT_EQ(s.empty(), real_s.empty());

	initialise_default_stack(s, real_s);

	testStacks(s, real_s);

	ASSERT_FALSE(s.empty());
	ASSERT_FALSE(real_s.empty());
	ASSERT_EQ(s.empty(), real_s.empty());
}

TYPED_TEST(stack_tester, size_test) {
	ft::stack<TypeParam>		s;
	std::stack<TypeParam>		real_s;

	ASSERT_EQ(s.size(), real_s.size());

	initialise_default_stack(s, real_s);

	ASSERT_EQ(s.size(), real_s.size());
	testStacks(s, real_s);
}

TYPED_TEST(stack_tester, top_test) {
	ft::stack<TypeParam>		s;
	std::stack<TypeParam>		real_s;
	ft::vector<TypeParam>		vec;
	std::vector<TypeParam>		vec_real;

	initialise_default_vector(vec, vec_real);

	for (size_t i = 0; i != vec.size(); i++) {
		s.push(vec[i]);
		real_s.push(vec_real[i]);
		ASSERT_EQ(s.top(), real_s.top());
	}

	testStacks(s, real_s);
}

TYPED_TEST(stack_tester, pop_test) {
	ft::stack<TypeParam>		s;
	std::stack<TypeParam>		real_s;

	initialise_default_stack(s, real_s);

	while (s.size()) {
		s.pop();
		real_s.pop();
		testStacks(s, real_s);
	}
	ASSERT_TRUE(s.empty());
	ASSERT_TRUE(real_s.empty());
}

TYPED_TEST(stack_tester, relational_operators_test) {
	ft::stack<TypeParam>		s;
	std::stack<TypeParam>		real_s;
	ft::vector<TypeParam>		vec;
	std::vector<TypeParam>		vec_real;

	initialise_default_vector(vec, vec_real);
	for (size_t i = 0; i != vec.size(); i++) {
		s.push(vec[i]);
		real_s.push(vec_real[i]);
	}

	ft::stack<TypeParam>		s2(s);
	std::stack<TypeParam>		real_s2(real_s);

	ASSERT_EQ((s == s2), (real_s == real_s2));
	ASSERT_EQ((s != s2), (real_s != real_s2));
	ASSERT_EQ((s < s2), (real_s < real_s2));
	ASSERT_EQ((s2 < s), (real_s2 < real_s));
	ASSERT_EQ((s <= s2), (real_s <= real_s2));
	ASSERT_EQ((s2 <= s), (real_s2 <= real_s));
	ASSERT_EQ((s >= s2), (real_s >= real_s2));
	ASSERT_EQ((s2 >= s), (real_s2 >= real_s));
	ASSERT_EQ((s > s2), (real_s > real_s2));
	ASSERT_EQ((s2 > s), (real_s2 > real_s));

	while (s2.size()) {
		s2.pop();
		real_s2.pop();
	}
	addition_to_vector(vec, vec_real);
	for (size_t i = 0; i != vec.size(); i++) {
		s2.push(vec[i]);
		real_s2.push(vec_real[i]);
	}
	ASSERT_EQ((s == s2), (real_s == real_s2));
	ASSERT_EQ((s != s2), (real_s != real_s2));
	ASSERT_EQ((s < s2), (real_s < real_s2));
	ASSERT_EQ((s2 < s), (real_s2 < real_s));
	ASSERT_EQ((s <= s2), (real_s <= real_s2));
	ASSERT_EQ((s2 <= s), (real_s2 <= real_s));
	ASSERT_EQ((s >= s2), (real_s >= real_s2));
	ASSERT_EQ((s2 >= s), (real_s2 >= real_s));
	ASSERT_EQ((s > s2), (real_s > real_s2));
	ASSERT_EQ((s2 > s), (real_s2 > real_s));
}
