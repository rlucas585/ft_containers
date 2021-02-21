/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/20 13:48:57 by rlucas        #+#    #+#                 */
/*   Updated: 2021/02/21 16:59:08 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <gtest/gtest.h>

#include <stdexcept>
#include <algorithm>
#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <iomanip>

#include "../src/list.hpp"
#include "test_fixture_classes.hpp"
#include "Example.hpp"
#include "test.hpp"

void	initialise_sorted_list(ft::list<int>& list, std::list<int>& reallist) {
	for (unsigned int i = 5; i <= 30; i += 5) {
		list.push_back(i);
		reallist.push_back(i);
	}
}

void	initialise_sorted_list(ft::list<std::string>& list, std::list<std::string>& reallist) {
	std::vector<std::string>		newvals;

	newvals.push_back("Lorem");
	newvals.push_back("adipiscing elit. Donec aliquam tempus orci. Pellentesque "
			"bibendum consequat mauris, id pharetra urna molestie eget. Quisque a vulputate dolor.");
	newvals.push_back("amet,");
	newvals.push_back("dolor");
	newvals.push_back("ipsum");
	newvals.push_back("sit long long long long long long long long long long long long long long");
	for (size_t i = 0; i != newvals.size(); i++) {
		list.push_back(newvals[i]);
		reallist.push_back(newvals[i]);
	}
}

void	initialise_sorted_list(ft::list<Example>& list, std::list<Example>& reallist) {
	std::vector<Example>		newvals;

	newvals.push_back(Example::createWithNameAndValue("Jotaro", 4));
	newvals.push_back(Example::createWithNameAndValue("Joseph", 12));
	newvals.push_back(Example::createWithNameAndValue("Josuke", 18));
	newvals.push_back(Example::createWithNameAndValue("Jonathan", 20));
	newvals.push_back(Example::createWithNameAndValue("Jolyne", 27));
	newvals.push_back(Example::createWithNameAndValue("Johnny", 5));
	newvals.push_back(Example::createWithNameAndValue("Giorno", 3));
	for (size_t i = 0; i != newvals.size(); i++) {
		list.push_back(newvals[i]);
		reallist.push_back(newvals[i]);
	}
}

void	initialise_default_list(ft::list<int>& list, std::list<int>& reallist) {
	for (unsigned int i = 5; i <= 30; i += 5) {
		list.push_back(i);
		reallist.push_back(i);
	}
	list.push_back(8);
	reallist.push_back(8);
	list.push_back(16);
	reallist.push_back(16);
}

void	initialise_default_list(ft::list<std::string>& list, std::list<std::string>& reallist) {
	std::vector<std::string>		newvals;

	newvals.push_back("Lorem");
	newvals.push_back("ipsum");
	newvals.push_back("dolor");
	newvals.push_back("adipiscing elit. Donec aliquam tempus orci. Pellentesque "
			"bibendum consequat mauris, id pharetra urna molestie eget. Quisque a vulputate dolor.");
	newvals.push_back("sit long long long long long long long long long long long long long long");
	newvals.push_back("amet,");
	for (size_t i = 0; i != newvals.size(); i++) {
		list.push_back(newvals[i]);
		reallist.push_back(newvals[i]);
	}
}

void	initialise_default_list(ft::list<Example>& list, std::list<Example>& reallist) {
	std::vector<Example>		newvals;

	newvals.push_back(Example::createWithNameAndValue("Jonathan", 20));
	newvals.push_back(Example::createWithNameAndValue("Joseph", 12));
	newvals.push_back(Example::createWithNameAndValue("Jotaro", 4));
	newvals.push_back(Example::createWithNameAndValue("Josuke", 18));
	newvals.push_back(Example::createWithNameAndValue("Giorno", 3));
	newvals.push_back(Example::createWithNameAndValue("Jolyne", 27));
	newvals.push_back(Example::createWithNameAndValue("Johnny", 5));
	for (size_t i = 0; i != newvals.size(); i++) {
		list.push_back(newvals[i]);
		reallist.push_back(newvals[i]);
	}
}

void	addition_to_list(ft::list<int>& list, std::list<int>& reallist) {
	list.front() += 1;
	reallist.front() += 1;
}

void	addition_to_list(ft::list<std::string>& list, std::list<std::string>& reallist) {
	std::string&	s = list.front();
	std::string&	reals = reallist.front();
	s[0] += 1;
	reals[0] += 1;
}

void	addition_to_list(ft::list<Example>& list, std::list<Example>& reallist) {
	Example&	e = list.front();
	Example&	real_e = reallist.front();
	e.addToName(1);
	real_e.addToName(1);
}

void	subtraction_to_list(ft::list<int>& list, std::list<int>& reallist) {
	list.front() -= 1;
	reallist.front() -= 1;
}

void	subtraction_to_list(ft::list<std::string>& list, std::list<std::string>& reallist) {
	std::string&	s = list.front();
	std::string&	reals = reallist.front();
	s[0] -= 1;
	reals[0] -= 1;
}

void	subtraction_to_list(ft::list<Example>& list, std::list<Example>& reallist) {
	Example&	e = list.front();
	Example&	real_e = reallist.front();
	e.subName(1);
	real_e.subName(1);
}

template <typename List>
std::string	list_to_str(List const& list) {
	std::stringstream	ss;
	typename List::const_iterator	it = list.begin();

	ss << "[";
	for (; it != list.end(); it++) {
		ss << *it << ", ";
	}
	ss << "]";
	return ss.str();
}

template <typename List>
void	print_list_info(List const& list, const char *name) {
	std::string		listStr = list_to_str(list);
	if (listStr.size() >= 30)
		listStr.erase(listStr.begin() + 30, listStr.end());

	std::cout << std::setw(10) << std::right << std::setfill(' ')
		<< name;
	std::cout << "|";
	std::cout << std::setw(10) << std::right << std::setfill(' ')
		<< list.size();
	std::cout << "|";
	std::cout << std::setw(30) << std::right << std::setfill(' ')
		<< listStr;
	std::cout << "|";
	std::cout << std::endl;
}

template <typename T>
void	print_table(ft::list<T> const& list, std::list<T> const& reallist) {
	std::cout <<
		"----------------------------------------------------------------"
		<< std::endl;
	std::cout << std::setw(10) << std::right << std::setfill(' ')
		<< "name";
	std::cout << "|";
	std::cout << std::setw(10) << std::right << std::setfill(' ')
		<< "size";
	std::cout << "|";
	std::cout << std::setw(30) << std::right << std::setfill(' ')
		<< "content";
	std::cout << "|";
	std::cout << std::endl;
	std::cout << "----------------------------------------------------------------" << std::endl;
	print_list_info(list, "list");
	print_list_info(reallist, "reallist");
	std::cout << "----------------------------------------------------------------" << std::endl;
}

template <typename Iterator>
Iterator		incrementIterator(Iterator it, size_t n) {
	while (n > 0) {
		it++;
		n -= 1;
	}
	return it;
}

template <typename Iterator>
Iterator		decrementIterator(Iterator it, size_t n) {
	while (n > 0) {
		it--;
		n -= 1;
	}
	return it;
}

template <typename T>
void	testSizeAndContent(ft::list<T>const& list, std::list<T>const& reallist) {
	if (PRINTED_OUTPUT)
		print_table(list, reallist);
	ASSERT_EQ(list.size(), reallist.size());
	typename	ft::list<T>::const_iterator		it = list.begin();
	typename	std::list<T>::const_iterator	itReal = reallist.begin();
	for (; it != list.end(); it++, itReal++)
		ASSERT_EQ(*it, *itReal);
}

TYPED_TEST_CASE(list_tester, Implementations);

TYPED_TEST(list_tester, empty_test) {
	ft::list<TypeParam>	list;
	std::list<TypeParam>	reallist;

	ASSERT_TRUE(list.empty());
	ASSERT_TRUE(reallist.empty());
	ASSERT_EQ(list.empty(), reallist.empty());

	initialise_default_list(list, reallist);

	ASSERT_EQ(list.empty(), reallist.empty());
	ASSERT_FALSE(list.empty());
	ASSERT_FALSE(reallist.empty());
}

TYPED_TEST(list_tester, push_back_test) {
	ft::list<TypeParam>	list;
	std::list<TypeParam>	reallist;
	initialise_default_list(list, reallist);

	testSizeAndContent(list, reallist);
}

TYPED_TEST(list_tester, size_test) {
	ft::list<TypeParam>	list;
	std::list<TypeParam>	reallist;
	initialise_default_list(list, reallist);

	ASSERT_EQ(list.size(), reallist.size());
}

TYPED_TEST(list_tester, max_size_test) {
	ft::list<TypeParam>		list;
	std::list<TypeParam>	reallist;
	initialise_default_list(list, reallist);
	size_t				diff;

	diff = std::max(list.max_size(), reallist.max_size()) -
		std::min(list.max_size(), reallist.max_size());
	ASSERT_TRUE(diff < 100);
}

TYPED_TEST(list_tester, resize_test) {
	ft::list<TypeParam>	list;
	std::list<TypeParam>	reallist;
	std::vector<TypeParam>		scrapVec;
	initialise_default_list(list, reallist);
	initialise_scrap_vector(scrapVec);

	testSizeAndContent(list, reallist);

	list.resize(list.size() + 3);
	reallist.resize(reallist.size() + 3);

	testSizeAndContent(list, reallist);

	list.resize(list.size() + 3, scrapVec[3]);
	reallist.resize(reallist.size() + 3, scrapVec[3]);

	testSizeAndContent(list, reallist);
}

TYPED_TEST(list_tester, front_back_test) {
	ft::list<TypeParam>	list;
	std::list<TypeParam>	reallist;

	initialise_default_list(list, reallist);
	ASSERT_EQ(list.front(), reallist.front());
	ASSERT_EQ(list.back(), reallist.back());
}

TYPED_TEST(list_tester, pop_back_test) {
	ft::list<TypeParam>	list;
	std::list<TypeParam>	reallist;
	initialise_default_list(list, reallist);

	testSizeAndContent(list, reallist);
	list.pop_back();
	reallist.pop_back();
	testSizeAndContent(list, reallist);
	while (!list.empty()) {
		list.pop_back();
		reallist.pop_back();
	}
	testSizeAndContent(list, reallist);
	ASSERT_TRUE(list.empty());
	ASSERT_TRUE(reallist.empty());
}

TYPED_TEST(list_tester, assign_iterator_test) {
	ft::list<TypeParam>	list;
	std::list<TypeParam>	reallist;
	std::vector<TypeParam>	scrapVec;
	initialise_default_list(list, reallist);
	initialise_scrap_vector(scrapVec);

	testSizeAndContent(list, reallist);

	list.assign(scrapVec.begin(), scrapVec.end());
	reallist.assign(scrapVec.begin(), scrapVec.end());

	testSizeAndContent(list, reallist);

	list.clear();
	reallist.clear();
	ASSERT_EQ(list.empty(), reallist.empty());

	list.assign(scrapVec.begin(), scrapVec.end());
	reallist.assign(scrapVec.begin(), scrapVec.end());

	testSizeAndContent(list, reallist);
}

TYPED_TEST(list_tester, assign_fill_test) {
	ft::list<TypeParam>	list;
	std::list<TypeParam>	reallist;
	std::vector<TypeParam>	scrapVec;
	initialise_default_list(list, reallist);
	initialise_scrap_vector(scrapVec);

	testSizeAndContent(list, reallist);

	list.assign(15, scrapVec[3]);
	reallist.assign(15, scrapVec[3]);
	ASSERT_EQ(list.size(), 15);
	ASSERT_EQ(reallist.size(), 15);

	testSizeAndContent(list, reallist);
}

TYPED_TEST(list_tester, insert_single_element_test) {
	ft::list<TypeParam>	list;
	std::list<TypeParam>	reallist;
	std::vector<TypeParam>	scrapVec;
	initialise_default_list(list, reallist);
	initialise_scrap_vector(scrapVec);

	testSizeAndContent(list, reallist);

	ASSERT_EQ(
			*list.insert(incrementIterator(list.begin(), 2), scrapVec[2]),
			*reallist.insert(incrementIterator(reallist.begin(), 2), scrapVec[2])
			);

	testSizeAndContent(list, reallist);

	ASSERT_EQ(
			*list.insert(decrementIterator(list.end(), 3), scrapVec[scrapVec.size() - 1]),
			*reallist.insert(decrementIterator(reallist.end(), 3), scrapVec[scrapVec.size() - 1])
			);

	testSizeAndContent(list, reallist);
}

TYPED_TEST(list_tester, insert_fill_test) {
	ft::list<TypeParam>	list;
	std::list<TypeParam>	reallist;
	std::vector<TypeParam>	scrapVec;
	initialise_default_list(list, reallist);
	initialise_scrap_vector(scrapVec);

	testSizeAndContent(list, reallist);

	list.insert(incrementIterator(list.begin(), 3), 8, scrapVec[0]);
	reallist.insert(incrementIterator(reallist.begin(), 3), 8, scrapVec[0]);

	testSizeAndContent(list, reallist);
}

TYPED_TEST(list_tester, insert_range_test) {
	ft::list<TypeParam>	list;
	std::list<TypeParam>	reallist;
	std::vector<TypeParam>	scrapVec;
	initialise_default_list(list, reallist);
	initialise_scrap_vector(scrapVec);

	testSizeAndContent(list, reallist);

	list.insert(incrementIterator(list.begin(), 3), scrapVec.begin(), scrapVec.end());
	reallist.insert(incrementIterator(reallist.begin(), 3), scrapVec.begin(), scrapVec.end());

	testSizeAndContent(list, reallist);

	list.insert(list.begin(), scrapVec.begin() + 4, scrapVec.end() - 2);
	reallist.insert(reallist.begin(), scrapVec.begin() + 4, scrapVec.end() - 2);

	testSizeAndContent(list, reallist);
}

TYPED_TEST(list_tester, erase_single_test) {
	ft::list<TypeParam>	list;
	std::list<TypeParam>	reallist;
	initialise_default_list(list, reallist);

	testSizeAndContent(list, reallist);

	ASSERT_EQ(
			*list.erase(list.begin()),
			*reallist.erase(reallist.begin())
			);

	testSizeAndContent(list, reallist);

	ASSERT_EQ(
			*list.erase(incrementIterator(list.begin(), list.size() / 2)),
			*reallist.erase(incrementIterator(reallist.begin(), reallist.size() / 2))
			);

	testSizeAndContent(list, reallist);
}

TYPED_TEST(list_tester, erase_range_test) {
	ft::list<TypeParam>	list;
	std::list<TypeParam>	reallist;
	initialise_default_list(list, reallist);

	testSizeAndContent(list, reallist);

	ASSERT_EQ(
			*list.erase(list.begin(), decrementIterator(list.end(), 2)),
			*reallist.erase(reallist.begin(), decrementIterator(reallist.end(), 2))
			);

	testSizeAndContent(list, reallist);
}

TYPED_TEST(list_tester, swap_member_test) {
	ft::list<TypeParam>	list;
	std::list<TypeParam>	reallist;
	std::vector<TypeParam>	scrapVec;
	initialise_default_list(list, reallist);
	initialise_scrap_vector(scrapVec);

	ft::list<TypeParam>	list2;
	std::list<TypeParam>	reallist2;
	list2.assign(scrapVec.begin(), scrapVec.end());
	reallist2.assign(scrapVec.begin(), scrapVec.end());

	testSizeAndContent(list, reallist);
	testSizeAndContent(list2, reallist2);

	list.swap(list2);
	reallist.swap(reallist2);

	testSizeAndContent(list, reallist);
	testSizeAndContent(list2, reallist2);
}

TYPED_TEST(list_tester, swap_non_member_test) {
	ft::list<TypeParam>	list;
	std::list<TypeParam>	reallist;
	std::vector<TypeParam>	scrapVec;
	initialise_default_list(list, reallist);
	initialise_scrap_vector(scrapVec);

	ft::list<TypeParam>	list2;
	std::list<TypeParam>	reallist2;
	list2.assign(scrapVec.begin(), scrapVec.end());
	reallist2.assign(scrapVec.begin(), scrapVec.end());

	testSizeAndContent(list, reallist);
	testSizeAndContent(list2, reallist2);

	ft::swap(list, list2);
	std::swap(reallist, reallist2);

	testSizeAndContent(list, reallist);
	testSizeAndContent(list2, reallist2);
}

TYPED_TEST(list_tester, clear_test) {
	ft::list<TypeParam>	list;
	std::list<TypeParam>	reallist;
	initialise_default_list(list, reallist);

	ASSERT_FALSE(list.empty());
	ASSERT_FALSE(reallist.empty());
	list.clear();
	reallist.clear();
	ASSERT_EQ(list.size(), 0);
	ASSERT_EQ(reallist.size(), 0);
	ASSERT_TRUE(list.empty());
	ASSERT_TRUE(reallist.empty());
}

TYPED_TEST(list_tester, splice_test_whole_list) {
	ft::list<TypeParam>	list;
	std::list<TypeParam>	reallist;
	initialise_default_list(list, reallist);
	ft::list<TypeParam>	list2;
	std::list<TypeParam>	reallist2;
	initialise_default_list(list2, reallist2);
	std::vector<TypeParam>	scrapVec;
	initialise_scrap_vector(scrapVec);

	typename ft::list<TypeParam>::iterator		it = incrementIterator(list.begin(), 3);
	typename std::list<TypeParam>::iterator		realit = incrementIterator(reallist.begin(), 3);

	for (typename std::vector<TypeParam>::iterator it = scrapVec.begin(); it != scrapVec.end(); it++) {
		list2.push_back(*it);
		reallist2.push_back(*it);
	}

	list.splice(it, list2);
	reallist.splice(realit, reallist2);

	testSizeAndContent(list, reallist);
	testSizeAndContent(list2, reallist2);
}

TYPED_TEST(list_tester, splice_test_single_element) {
	ft::list<TypeParam>	list;
	std::list<TypeParam>	reallist;
	initialise_default_list(list, reallist);
	ft::list<TypeParam>	list2;
	std::list<TypeParam>	reallist2;
	initialise_default_list(list2, reallist2);

	typename ft::list<TypeParam>::iterator		it = list.begin();
	typename std::list<TypeParam>::iterator		realit = reallist.begin();
	typename ft::list<TypeParam>::iterator		tmpit = list2.begin();
	typename std::list<TypeParam>::iterator		tmprealit = reallist2.begin();

	it = incrementIterator(it, list.size() / 2);
	realit = incrementIterator(realit, reallist.size() / 2);
	tmpit = incrementIterator(tmpit, list2.size() / 4);
	tmprealit = incrementIterator(tmprealit, reallist2.size() / 4);

	list.splice(it, list2, tmpit);
	reallist.splice(realit, reallist2, tmprealit);

	testSizeAndContent(list, reallist);
	testSizeAndContent(list2, reallist2);

	tmpit = list2.begin();
	tmprealit = reallist2.begin();

	list.splice(it, list2, tmpit);
	reallist.splice(realit, reallist2, tmprealit);

	testSizeAndContent(list, reallist);
	testSizeAndContent(list2, reallist2);

	tmpit = incrementIterator(tmpit, 3);
	tmprealit = incrementIterator(tmprealit, 3);

	list.splice(it, list2, tmpit);
	reallist.splice(realit, reallist2, tmprealit);

	testSizeAndContent(list, reallist);
	testSizeAndContent(list2, reallist2);
}

TYPED_TEST(list_tester, splice_test_range) {
	ft::list<TypeParam>	list;
	std::list<TypeParam>	reallist;
	initialise_default_list(list, reallist);
	ft::list<TypeParam>	list2;
	std::list<TypeParam>	reallist2;
	initialise_default_list(list2, reallist2);

	std::vector<TypeParam>	scrapVec;
	initialise_scrap_vector(scrapVec);

	for (typename std::vector<TypeParam>::iterator it = scrapVec.begin(); it != scrapVec.end(); it++) {
		list2.push_back(*it);
		reallist2.push_back(*it);
	}

	list.splice(list.begin(), list2, incrementIterator(list2.begin(), 4), list2.end());
	reallist.splice(reallist.begin(), reallist2,
			incrementIterator(reallist2.begin(), 4), reallist2.end());

	testSizeAndContent(list, reallist);
	testSizeAndContent(list2, reallist2);
}

TYPED_TEST(list_tester, remove_test) {
	ft::list<TypeParam>	list;
	std::list<TypeParam>	reallist;
	initialise_default_list(list, reallist);

	std::vector<TypeParam>	scrapVec;
	initialise_scrap_vector(scrapVec);

	testSizeAndContent(list, reallist);

	list.remove(scrapVec.back());
	reallist.remove(scrapVec.back());

	testSizeAndContent(list, reallist);
}

TYPED_TEST(list_tester, remove_if_test) {
	ft::list<TypeParam>	list;
	std::list<TypeParam>	reallist;
	initialise_default_list(list, reallist);
	bool		(*func)(TypeParam const&) = predicate_func;

	list.remove_if(func);
	reallist.remove_if(func);

	testSizeAndContent(list, reallist);
}

TYPED_TEST(list_tester, unique_void_test) {
	std::vector<TypeParam>	scrapVec;
	initialise_scrap_vector(scrapVec);

	ft::list<TypeParam>	list(20, scrapVec.front());
	std::list<TypeParam>	reallist(20, scrapVec.front());

	for (int i = 0; i < 3; i++) {
		list.push_front(scrapVec.back());
		reallist.push_front(scrapVec.back());
	}
	testSizeAndContent(list, reallist);

	list.unique();
	reallist.unique();

	testSizeAndContent(list, reallist);
}

TYPED_TEST(list_tester, unique_predicate_test) {
	std::vector<TypeParam>	scrapVec;
	initialise_scrap_vector(scrapVec);
	bool		(*func)(TypeParam const&, TypeParam const&) = binary_predicate_func;

	ft::list<TypeParam>	list(20, scrapVec.front());
	std::list<TypeParam>	reallist(20, scrapVec.front());

	for (int i = 0; i < 3; i++) {
		list.push_front(scrapVec.back());
		reallist.push_front(scrapVec.back());
	}
	testSizeAndContent(list, reallist);

	list.unique(func);
	reallist.unique(func);

	testSizeAndContent(list, reallist);
}

TYPED_TEST(list_tester, merge_standard_test) {
	ft::list<TypeParam>	list;
	std::list<TypeParam>	reallist;
	initialise_sorted_list(list, reallist);
	std::vector<TypeParam>	scrapVec;
	initialise_scrap_vector(scrapVec);
	ft::list<TypeParam>	list2;
	std::list<TypeParam>	reallist2;

	for (typename std::vector<TypeParam>::iterator it = scrapVec.begin(); it != scrapVec.end(); it++) {
		list2.push_back(*it);
		reallist2.push_back(*it);
	}

	list.merge(list2);
	reallist.merge(reallist2);

	testSizeAndContent(list, reallist);
	testSizeAndContent(list2, reallist2);
}

TYPED_TEST(list_tester, merge_predicate_test) {
	ft::list<TypeParam>	list;
	std::list<TypeParam>	reallist;
	initialise_sorted_list(list, reallist);
	std::vector<TypeParam>	scrapVec;
	initialise_scrap_vector(scrapVec);
	ft::list<TypeParam>	list2;
	std::list<TypeParam>	reallist2;
	bool	(*func)(TypeParam const&, TypeParam const&) = moreThanFunc;

	for (typename std::vector<TypeParam>::iterator it = scrapVec.begin(); it != scrapVec.end(); it++) {
		list2.push_back(*it);
		reallist2.push_back(*it);
	}
	list.reverse();
	list2.reverse();
	reallist.reverse();
	reallist2.reverse();

	list.merge(list2, func);
	reallist.merge(reallist2, func);

	testSizeAndContent(list, reallist);
	testSizeAndContent(list2, reallist2);
}

TYPED_TEST(list_tester, sort_standard_test) {
	ft::list<TypeParam>	list;
	std::list<TypeParam>	reallist;
	initialise_default_list(list, reallist);

	list.sort();
	reallist.sort();

	testSizeAndContent(list, reallist);
}

TYPED_TEST(list_tester, sort_custom_test) {
	ft::list<TypeParam>	list;
	std::list<TypeParam>	reallist;
	initialise_default_list(list, reallist);
	bool	(*func)(TypeParam const&, TypeParam const&) = moreThanFunc;

	list.sort(func);
	reallist.sort(func);

	testSizeAndContent(list, reallist);
}

TYPED_TEST(list_tester, reverse_test) {
	ft::list<TypeParam>	list;
	std::list<TypeParam>	reallist;
	initialise_default_list(list, reallist);

	list.reverse();
	reallist.reverse();

	testSizeAndContent(list, reallist);
}

TYPED_TEST(list_tester, fill_constructor_test) {
	std::vector<TypeParam>	scrapVec;
	initialise_scrap_vector(scrapVec);

	ft::list<TypeParam>	list(20, scrapVec.front());
	std::list<TypeParam>	reallist(20, scrapVec.front());

	testSizeAndContent(list, reallist);
}

TYPED_TEST(list_tester, range_constructor_test) {
	std::vector<TypeParam>	scrapVec;
	initialise_scrap_vector(scrapVec);

	ft::list<TypeParam>	list(scrapVec.begin(), scrapVec.end());
	std::list<TypeParam>	reallist(scrapVec.begin(), scrapVec.end());

	testSizeAndContent(list, reallist);
}

TYPED_TEST(list_tester, relational_operators_test) {
	ft::list<TypeParam>	list;
	std::list<TypeParam>	reallist;
	initialise_default_list(list, reallist);

	ft::list<TypeParam>	listCopy(list);
	std::list<TypeParam>	reallistCopy(reallist);

	ASSERT_EQ((list == listCopy), (reallist == reallistCopy));
	ASSERT_EQ((list != listCopy), (reallist != reallistCopy));
	ASSERT_EQ((list < listCopy), (reallist < reallistCopy));
	ASSERT_EQ((listCopy < list), (reallistCopy < reallist));
	ASSERT_EQ((list <= listCopy), (reallist <= reallistCopy));
	ASSERT_EQ((listCopy <= list), (reallistCopy <= reallist));
	ASSERT_EQ((list >= listCopy), (reallist >= reallistCopy));
	ASSERT_EQ((listCopy >= list), (reallistCopy >= reallist));
	ASSERT_EQ((list > listCopy), (reallist > reallistCopy));
	ASSERT_EQ((listCopy > list), (reallistCopy > reallist));
	addition_to_list(list, reallist);
	ASSERT_EQ((list == listCopy), (reallist == reallistCopy));
	ASSERT_EQ((list != listCopy), (reallist != reallistCopy));
	ASSERT_EQ((list < listCopy), (reallist < reallistCopy));
	ASSERT_EQ((listCopy < list), (reallistCopy < reallist));
	ASSERT_EQ((list <= listCopy), (reallist <= reallistCopy));
	ASSERT_EQ((listCopy <= list), (reallistCopy <= reallist));
	ASSERT_EQ((list >= listCopy), (reallist >= reallistCopy));
	ASSERT_EQ((listCopy >= list), (reallistCopy >= reallist));
	ASSERT_EQ((list > listCopy), (reallist > reallistCopy));
	ASSERT_EQ((listCopy > list), (reallistCopy > reallist));
}

TYPED_TEST(list_tester, iterator_increment_tests) {
	ft::list<TypeParam>	list;
	std::list<TypeParam>	reallist;
	initialise_default_list(list, reallist);

	typename ft::list<TypeParam>::const_iterator	it = list.begin();
	typename std::list<TypeParam>::const_iterator	real_it = reallist.begin();

	for (; it != list.end(); it++, real_it++)
		ASSERT_EQ(*it, *real_it);
}

TYPED_TEST(list_tester, iterator_decrement_tests) {
	ft::list<TypeParam>	list;
	std::list<TypeParam>	reallist;
	initialise_default_list(list, reallist);

	typename ft::list<TypeParam>::const_iterator	it = decrementIterator(list.end(), 1);
	typename std::list<TypeParam>::const_iterator	real_it = decrementIterator(reallist.end(), 1);

	for (; it != list.begin(); it--, real_it--)
		ASSERT_EQ(*it, *real_it);
}

TYPED_TEST(list_tester, iterator_relational_operators_tests) {
	ft::list<TypeParam>	list;
	std::list<TypeParam>	reallist;
	initialise_default_list(list, reallist);

	typename ft::list<TypeParam>::const_iterator	it = list.begin();
	typename std::list<TypeParam>::const_iterator	real_it = reallist.begin();

	typename ft::list<TypeParam>::const_iterator	it2 = it;
	typename std::list<TypeParam>::const_iterator	real_it2 = real_it;

	ASSERT_EQ((it == it2), (real_it == real_it2));
	it++;
	real_it++;
	ASSERT_EQ((it == it2), (real_it == real_it2));
	ASSERT_EQ((it != it2), (real_it != real_it2));

	/* compare non-const to const iterators */
	typename ft::list<TypeParam>::iterator	nc_it = incrementIterator(list.begin(), 1);
	typename std::list<TypeParam>::iterator	nc_real_it = incrementIterator(reallist.begin(), 1);

	ASSERT_EQ((it == nc_it), (real_it == nc_real_it));
	ASSERT_EQ((it != nc_it), (real_it != nc_real_it));
	nc_it++;
	nc_real_it++;
	ASSERT_EQ((it == nc_it), (real_it == nc_real_it));
	ASSERT_EQ((it != nc_it), (real_it != nc_real_it));
}

