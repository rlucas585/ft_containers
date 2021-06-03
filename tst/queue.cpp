/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   queue.cpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/13 15:05:42 by rlucas        #+#    #+#                 */
/*   Updated: 2021/03/13 15:46:31 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <gtest/gtest.h>

#include <stdexcept>
#include <algorithm>
#include <queue>
#include <string>
#include <iostream>
#include <iomanip>

#include "../src/queue.hpp"
#include "test_fixture_classes.hpp"
#include "Example.hpp"
#include "test.hpp"

template <typename Queue>
static std::string	queue_to_str(Queue const& queue) {
	std::stringstream		ss;
	Queue					copy(queue);

	ss << "[";
	while (copy.size()) {
		if (copy.size() == 1)
			ss << copy.front();
		else
			ss << copy.front() << ", ";
		copy.pop();
	}
	ss << "]";
	return ss.str();
}

template <typename Queue>
static void	print_queue_info(Queue const& queue, const char *name) {
	std::string		queueStr = queue_to_str(queue);
	if (queueStr.size() >= 40)
		queueStr.erase(queueStr.begin() + 40, queueStr.end());

	std::cout << std::setw(10) << std::right << std::setfill(' ')
		<< name;
	std::cout << "|";
	std::cout << std::setw(10) << std::right << std::setfill(' ')
		<< queue.size();
	std::cout << "|";
	std::cout << std::setw(40) << std::right << std::setfill(' ')
		<< queueStr;
	std::cout << "|";
	std::cout << std::endl;
}

template <typename T>
static void	print_table(ft::queue<T> const& queue, std::queue<T> const& realqueue) {
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
	print_queue_info(queue, "queue");
	print_queue_info(realqueue, "realqueue");
	std::cout << "----------------------------------------------------------------" << std::endl;
}

template <typename T>
void	initialise_default_queue(ft::queue<T>& s, std::queue<T>& real_s) {
	ft::vector<T>		t_vec1;
	std::vector<T>		t_vec2;
	initialise_default_vector(t_vec1, t_vec2);

	for (size_t i = 0; i != t_vec1.size(); i++) {
		s.push(t_vec1[i]);
		real_s.push(t_vec2[i]);
	}
}

template <typename T>
void	testQueues(ft::queue<T>const& s, std::queue<T>const& real_s) {
	ft::queue<T>		copy(s);
	std::queue<T>		realcopy(real_s);

	if (PRINTED_OUTPUT)
		print_table(s, real_s);
	ASSERT_EQ(copy.size(), realcopy.size());
	while (copy.size()) {
		ASSERT_EQ(copy.front(), realcopy.front());
		copy.pop();
		realcopy.pop();
	}
}

TYPED_TEST_CASE(queue_tester, Implementations);

TYPED_TEST(queue_tester, empty_test) {
	ft::queue<TypeParam>		q;
	std::queue<TypeParam>		real_q;

	ASSERT_TRUE(q.empty());
	ASSERT_TRUE(real_q.empty());
	ASSERT_EQ(q.empty(), real_q.empty());

	initialise_default_queue(q, real_q);

	testQueues(q, real_q);

	ASSERT_FALSE(q.empty());
	ASSERT_FALSE(real_q.empty());
	ASSERT_EQ(q.empty(), real_q.empty());
}

TYPED_TEST(queue_tester, size_test) {
	ft::queue<TypeParam>		q;
	std::queue<TypeParam>		real_q;

	ASSERT_EQ(q.size(), real_q.size());

	initialise_default_queue(q, real_q);

	ASSERT_EQ(q.size(), real_q.size());
	testQueues(q, real_q);
}

TYPED_TEST(queue_tester, front_back_test) {
	ft::queue<TypeParam>		q;
	std::queue<TypeParam>		real_q;
	ft::vector<TypeParam>		vec;
	std::vector<TypeParam>		vec_real;

	initialise_default_vector(vec, vec_real);

	for (size_t i = 0; i != vec.size(); i++) {
		q.push(vec[i]);
		real_q.push(vec_real[i]);
		ASSERT_EQ(q.front(), real_q.front());
		ASSERT_EQ(q.back(), real_q.back());
	}

	testQueues(q, real_q);
}

TYPED_TEST(queue_tester, pop_test) {
	ft::queue<TypeParam>		q;
	std::queue<TypeParam>		real_q;

	initialise_default_queue(q, real_q);

	while (q.size()) {
		q.pop();
		real_q.pop();
		testQueues(q, real_q);
	}
	ASSERT_TRUE(q.empty());
	ASSERT_TRUE(real_q.empty());
}

TYPED_TEST(queue_tester, relational_operators_test) {
	ft::queue<TypeParam>		q;
	std::queue<TypeParam>		real_q;
	ft::vector<TypeParam>		vec;
	std::vector<TypeParam>		vec_real;

	initialise_default_vector(vec, vec_real);
	for (size_t i = 0; i != vec.size(); i++) {
		q.push(vec[i]);
		real_q.push(vec_real[i]);
	}

	ft::queue<TypeParam>		q2(q);
	std::queue<TypeParam>		real_q2(real_q);

	ASSERT_EQ((q == q2), (real_q == real_q2));
	ASSERT_EQ((q != q2), (real_q != real_q2));
	ASSERT_EQ((q < q2), (real_q < real_q2));
	ASSERT_EQ((q2 < q), (real_q2 < real_q));
	ASSERT_EQ((q <= q2), (real_q <= real_q2));
	ASSERT_EQ((q2 <= q), (real_q2 <= real_q));
	ASSERT_EQ((q >= q2), (real_q >= real_q2));
	ASSERT_EQ((q2 >= q), (real_q2 >= real_q));
	ASSERT_EQ((q > q2), (real_q > real_q2));
	ASSERT_EQ((q2 > q), (real_q2 > real_q));

	while (q2.size()) {
		q2.pop();
		real_q2.pop();
	}
	addition_to_vector(vec, vec_real);
	for (size_t i = 0; i != vec.size(); i++) {
		q2.push(vec[i]);
		real_q2.push(vec_real[i]);
	}
	ASSERT_EQ((q == q2), (real_q == real_q2));
	ASSERT_EQ((q != q2), (real_q != real_q2));
	ASSERT_EQ((q < q2), (real_q < real_q2));
	ASSERT_EQ((q2 < q), (real_q2 < real_q));
	ASSERT_EQ((q <= q2), (real_q <= real_q2));
	ASSERT_EQ((q2 <= q), (real_q2 <= real_q));
	ASSERT_EQ((q >= q2), (real_q >= real_q2));
	ASSERT_EQ((q2 >= q), (real_q2 >= real_q));
	ASSERT_EQ((q > q2), (real_q > real_q2));
	ASSERT_EQ((q2 > q), (real_q2 > real_q));
}
