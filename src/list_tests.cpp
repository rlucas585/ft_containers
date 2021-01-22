/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_tests.cpp                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/20 11:02:33 by rlucas        #+#    #+#                 */
/*   Updated: 2021/01/22 13:54:56 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <list>
#include <vector>

#include "colors.hpp"
#include "utils.hpp"
#include "test.hpp"
#include "list.hpp"
#include "vector.hpp"

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

// I made this just to check the reverse iteration...
template <typename T>
static void	print_list_reverse(T &list) {
	typename T::const_reverse_iterator it = list.rbegin();

	std::cout << "[";
	while (it != list.rend()) {
		std::cout << *it << ", ";
		it++;
	}
	std::cout << "]";
}

template <typename T, typename U>
static void	print_fake_and_real_collection(T &fake, const char *fake_name,
		U &real, const char *real_name) {
	std::cout << fake_name << " (forward): ";
	print_list(fake);
	std::cout << std::endl;
	std::cout << real_name << " (forward): ";
	print_list(real);
	std::cout << std::endl;
}

template <typename T, typename U>
static void	print_fake_and_real_collection_reverse(T &fake, const char *fake_name,
		U &real, const char *real_name) {
	std::cout << fake_name << " (reverse): ";
	print_list_reverse(fake);
	std::cout << std::endl;
	std::cout << real_name << " (reverse): ";
	print_list_reverse(real);
	std::cout << std::endl;
}

static void	int_add_func(int &n) { n += 2; }
static void	int_sub_func(int &n) { n -= 2; }
static void	int_mul_func(int &n) { n *= 4; }
// static void	string_add_func(std::string &s) { if (s.size() == 0) { return ; } else { s[0] += 1; } }
// static void	string_sub_func(std::string &s) { if (s.size() == 0) { return ; } else { s[0] -= 1; } }

static void fill_int_list(ft::list<int> &list, std::list<int> &reallist) {
	list.clear();
	reallist.clear();
	for (unsigned int i = 0; i < 4; i++) {
		list.push_back(2 * i);
		reallist.push_back(2 * i);
	}
}

template <typename T>
static void	print_fake_and_real_info(ft::list<T> const& list, std::list<T> const& reallist) {
	print_fake_and_real(list.size(), "ft::list size", reallist.size(), "std::list size");
	print_fake_and_real_collection(list, "ft::list", reallist, "std::list");
}

template <typename T>
static void	print_fake_and_real_info(ft::list<T> const& list, const char *label1,
		std::list<T> const& reallist, const char *label2) {
	std::string		label3(label1);
	std::string		label4(label2);

	label3 += " size";
	label4 += " size";
	print_fake_and_real(list.size(), label3.c_str(), reallist.size(), label4.c_str());
	print_fake_and_real_collection(list, label1, reallist, label2);
}

template <typename T>
static void swap_test(ft::list<T> &list, std::list<T> &reallist) {
	print_info(WHITE, "Assignment (=) test");
	print_fake_and_real_info(list, reallist);
	std::cout << "Assigning..." << std::endl;
	ft::list<int>	tmp1 = list;
	std::list<int>	tmp2 = reallist;
	while (tmp1.size() > 2) {
		tmp1.pop_back();
		tmp2.pop_back();
	}
	print_info(WHITE, "swap() test");
	print_fake_and_real_info(list, reallist);
	print_fake_and_real_info(tmp1, "tmp1", tmp2, "tmp2");
	std::cout << "Swapping..." << std::endl;
	tmp1.swap(list);
	tmp2.swap(reallist);
	print_fake_and_real_info(list, reallist);
	print_fake_and_real_info(tmp1, "tmp1", tmp2, "tmp2");
	tmp1.swap(list);
	tmp2.swap(reallist);
}

template <typename T>
static void reverse_test(ft::list<T> &list, std::list<T> &reallist) {
	print_info(WHITE, "reverse() test");
	print_fake_and_real_info(list, reallist);
	list.reverse();
	reallist.reverse();
	print_fake_and_real_info(list, reallist);
}


ft::list<int>		create_tmp_list(void) {
	ft::list<int>		tmp;
	for (int i = 3; i < 20; i += 3)
		tmp.push_back(i);
	return tmp;
}

std::list<int>		create_tmp_list_real(void) {
	std::list<int>		tmp;
	for (int i = 3; i < 20; i += 3)
		tmp.push_back(i);
	return tmp;
}

template <typename T>
static void assign_test(ft::list<T> &list, std::list<T> &reallist) {
	ft::list<T>		tmplist = create_tmp_list();
	std::list<T>	tmpreallist = create_tmp_list_real();
	print_info(WHITE, "assign() test 1 (range)");
	print_fake_and_real_info(list, reallist);
	std::cout << "assign() called..." << std::endl;
	list.assign(tmplist.begin(), tmplist.end());
	reallist.assign(tmpreallist.begin(), tmpreallist.end());
	print_fake_and_real_info(list, reallist);
	print_info(WHITE, "assign() test 2 (fill)");
	list.assign(4, tmplist.front());
	reallist.assign(4, tmpreallist.front());
	print_fake_and_real_info(list, reallist);
}

template <typename T>
static void	insert_test(ft::list<T> &list, std::list<T> &reallist) {
	ft::list<T>		tmplist = create_tmp_list();
	std::list<T>	tmpreallist = create_tmp_list_real();
	typename ft::list<T>::iterator		it = list.begin();
	typename std::list<T>::iterator		realit = reallist.begin();

	// Both of these should be compile errors
	// typename ft::list<T>::iterator		fake_it = 0;
	// typename std::list<T>::iterator		fake_realit = 0;
	typename ft::list<T>::iterator		fake_it;
	typename std::list<T>::iterator		fake_realit;
	print_info(WHITE, "insert() test 1 (single element)");
	print_fake_and_real_info(list, reallist);
	for (size_t i = 0; i < list.size() / 2; i++) {
		it++;
		realit++;
	}
	print_fake_and_real(*list.insert(it, tmplist.front()), "ft::vector (insert ret)",
			*reallist.insert(realit, tmpreallist.front()), "std::vector (insert ret)");
	print_fake_and_real_info(list, reallist);

	print_info(WHITE, "insert() test 1.5 (single element at front)");
	print_fake_and_real(*list.insert(list.begin(), tmplist.front()), "ft::vector (insert ret)",
			*reallist.insert(reallist.begin(), tmpreallist.front()), "std::vector (insert ret)");
	print_fake_and_real_info(list, reallist);

	// Both of these should seg fault
	// print_info(WHITE, "insert() test 1.5.5 (invalid iterator)");
	// reallist.insert(fake_realit, tmpreallist.front());
	// list.insert(fake_it, tmplist.front());
	// print_fake_and_real_info(list, reallist);

	print_info(WHITE, "insert() test 2 (fill)");
	it++;
	realit++;
	list.insert(it, 5, tmplist.back());
	reallist.insert(realit, 5, tmpreallist.back());
	print_fake_and_real_info(list, reallist);
	print_info(WHITE, "insert() test 3 (range)");
	it = list.begin();
	realit = reallist.begin();
	for (size_t i = 0; i < 6; i++) {
		it++;
		realit++;
	}
	list.insert(it, tmplist.begin(), tmplist.end());
	reallist.insert(realit, tmpreallist.begin(), tmpreallist.end());
	print_fake_and_real_info(list, reallist);
}

template <typename T>
static void	erase_test(ft::list<T> &list, std::list<T> &reallist) {
	ft::list<T>		tmplist = create_tmp_list();
	std::list<T>	tmpreallist = create_tmp_list_real();
	typename ft::list<T>::iterator		it = list.begin();
	typename std::list<T>::iterator		realit = reallist.begin();

	print_info(WHITE, "erase() test 1 (single element)");
	for (size_t i = 0; i < 2; i++) {
		it++;
		realit++;
	}
	list.insert(it, tmplist.begin(), tmplist.end());
	reallist.insert(realit, tmpreallist.begin(), tmpreallist.end());
	for (size_t i = 0; i < tmplist.size() / 2; i++) {
		it--;
		realit--;
	}
	print_fake_and_real_info(list, reallist);
	print_fake_and_real(*list.erase(it), "ft::vector (erase ret)",
			*reallist.erase(realit), "std::vector (erase ret)");
	print_fake_and_real_info(list, reallist);

	it = list.begin();
	realit = reallist.begin();
	for (size_t i = 0; i < list.size() / 2; i++) {
		it++;
		realit++;
	}
	print_info(WHITE, "erase() test 2 (range)");
	print_fake_and_real(*list.erase(list.begin(), it), "ft::vector (erase ret)",
			*reallist.erase(reallist.begin(), realit), "std::vector (erase ret)");
	print_fake_and_real_info(list, reallist);
}

template <typename T>
static void	resize_test(ft::list<T> &list, std::list<T> &reallist) {
	ft::list<T>		tmplist = create_tmp_list();
	print_info(WHITE, "resize() test 1 (reduce size)");
	print_fake_and_real_info(list, reallist);
	list.resize(3);
	reallist.resize(3);
	print_fake_and_real_info(list, reallist);
	print_info(WHITE, "resize() test 2 (increase size)");
	list.resize(15, tmplist.front());
	reallist.resize(15, tmplist.front());
	print_fake_and_real_info(list, reallist);
}

template <typename T>
static void	max_size_test(ft::list<T> &list, std::list<T> &reallist) {
	print_info(WHITE, "max_size() test");
	print_fake_and_real(list.max_size(), "ft::vector", reallist.max_size(), "std::vector");
}

template <typename T>
static void	splice_test(ft::list<T> &list, std::list<T> &reallist) {
	ft::list<T>		tmplist = create_tmp_list();
	std::list<T>	tmpreallist = create_tmp_list_real();
	typename ft::list<T>::iterator		it = list.begin();
	typename std::list<T>::iterator		realit = reallist.begin();
	typename ft::list<T>::iterator		tmpit = tmplist.begin();
	typename std::list<T>::iterator		tmprealit = tmpreallist.begin();

	for (size_t i = 0; i < tmplist.size() / 2; i++) {
		it++;
		realit++;
		tmpit++;
		tmprealit++;
	}
	print_info(WHITE, "splice() test 2 (single element)");
	print_fake_and_real_info(list, reallist);
	print_fake_and_real_info(tmplist, "srclist (ft): ", tmpreallist, "srclist (std):");
	list.splice(it, tmplist, tmpit);
	reallist.splice(realit, tmpreallist, tmprealit);
	print_fake_and_real_info(list, reallist);
	print_fake_and_real_info(tmplist, "srclist (ft): ", tmpreallist, "srclist (std):");

	tmpit = tmplist.begin();
	tmprealit = tmpreallist.begin();
	for (size_t i = 0; i < tmplist.size() / 2; i++) {
		tmpit++;
		tmprealit++;
	}
	print_info(WHITE, "splice() test 3 (range)");
	list.splice(list.begin(), tmplist, tmpit, tmplist.end());
	reallist.splice(reallist.begin(), tmpreallist, tmprealit, tmpreallist.end());
	print_fake_and_real_info(list, reallist);
	print_fake_and_real_info(tmplist, "srclist (ft): ", tmpreallist, "srclist (std):");

	print_info(WHITE, "splice() test 1 (all elements)");
	list.splice(it, tmplist);
	reallist.splice(realit, tmpreallist);
	print_fake_and_real_info(list, reallist);
	print_fake_and_real_info(tmplist, "srclist (ft): ", tmpreallist, "srclist (std):");
}

template <typename T>
static void	reverse_iterator_test(ft::list<T> &list, std::list<T> &reallist) {
	typename ft::list<T>::iterator				it = list.begin();
	typename ft::list<T>::reverse_iterator		rit = list.rend();
	typename std::list<T>::iterator				realit = reallist.begin();
	typename std::list<T>::reverse_iterator		realrit = reallist.rend();

	print_info(WHITE, "Reverse iterator comparison test");

	// Can be used to prove a concept - but relies on uninitialised data,
	// so will create an error in valgrind
	// print_fake_and_real((*it == *(rit)), "ft::vector", (*realit == *(realrit)), "std::vector");
	rit--;
	realrit--;
	print_fake_and_real((*it == *(rit)), "ft::vector", (*realit == *(realrit)), "std::vector");
}

static void	int_list_tests(void (*f1)(int &n), void (*f2)(int &n), void (*f3)(int &n)) {
	print_divider(CYAN, "ft::list<int> tests");

	(void)f1;(void)f2;(void)f3;
	ft::list<int>		list;
	std::list<int>		reallist;
	// std::list<int>		newvals;
	

	print_info(WHITE, "push_front(), front(), back() and empty() tests");
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
	list.push_back(5);
	reallist.push_back(5);

	print_fake_and_real_info(list, reallist);
	print_info(WHITE, "reverse_iterator print tests");
	print_fake_and_real_collection_reverse(list, "ft::list", reallist, "std::list");

	list.push_back(10);
	reallist.push_back(10);
	print_fake_and_real_info(list, reallist);

	print_info(WHITE, "pop_front() tests");
	list.pop_front();
	reallist.pop_front();
	print_fake_and_real_info(list, reallist);
	while (!list.empty()) {
		list.pop_front();
		reallist.pop_front();
	}
	print_fake_and_real_info(list, reallist);

	print_info(WHITE, "pop_back() tests");
	fill_int_list(list, reallist);
	print_fake_and_real_info(list, reallist);
	while (!list.empty()) {
		list.pop_back();
		reallist.pop_back();
	}
	print_fake_and_real_info(list, reallist);

	print_info(WHITE, "clear() test");
	fill_int_list(list, reallist);
	print_fake_and_real_info(list, reallist);
	list.clear();
	reallist.clear();
	print_fake_and_real_info(list, reallist);

	fill_int_list(list, reallist);
	swap_test(list, reallist);

	reverse_test(list, reallist);

	fill_int_list(list, reallist);
	assign_test(list, reallist);

	reverse_iterator_test(list, reallist);

	fill_int_list(list, reallist);
	insert_test(list, reallist);

	fill_int_list(list, reallist);
	erase_test(list, reallist);

	fill_int_list(list, reallist);
	fill_int_list(list, reallist);
	resize_test(list, reallist);

	fill_int_list(list, reallist);
	max_size_test(list, reallist);

	splice_test(list, reallist);

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