TYPED_TEST(list_tester, iterator_modification_tests) {
	ft::list<TypeParam>	list;
	std::list<TypeParam>	reallist;
	initialise_default_list(list, reallist);

	testSizeAndContent(list, reallist);

	typename ft::list<TypeParam>::iterator	it = list.begin();
	typename std::list<TypeParam>::iterator	real_it = reallist.begin();
	for (; it != list.end(); it++, real_it++) {
		addition_func(*it);
		addition_func(*real_it);
	}
	testSizeAndContent(list, reallist);

	it = list.begin();
	real_it = reallist.begin();
	for (; it != list.end(); it++, real_it++) {
		subtraction_func(*it);
		subtraction_func(*real_it);
	}
	testSizeAndContent(list, reallist);

	it = list.begin();
	real_it = reallist.begin();
	for (; it != list.end(); it++, real_it++) {
		multiplication_func(*it);
		multiplication_func(*real_it);
	}
	testSizeAndContent(list, reallist);
}

TYPED_TEST(list_tester, reverse_iterator_increment_tests) {
	ft::list<TypeParam>	list;
	std::list<TypeParam>	reallist;
	initialise_default_list(list, reallist);

	typename ft::list<TypeParam>::const_reverse_iterator	it = list.rbegin();
	typename std::list<TypeParam>::const_reverse_iterator	real_it = reallist.rbegin();

	for (; it != list.rend(); it++, real_it++)
		ASSERT_EQ(*it, *real_it);
}

