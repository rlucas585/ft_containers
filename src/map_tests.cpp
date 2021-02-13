/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_tests.cpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/29 09:30:03 by rlucas        #+#    #+#                 */
/*   Updated: 2021/02/13 15:31:37 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <map>

#include "colors.hpp"
#include "utils.hpp"
#include "test.hpp"
#include "vector.hpp"

static void	int_map_tests(void (*f1)(int &n), void (*f2)(int &n), void (*f3)(int &n)) {
	print_divider(CYAN, "ft::map<int> tests");

	(void)f1;(void)f2;(void)f3;
	ft::map<int, int>			map;
	std::map<int, int>		realmap;

	print_line(CYAN);
}

static void	int_add_func(int &n) { n += 2; }
static void	int_sub_func(int &n) { n -= 2; }
static void	int_mul_func(int &n) { n *= 4; }

void	map_tests(bool int_test, bool string_test, bool object_test) {
	(void)string_test;
	(void)object_test;
	if (int_test)
		int_map_tests(int_add_func, int_sub_func, int_mul_func);
	// if (string_test)
	// 	string_vector_tests(string_add_func, string_sub_func, string_not_func);
	// if (object_test)
	// 	any_object_tests();
}
