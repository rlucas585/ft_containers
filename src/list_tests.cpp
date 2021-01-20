/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_tests.cpp                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/20 11:02:33 by rlucas        #+#    #+#                 */
/*   Updated: 2021/01/20 16:11:52 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <list>

#include "colors.hpp"
#include "utils.hpp"
#include "test.hpp"
#include "list.hpp"

template <typename T, typename U>
static void	print_fake_and_real(T fake, const char *fake_name,
		U real, const char *real_name) {
	std::cout << std::boolalpha;
	std::cout << fake_name << ": " << std::setw(5) << fake;
	std::cout << " | " << real_name << ": " << std::setw(5) << real;
	std::cout << std::endl;
}

template <typename T>
static void	print_list(T &list) {
	typename T::const_iterator it = list.begin();

	std::cout << "[";
	while (it != list.end()) {
		std::cout << *it << ", ";
		it++;
	}
	std::cout << "]";
}

template <typename T, typename U>
static void	print_fake_and_real_collection(T &fake, const char *fake_name,
		U &real, const char *real_name) {
	std::cout << fake_name << ": ";
	print_list(fake);
	std::cout << std::endl;
	std::cout << real_name << ": ";
	print_list(real);
	std::cout << std::endl;
}

static void	int_add_func(int &n) { n += 2; }
static void	int_sub_func(int &n) { n -= 2; }
static void	int_mul_func(int &n) { n *= 4; }
// static void	string_add_func(std::string &s) { if (s.size() == 0) { return ; } else { s[0] += 1; } }
// static void	string_sub_func(std::string &s) { if (s.size() == 0) { return ; } else { s[0] -= 1; } }

static void	int_list_tests(void (*f1)(int &n), void (*f2)(int &n), void (*f3)(int &n)) {
	print_divider(CYAN, "ft::list<int> tests");

	(void)f1;(void)f2;(void)f3;
	ft::list<int>		list;
	std::list<int>		reallist;
	// std::list<int>		newvals;
	

	print_info(WHITE, "push_front(), and front() and back() tests");
	print_fake_and_real(list.empty(), "ft::list empty", reallist.empty(), "std::list empty");
	list.push_front(5);
	reallist.push_front(5);
	print_fake_and_real(list.front(), "ft::list front", reallist.front(), "std::list front");
	print_fake_and_real(list.back(), "ft::list back", reallist.back(), "std::list back");
	list.push_front(10);
	reallist.push_front(10);
	print_fake_and_real(list.front(), "ft::list front", reallist.front(), "std::list front");
	print_fake_and_real(list.back(), "ft::list back", reallist.back(), "std::list back");
	print_fake_and_real(list.size(), "ft::list size", reallist.size(), "std::list size");
	print_fake_and_real(list.empty(), "ft::list empty", reallist.empty(), "std::list empty");

	print_info(WHITE, "push_back() tests");
	print_fake_and_real(list.empty(), "ft::list empty", reallist.empty(), "std::list empty");
	list.push_back(5);
	reallist.push_back(5);

	print_fake_and_real_collection(list, "ft::list", reallist, "std::list");

	list.push_back(10);
	reallist.push_back(10);
	print_fake_and_real_collection(list, "ft::list", reallist, "std::list");
	print_fake_and_real(list.size(), "ft::list size", reallist.size(), "std::list size");
	print_fake_and_real(list.empty(), "ft::list empty", reallist.empty(), "std::list empty");

	print_info(WHITE, "pop_front() tests");
	list.pop_front();
	reallist.pop_front();
	print_fake_and_real(list.size(), "ft::list size", reallist.size(), "std::list size");
	print_fake_and_real(list.front(), "ft::list front", reallist.front(), "std::list front");
	print_fake_and_real(list.back(), "ft::list back", reallist.back(), "std::list back");
	while (!list.empty()) {
		list.pop_front();
		reallist.pop_front();
	}
	print_fake_and_real(list.size(), "ft::list size", reallist.size(), "std::list size");

	print_info(WHITE, "pop_back() tests");
	for (unsigned int i = 0; i < 4; i++) {
		list.push_back(2 * i);
		reallist.push_back(2 * i);
	}
	print_fake_and_real(list.size(), "ft::list size", reallist.size(), "std::list size");
	print_fake_and_real(list.front(), "ft::list front", reallist.front(), "std::list front");
	print_fake_and_real(list.back(), "ft::list back", reallist.back(), "std::list back");
	while (!list.empty()) {
		list.pop_back();
		reallist.pop_back();
	}
	print_fake_and_real(list.size(), "ft::list size", reallist.size(), "std::list size");

	print_line(CYAN);
}

void	list_tests(bool int_test, bool string_test, bool object_test) {
	(void)string_test;
	(void)object_test;
	if (int_test)
		int_list_tests(int_add_func, int_sub_func, int_mul_func);
	// if (string_test)
	// 	string_list_tests(string_add_func, string_sub_func);
	// if (object_test)
	// 	any_object_tests();
}