TYPED_TEST(list_tester, reverse_iterator_decrement_tests) {
	ft::list<TypeParam>	list;
	std::list<TypeParam>	reallist;
	initialise_default_list(list, reallist);

	typename ft::list<TypeParam>::const_reverse_iterator	it = decrementIterator(list.rend(), 1);
	typename std::list<TypeParam>::const_reverse_iterator	real_it = decrementIterator(reallist.rend(), 1);

	for (; it != list.rbegin(); it--, real_it--)
		ASSERT_EQ(*it, *real_it);
	it = list.rbegin();
	real_it = reallist.rbegin();
	it = incrementIterator(it, 3);
	real_it = incrementIterator(real_it, 3);
	ASSERT_EQ(*it, *real_it);
	it = decrementIterator(it, 2);
	real_it = decrementIterator(real_it, 2);
	ASSERT_EQ(*it, *real_it);

	typename ft::list<TypeParam>::const_reverse_iterator	it2 = incrementIterator(list.rbegin(), 4);
	typename std::list<TypeParam>::const_reverse_iterator	real_it2 = incrementIterator(reallist.rbegin(), 4);

	it2 = it;
	real_it2 = real_it;
	ASSERT_EQ(*it2, *real_it);
	ASSERT_EQ(*it, *real_it2);
}

TYPED_TEST(list_tester, iterator_reverse_relational_operators_tests) {
	ft::list<TypeParam>	list;
	std::list<TypeParam>	reallist;
	initialise_default_list(list, reallist);

	typename ft::list<TypeParam>::const_reverse_iterator	it = list.rbegin();
	typename std::list<TypeParam>::const_reverse_iterator	real_it = reallist.rbegin();

	typename ft::list<TypeParam>::const_reverse_iterator	it2 = it;
	typename std::list<TypeParam>::const_reverse_iterator	real_it2 = real_it;

	ASSERT_EQ((it == it2), (real_it == real_it2));
	it++;
	real_it++;
	ASSERT_EQ((it == it2), (real_it == real_it2));
	ASSERT_EQ((it != it2), (real_it != real_it2));

	/* compare non-const to const iterators */
	typename ft::list<TypeParam>::reverse_iterator	nc_it = incrementIterator(list.rbegin(), 1);
	typename std::list<TypeParam>::reverse_iterator	nc_real_it = incrementIterator(reallist.rbegin(), 1);

	ASSERT_EQ((it == nc_it), (real_it == nc_real_it));
	ASSERT_EQ((it != nc_it), (real_it != nc_real_it));
	nc_it++;
	nc_real_it++;
	ASSERT_EQ((it == nc_it), (real_it == nc_real_it));
	ASSERT_EQ((it != nc_it), (real_it != nc_real_it));
}

TYPED_TEST(list_tester, iterator_reverse_construction_tests) {
	ft::list<TypeParam>	list;
	std::list<TypeParam>	reallist;
	initialise_default_list(list, reallist);

	typename ft::list<TypeParam>::const_iterator	it = list.begin();
	typename std::list<TypeParam>::const_iterator	real_it = reallist.begin();
	typename ft::list<TypeParam>::const_reverse_iterator	rit = list.rbegin();
	typename std::list<TypeParam>::const_reverse_iterator	real_rit = reallist.rbegin();

	typename ft::list<TypeParam>::reverse_iterator	nc_rit(list.rbegin());
	typename std::list<TypeParam>::reverse_iterator	nc_real_rit(reallist.rbegin());
	typename ft::list<TypeParam>::const_reverse_iterator	rit2(nc_rit);
	typename std::list<TypeParam>::const_reverse_iterator	real_rit2(nc_real_rit);

	ASSERT_EQ(*it, *real_it);
	ASSERT_EQ(*rit, *real_rit);
	ASSERT_EQ(*nc_rit, *nc_real_rit);
	ASSERT_EQ(*rit2, *real_rit2);
}

TYPED_TEST(list_tester, iterator_reverse_modification_tests) {
	ft::list<TypeParam>	list;
	std::list<TypeParam>	reallist;
	initialise_default_list(list, reallist);

	testSizeAndContent(list, reallist);

	typename ft::list<TypeParam>::reverse_iterator	it = list.rbegin();
	typename std::list<TypeParam>::reverse_iterator	real_it = reallist.rbegin();
	for (; it != list.rend(); it++, real_it++) {
		addition_func(*it);
		addition_func(*real_it);
	}
	testSizeAndContent(list, reallist);

	it = list.rbegin();
	real_it = reallist.rbegin();
	for (; it != list.rend(); it++, real_it++) {
		subtraction_func(*it);
		subtraction_func(*real_it);
	}
	testSizeAndContent(list, reallist);

	it = list.rbegin();
	real_it = reallist.rbegin();
	for (; it != list.rend(); it++, real_it++) {
		multiplication_func(*it);
		multiplication_func(*real_it);
	}
	testSizeAndContent(list, reallist);
}

TYPED_TEST(list_tester, iterator_reverse_base_test) {
	ft::list<TypeParam>	list;
	std::list<TypeParam>	reallist;
	initialise_default_list(list, reallist);

	typename ft::list<TypeParam>::reverse_iterator	nc_rit(incrementIterator(list.rbegin(), 1));
	typename std::list<TypeParam>::reverse_iterator	nc_real_rit(incrementIterator(reallist.rbegin(), 1));
	typename ft::list<TypeParam>::const_reverse_iterator	rit2(incrementIterator(nc_rit, 3));
	typename std::list<TypeParam>::const_reverse_iterator	real_rit2(incrementIterator(nc_real_rit, 3));

	ASSERT_EQ(*(nc_rit.base()), *(nc_real_rit.base()));
	ASSERT_EQ(*(rit2.base()), *(real_rit2.base()));
}
