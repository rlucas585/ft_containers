/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <ryanl585codam@gmail.com>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/06 12:49:55 by rlucas        #+#    #+#                 */
/*   Updated: 2021/01/17 17:08:14 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>

#include "colors.hpp"
#include "utils.hpp"
#include "Vector.hpp"

template <typename T>
void	try_index(ft::vector<T> &vec, size_t i) {
	T		val;
	try {
		val = vec[i];
		std::cout << "Index " << i << ": " << val << std::endl;
	} catch (std::exception &e) {
		std::cerr << "Error " << ": " << e.what() << std::endl;
	}
}

template <typename T>
void	print_vector(T &vec) {
	std::cout << "[";
	for (unsigned int i = 0; i < vec.size(); i++) {
		if (i == vec.size() - 1)
			std::cout << vec[i] << "]";
		else
			std::cout << vec[i] << ", ";
	}
}

template <typename T, typename U>
void	print_fake_and_real_collection(T &fake, const char *fake_name,
		U &real, const char *real_name) {
	std::cout << fake_name << ": ";
	print_vector(fake);
	std::cout << std::endl;
	std::cout << real_name << ": ";
	print_vector(real);
}

template <typename T, typename U>
void	print_fake_and_real(T fake, const char *fake_name,
		U real, const char *real_name) {
	std::cout << std::boolalpha;
	std::cout << fake_name << ": " << std::setw(5) << fake;
	std::cout << " | " << real_name << ": " << std::setw(5) << real;
	std::cout << std::endl;
}

template <typename T>
void	basic_method_tests(ft::vector<T> &vec, std::vector<T> &realvec, std::vector<T> &newvals,
		void (*f1)(T &n), void (*f2)(T &n)) {
	print_info(RED, "Basic tests");

	print_info(WHITE, "empty() tests 1");
	print_fake_and_real(vec.empty(), "ft::vector", realvec.empty(), "std::vector");

	print_info(WHITE, "push_back() tests");
	print_fake_and_real_collection(vec, "ft::vector", realvec, "std::vector");
	std::cout << std::endl;
	for (unsigned int i = 0; i < newvals.size(); i += 1) {
		vec.push_back(newvals[i]);
		realvec.push_back(newvals[i]);
	}
	print_fake_and_real_collection(vec, "ft::vector", realvec, "std::vector");
	std::cout << std::endl;

	print_info(WHITE, "size() tests 1");
	print_fake_and_real(vec.size(), "ft::vector", realvec.size(), "std::vector");

	print_info(WHITE, "max_size() tests");
	print_fake_and_real(vec.max_size(), "ft::vector", realvec.max_size(), "std::vector");

	print_info(WHITE, "Element access [] test");
	print_fake_and_real(vec[2], "ft::vector", realvec[2], "std::vector");
	print_fake_and_real(vec[5], "ft::vector", realvec[5], "std::vector");
	// std::cout << "Undefined:" << std::endl;
	// print_fake_and_real(vec[-1], "ft::vector", realvec[-1], "std::vector");
	// print_fake_and_real(vec[6], "ft::vector", realvec[6], "std::vector");

	print_info(WHITE, "resize() tests");
	print_fake_and_real(vec.size(), "ft::vector", realvec.size(), "std::vector");
	vec.resize(vec.size() + 3);
	realvec.resize(realvec.size() + 3);
	print_fake_and_real(vec.size(), "ft::vector", realvec.size(), "std::vector");
	print_fake_and_real_collection(vec, "ft::vector", realvec, "std::vector");
	std::cout << std::endl;
	vec.resize(vec.size() + 3, *(newvals.begin() + 2));
	realvec.resize(realvec.size() + 3, *(newvals.begin() + 2));
	print_fake_and_real(vec.size(), "ft::vector", realvec.size(), "std::vector");
	print_fake_and_real_collection(vec, "ft::vector", realvec, "std::vector");
	std::cout << std::endl;

	print_info(WHITE, "capacity() tests");
	print_fake_and_real(vec.capacity(), "ft::vector", realvec.capacity(), "std::vector");
	vec.push_back(newvals.front());
	realvec.push_back(newvals.front());
	print_fake_and_real(vec.capacity(), "ft::vector", realvec.capacity(), "std::vector");

	print_info(WHITE, "empty() tests 2");
	print_fake_and_real(vec.empty(), "ft::vector", realvec.empty(), "std::vector");

	print_info(WHITE, "size() tests 2");
	print_fake_and_real(vec.size(), "ft::vector", realvec.size(), "std::vector");

	print_info(WHITE, "at() tests");
	try {
		std::cout << "ft::vector: " << vec.at(3) << std::endl;
		std::cout << "ft::vector: " << vec.at(20) << std::endl;
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	try {
		std::cout << "std::vector: " << realvec.at(3) << std::endl;
		std::cout << "std::vector: " << realvec.at(20) << std::endl;
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	try {
		std::cout << "ft::vector: " << vec.at(-1) << std::endl;
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	try {
		std::cout << "std::vector: " << realvec.at(-1) << std::endl;
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}

	print_info(WHITE, "front() and back() tests");
	print_fake_and_real(vec.front(), "ft::vector", realvec.front(), "std::vector");
	print_fake_and_real(vec.back(), "ft::vector", realvec.back(), "std::vector");

	print_info(WHITE, "pop_back() tests");
	print_fake_and_real_collection(vec, "ft::vector", realvec, "std::vector");
	std::cout << std::endl;
	ft::vector<T>	tmp1 = vec;
	std::vector<T>	tmp2 = realvec;
	for (unsigned int i = 0; i < 2; i++) {
		vec.pop_back();
		realvec.pop_back();
	}
	print_fake_and_real_collection(vec, "ft::vector", realvec, "std::vector");
	std::cout << std::endl;
	while (!vec.empty()) {
		vec.pop_back();
		realvec.pop_back();
	}
	print_fake_and_real_collection(vec, "ft::vector", realvec, "std::vector");
	std::cout << std::endl;

	ft::vector<T>	tmp3 = vec;
	std::vector<T>	tmp4 = realvec;
	tmp3.assign(120, newvals[3]);
	tmp4.assign(120, newvals[3]);

	print_info(WHITE, "assign() tests");
	vec.assign(tmp1.begin(), tmp1.end());
	realvec.assign(tmp2.begin(), tmp2.end());
	print_fake_and_real_collection(vec, "ft::vector", realvec, "std::vector");
	std::cout << std::endl;
	print_fake_and_real(vec.size(), "ft::vector", realvec.size(), "std::vector");
	print_fake_and_real(vec.capacity(), "ft::vector", realvec.capacity(), "std::vector");

	vec.assign(tmp3.begin(), tmp3.end());
	realvec.assign(tmp4.begin(), tmp4.end());
	print_fake_and_real_collection(vec, "ft::vector", realvec, "std::vector");
	std::cout << std::endl;
	print_fake_and_real(vec.size(), "ft::vector", realvec.size(), "std::vector");
	print_fake_and_real(vec.capacity(), "ft::vector", realvec.capacity(), "std::vector");

	vec = tmp1;
	realvec = tmp2;

	vec.assign(30, newvals[1]);
	realvec.assign(30, newvals[1]);
	print_fake_and_real_collection(vec, "ft::vector", realvec, "std::vector");
	std::cout << std::endl;
	print_fake_and_real(vec.size(), "ft::vector", realvec.size(), "std::vector");
	print_fake_and_real(vec.capacity(), "ft::vector", realvec.capacity(), "std::vector");

	vec = tmp1;
	realvec = tmp2;

	print_info(WHITE, "insert() tests part 1");
	std::cout << "ft::vector: " << *(vec.insert(vec.begin() + 2, newvals[0])) << std::endl;
	std::cout << "std::vector: " << *(realvec.insert(realvec.begin() + 2, newvals[0])) << std::endl;
	print_fake_and_real_collection(vec, "ft::vector", realvec, "std::vector");
	std::cout << std::endl;

	std::cout << "ft::vector: " << *(vec.insert(vec.begin() + 5, newvals[4])) << std::endl;
	std::cout << "std::vector: " << *(realvec.insert(realvec.begin() + 5, newvals[4])) << std::endl;
	print_fake_and_real_collection(vec, "ft::vector", realvec, "std::vector");
	std::cout << std::endl;

	print_info(WHITE, "insert() tests part 2");
	vec.insert(vec.begin() + 3, 8, newvals[4]);
	realvec.insert(realvec.begin() + 3, 8, newvals[4]);
	print_fake_and_real_collection(vec, "ft::vector", realvec, "std::vector");
	std::cout << std::endl;
	print_fake_and_real(vec.size(), "ft::vector", realvec.size(), "std::vector");
	print_fake_and_real(vec.capacity(), "ft::vector", realvec.capacity(), "std::vector");

	vec = tmp1;
	realvec = tmp2;
	vec.insert(vec.begin() + 3, 50, newvals[4]);
	realvec.insert(realvec.begin() + 3, 50, newvals[4]);
	print_fake_and_real_collection(vec, "ft::vector", realvec, "std::vector");
	std::cout << std::endl;
	print_fake_and_real(vec.size(), "ft::vector", realvec.size(), "std::vector");
	print_fake_and_real(vec.capacity(), "ft::vector", realvec.capacity(), "std::vector");

	vec = tmp1;
	realvec = tmp2;

	print_info(WHITE, "insert() tests part 3");
	vec.insert(vec.begin() + 3, tmp1.begin(), tmp1.end());
	realvec.insert(realvec.begin() + 3, tmp2.begin(), tmp2.end());
	print_fake_and_real_collection(vec, "ft::vector", realvec, "std::vector");
	std::cout << std::endl;
	print_fake_and_real(vec.size(), "ft::vector", realvec.size(), "std::vector");
	print_fake_and_real(vec.capacity(), "ft::vector", realvec.capacity(), "std::vector");

	vec = tmp1;
	realvec = tmp2;

	print_info(WHITE, "erase() tests part 1");
	print_fake_and_real_collection(vec, "ft::vector", realvec, "std::vector");
	std::cout << std::endl;
	std::cout << "ft::vector: " << *(vec.erase(vec.begin() + 3)) << std::endl;
	std::cout << "std::vector: " << *(realvec.erase(realvec.begin() + 3)) << std::endl;
	print_fake_and_real_collection(vec, "ft::vector", realvec, "std::vector");
	std::cout << std::endl;
	// Both should segmentation fault
	// std::cout << "ft::vector: " << *(vec.erase(vec.end())) << std::endl;
	// std::cout << "std::vector: " << *(realvec.erase(realvec.end())) << std::endl;
	std::cout << "ft::vector: " << *(vec.erase(vec.end() - 1)) << std::endl;
	std::cout << "std::vector: " << *(realvec.erase(realvec.end() - 1)) << std::endl;
	print_fake_and_real_collection(vec, "ft::vector", realvec, "std::vector");
	std::cout << std::endl;

	vec = tmp1;
	realvec = tmp2;

	print_info(WHITE, "erase() tests part 2");
	print_fake_and_real_collection(vec, "ft::vector", realvec, "std::vector");
	std::cout << std::endl;
	std::cout << "ft::vector: " << *(vec.erase(vec.begin() + 1, vec.begin() + 4)) << std::endl;
	std::cout << "std::vector: " << *(realvec.erase(realvec.begin() + 1, realvec.begin() + 4)) << std::endl;
	print_fake_and_real_collection(vec, "ft::vector", realvec, "std::vector");
	std::cout << std::endl;
	// Both should segmentation fault
	// std::cout << "ft::vector: " << *(vec.erase(vec.begin(), vec.end() + 4)) << std::endl;
	// std::cout << "std::vector: " << *(realvec.erase(realvec.begin(), realvec.end() + 4)) << std::endl;
	std::cout << "ft::vector: " << *(vec.erase(vec.begin() + 1, vec.end() - 2)) << std::endl;
	std::cout << "std::vector: " << *(realvec.erase(realvec.begin() + 1, realvec.end() - 2)) << std::endl;
	print_fake_and_real_collection(vec, "ft::vector", realvec, "std::vector");
	std::cout << std::endl;

	std::cout << "Difference here is undefined behaviour:" << std::endl;
	std::cout << "ft::vector: " << *(vec.erase(vec.begin(), vec.end())) << std::endl;
	std::cout << "std::vector: " << *(realvec.erase(realvec.begin(), realvec.end())) << std::endl;
	print_fake_and_real_collection(vec, "ft::vector", realvec, "std::vector");
	std::cout << std::endl;
	print_fake_and_real(vec.size(), "ft::vector", realvec.size(), "std::vector");
	print_fake_and_real(vec.capacity(), "ft::vector", realvec.capacity(), "std::vector");

	vec = tmp1;
	realvec = tmp2;

	print_info(WHITE, "swap() tests part 1");
	vec.assign(tmp3.begin() + 3, tmp3.end());
	realvec.assign(tmp4.begin() + 3, tmp4.end());
	print_fake_and_real_collection(vec, "ft::vector", realvec, "std::vector");
	std::cout << std::endl;
	print_fake_and_real(vec.size(), "ft::vector", realvec.size(), "std::vector");
	print_fake_and_real(vec.capacity(), "ft::vector", realvec.capacity(), "std::vector");

	vec.swap(tmp1);
	realvec.swap(tmp2);
	print_fake_and_real_collection(vec, "ft::vector", realvec, "std::vector");
	std::cout << std::endl;
	print_fake_and_real_collection(vec, "ft::vector", realvec, "std::vector");
	std::cout << std::endl;
	print_fake_and_real(vec.size(), "ft::vector", realvec.size(), "std::vector");
	print_fake_and_real(vec.capacity(), "ft::vector", realvec.capacity(), "std::vector");

	print_info(WHITE, "swap() tests part 2");
	swap(vec, tmp1);
	swap(realvec, tmp2);
	print_fake_and_real_collection(vec, "ft::vector", realvec, "std::vector");
	std::cout << std::endl;
	print_fake_and_real(vec.size(), "ft::vector", realvec.size(), "std::vector");
	print_fake_and_real(vec.capacity(), "ft::vector", realvec.capacity(), "std::vector");

	print_info(WHITE, "clear() tests");
	vec.swap(tmp1);
	realvec.swap(tmp2);
	print_fake_and_real(vec.size(), "ft::vector", realvec.size(), "std::vector");
	print_fake_and_real(vec.capacity(), "ft::vector", realvec.capacity(), "std::vector");
	vec.clear();
	realvec.clear();
	print_fake_and_real(vec.size(), "ft::vector", realvec.size(), "std::vector");
	print_fake_and_real(vec.capacity(), "ft::vector", realvec.capacity(), "std::vector");
	print_fake_and_real_collection(vec, "ft::vector", realvec, "std::vector");
	std::cout << std::endl;

	print_info(WHITE, "Relational operator tests");
	vec = tmp1;
	realvec = tmp2;
	ft::vector<T>	vec2 = tmp1;
	std::vector<T>	realvec2 = tmp2;
	print_fake_and_real((vec == tmp1), "ft::vector", (realvec == tmp2), "std::vector");
	print_fake_and_real((vec != tmp1), "ft::vector", (realvec != tmp2), "std::vector");
	print_fake_and_real((vec < tmp1), "ft::vector", (realvec < tmp2), "std::vector");
	print_fake_and_real((vec2 < tmp1), "ft::vector", (realvec2 < tmp2), "std::vector");
	print_fake_and_real((vec <= tmp1), "ft::vector", (realvec <= tmp2), "std::vector");
	print_fake_and_real((vec2 <= tmp1), "ft::vector", (realvec2 <= tmp2), "std::vector");
	print_fake_and_real((vec > tmp1), "ft::vector", (realvec > tmp2), "std::vector");
	print_fake_and_real((vec2 > tmp1), "ft::vector", (realvec2 > tmp2), "std::vector");
	print_fake_and_real((vec >= tmp1), "ft::vector", (realvec >= tmp2), "std::vector");
	print_fake_and_real((vec2 >= tmp1), "ft::vector", (realvec2 >= tmp2), "std::vector");
	f1(vec.at(0));
	f1(realvec.at(0));
	f2(vec2.at(0));
	f2(realvec2.at(0));
	print_fake_and_real((vec == tmp1), "ft::vector", (realvec == tmp2), "std::vector");
	print_fake_and_real((vec != tmp1), "ft::vector", (realvec != tmp2), "std::vector");
	print_fake_and_real((vec < tmp1), "ft::vector", (realvec < tmp2), "std::vector");
	print_fake_and_real((vec2 < tmp1), "ft::vector", (realvec2 < tmp2), "std::vector");
	print_fake_and_real((vec <= tmp1), "ft::vector", (realvec <= tmp2), "std::vector");
	print_fake_and_real((vec2 <= tmp1), "ft::vector", (realvec2 <= tmp2), "std::vector");
	print_fake_and_real((vec > tmp1), "ft::vector", (realvec > tmp2), "std::vector");
	print_fake_and_real((vec2 > tmp1), "ft::vector", (realvec2 > tmp2), "std::vector");
	print_fake_and_real((vec >= tmp1), "ft::vector", (realvec >= tmp2), "std::vector");
	print_fake_and_real((vec2 >= tmp1), "ft::vector", (realvec2 >= tmp2), "std::vector");
}

template <typename T>
void	increment_tests(ft::vector<T> &vec, std::vector<T> &realvec) {
	typename ft::vector<T>::const_iterator it = vec.begin();
	typename std::vector<T>::const_iterator real_it = realvec.begin();

	print_info(WHITE, "Increment/Decrement tests");
	print_info(BLUE, "Incrementing and dereferencing with [] operator");
	for (unsigned int i = 0; i < realvec.size(); ++i)
		print_fake_and_real(it[i], "ft::vector", real_it[i], "std::vector");


	print_info(BLUE, "Incrementing towards end");
	std::cout << "ft::vector: ";
	for	(typename ft::vector<T>::const_iterator i = vec.begin(); i != vec.end(); i++)
		std::cout << *i << ", ";
	std::cout << " | std::vector: ";
	for	(typename std::vector<T>::const_iterator i = realvec.begin(); i != realvec.end(); i++)
		std::cout << *i << ", ";
	std::cout << std::endl;

	print_info(BLUE, "Decrementing towards beginning");
	std::cout << "ft::vector: ";
	for	(typename ft::vector<T>::const_iterator i = vec.end() - 1; i >= vec.begin(); i--)
		std::cout << *i << ", ";
	std::cout << " | std::vector: ";
	for	(typename std::vector<T>::const_iterator i = realvec.end() - 1; i >= realvec.begin(); i--)
		std::cout << *i << ", ";
	std::cout << std::endl;
}

template <typename T>
void	operation_tests(ft::vector<T> &vec, std::vector<T> &realvec) {
	typename ft::vector<T>::const_iterator it = vec.begin();
	typename std::vector<T>::const_iterator real_it = realvec.begin();

	print_info(WHITE, "Addition, subtraction, and copying");
	print_info(BLUE, "Compound assignment (+= and -=)");
	it = vec.begin();
	real_it = realvec.begin();
	it += 3;
	real_it += 3;
	print_fake_and_real(*it, "ft::vector", *real_it, "std::vector");
	it -= 2;
	real_it -= 2;
	print_fake_and_real(*it, "ft::vector", *real_it, "std::vector");

	print_info(BLUE, "Addition/subtraction with ints, subtraction with pointer");
	it += 2;
	real_it += 2;
	print_fake_and_real(*(it + 2), "ft::vector", *(real_it + 2), "std::vector");
	print_fake_and_real(*(it - 2), "ft::vector", *(real_it - 2), "std::vector");
	print_fake_and_real(*(2 + it), "ft::vector", *(2 + real_it), "std::vector");
	print_fake_and_real(*(1 + it + 1), "ft::vector", *(1 + real_it + 1), "std::vector");

	typename ft::vector<T>::const_iterator it2 = vec.begin() + 4;
	typename std::vector<T>::const_iterator real_it2 = realvec.begin() + 4;
	print_fake_and_real((it2 - it), "ft::vector", (real_it2 - real_it), "std::vector");
	print_info(BLUE, "Assignment with =");
	it2 = it;
	real_it2 = real_it;
	print_fake_and_real(*it2, "ft::vector", *real_it2, "std::vector");
}

template <typename T>
void	copy_comparison_tests(ft::vector<T> &vec, std::vector<T> &realvec) {
	typename ft::vector<T>::const_iterator it = vec.begin();
	typename std::vector<T>::const_iterator real_it = realvec.begin();

	print_info(WHITE, "Copy-construction & Comparisons");
	it = vec.begin();
	typename ft::vector<T>::const_iterator it3(it);
	real_it = realvec.begin();
	typename std::vector<T>::const_iterator real_it3(real_it);

	print_fake_and_real((it == it3), "ft::vector", (real_it == real_it3), "std::vector");
	it += 1;
	real_it += 1;
	print_fake_and_real((it == it3), "ft::vector", (real_it == real_it3), "std::vector");
	print_fake_and_real((it >= it3), "ft::vector", (real_it >= real_it3), "std::vector");
	print_fake_and_real((it <= it3), "ft::vector", (real_it <= real_it3), "std::vector");
	print_fake_and_real((it != it3), "ft::vector", (real_it != real_it3), "std::vector");

	typename ft::vector<T>::iterator nc_it;
	typename std::vector<T>::iterator nc_real_it;

	print_info(WHITE, "const to non-const comparisons");
	it = vec.begin();
	nc_it = vec.begin();
	real_it = realvec.begin();
	nc_real_it = realvec.begin();
	print_fake_and_real((it == nc_it), "ft::vector", (real_it == nc_real_it), "std::vector");
	print_fake_and_real((nc_it == it), "ft::vector", (nc_real_it == real_it), "std::vector");
	it += 1;
	real_it += 1;
	print_fake_and_real((it >= nc_it), "ft::vector", (real_it >= nc_real_it), "std::vector");
	print_fake_and_real((nc_it >= it), "ft::vector", (nc_real_it >= real_it), "std::vector");
	print_fake_and_real((it <= nc_it), "ft::vector", (real_it <= nc_real_it), "std::vector");
	print_fake_and_real((nc_it <= it), "ft::vector", (nc_real_it <= real_it), "std::vector");
	print_fake_and_real((it < nc_it), "ft::vector", (real_it < nc_real_it), "std::vector");
	print_fake_and_real((nc_it < it), "ft::vector", (nc_real_it < real_it), "std::vector");
	print_fake_and_real((it > nc_it), "ft::vector", (real_it > nc_real_it), "std::vector");
	print_fake_and_real((nc_it > it), "ft::vector", (nc_real_it > real_it), "std::vector");
}

template <typename T>
void	modification_tests(ft::vector<T> &vec, std::vector<T> &realvec,
		void (*f1)(int &n), void (*f2)(int &n), void (*f3)(int &n)) {
	print_info(WHITE, "Edits with non-const iterators");
	typename ft::vector<T>::iterator nc_it;
	typename std::vector<T>::iterator nc_real_it;

	print_fake_and_real_collection(vec, "ft::vector", realvec, "std::vector");
	std::cout << std::endl;

	if (!f1)
		return ;

	print_info(BLUE, "Addition to all values");
	for (nc_it = vec.begin(); nc_it != vec.end(); nc_it++)
		f1(*nc_it);
	for (nc_real_it = realvec.begin(); nc_real_it != realvec.end(); nc_real_it++)
		f1(*nc_real_it);
	print_fake_and_real_collection(vec, "ft::vector", realvec, "std::vector");
	std::cout << std::endl;

	if (!f2)
		return ;

	print_info(BLUE, "Subtraction to all values");
	for (nc_it = vec.begin(); nc_it != vec.end(); nc_it++)
		f2(*nc_it);
	for (nc_real_it = realvec.begin(); nc_real_it != realvec.end(); nc_real_it++)
		f2(*nc_real_it);
	print_fake_and_real_collection(vec, "ft::vector", realvec, "std::vector");
	std::cout << std::endl;

	if (!f3)
		return ;

	print_info(BLUE, "Multiplication to all values");
	for (nc_it = vec.begin(); nc_it != vec.end(); nc_it++)
		f3(*nc_it);
	for (nc_real_it = realvec.begin(); nc_real_it != realvec.end(); nc_real_it++)
		f3(*nc_real_it);
	print_fake_and_real_collection(vec, "ft::vector", realvec, "std::vector");
	std::cout << std::endl;
}

template <typename T>
void	reverse_increment_tests(ft::vector<T> &vec, std::vector<T> &realvec) {
	typename ft::vector<T>::const_reverse_iterator	rit = vec.rbegin();
	typename std::vector<T>::const_reverse_iterator	real_rit = realvec.rbegin();
	typename ft::vector<T>::const_reverse_iterator	rit2 = vec.rbegin();
	typename std::vector<T>::const_reverse_iterator	real_rit2 = realvec.rbegin();

	print_info(BLUE, "Reverse Incrementing towards reverse end (beginning)");
	std::cout << "ft::vector: ";
	for	(rit = vec.rbegin(); rit != vec.rend(); rit++)
		std::cout << *rit << ", ";
	std::cout << " | std::vector: ";
	for	(real_rit = realvec.rbegin(); real_rit != realvec.rend(); real_rit++)
		std::cout << *real_rit << ", ";
	std::cout << std::endl;

	print_info(BLUE, "Reverse Decrementing towards reverse beginning (end)");
	std::cout << "ft::vector: ";
	for	(rit = vec.rend() - 1; rit >= vec.rbegin(); rit--)
		std::cout << *rit << ", ";
	std::cout << " | std::vector: ";
	for	(real_rit = realvec.rend() - 1; real_rit >= realvec.rbegin(); real_rit--)
		std::cout << *real_rit << ", ";
	std::cout << std::endl;

	print_info(BLUE, "Addition, subtraction of reverse iterators");
	rit = vec.rbegin();
	real_rit = realvec.rbegin();
	rit += 3;
	real_rit += 3;
	print_fake_and_real(*rit, "ft::vector", *real_rit, "std::vector");
	rit -= 2;
	real_rit -= 2;
	print_fake_and_real(*rit, "ft::vector", *real_rit, "std::vector");

	print_info(BLUE, "Addition/subtraction with ints, subtraction with pointer");
	rit += 2;
	real_rit += 2;
	print_fake_and_real(*(rit + 2), "ft::vector", *(real_rit + 2), "std::vector");
	print_fake_and_real(*(rit - 2), "ft::vector", *(real_rit - 2), "std::vector");
	print_fake_and_real(*(2 + rit), "ft::vector", *(2 + real_rit), "std::vector");
	print_fake_and_real(*(1 + rit + 1), "ft::vector", *(1 + real_rit + 1), "std::vector");
	rit2 = vec.rbegin() + 4;
	real_rit2 = realvec.rbegin() + 4;
	print_fake_and_real((rit2 - rit), "ft::vector", (real_rit2 - real_rit), "std::vector");
	rit2 = vec.rbegin() + 2;
	real_rit2 = realvec.rbegin() + 2;
	print_fake_and_real((rit2 - rit), "ft::vector", (real_rit2 - real_rit), "std::vector");

}

template <typename T>
void	reverse_copy_comparison_tests(ft::vector<T> &vec, std::vector<T> &realvec) {
	typename ft::vector<T>::const_iterator it = vec.begin();
	typename std::vector<T>::const_iterator real_it = realvec.begin();
	typename ft::vector<T>::const_reverse_iterator	rit = vec.rbegin();
	typename std::vector<T>::const_reverse_iterator	real_rit = realvec.rbegin();

	print_info(WHITE, "Reverse iterator constructions and conversions");

	// Both should not compile!
	// it = ft::vector<int>::const_iterator(rit);
	// real_it = std::vector<T>::const_iterator(real_rit);

	typename ft::vector<T>::reverse_iterator	nc_rit(vec.rbegin());
	typename std::vector<T>::reverse_iterator	nc_real_rit(realvec.rbegin());
	typename ft::vector<T>::const_reverse_iterator	rit2(nc_rit);
	typename std::vector<T>::const_reverse_iterator	real_rit2(nc_real_rit);
	typename ft::vector<T>::const_reverse_iterator	rit3 = nc_rit;
	typename std::vector<T>::const_reverse_iterator	real_rit3 = nc_real_rit;
	rit3 += 2;
	real_rit3 += 2;

	print_fake_and_real(*it, "ft::vector", *real_it, "std::vector");
	print_fake_and_real(*rit2, "ft::vector", *real_rit2, "std::vector");
	print_fake_and_real(*rit3, "ft::vector", *real_rit3, "std::vector");

	print_info(BLUE, "Reverse iterator const and non-const comparisons");
	rit = vec.rbegin();
	nc_rit = vec.rbegin();
	real_rit = realvec.rbegin();
	nc_real_rit = realvec.rbegin();
	print_fake_and_real((rit == nc_rit), "ft::vector", (real_rit == nc_real_rit), "std::vector");
	print_fake_and_real((nc_rit == rit), "ft::vector", (nc_real_rit == real_rit), "std::vector");
	rit += 1;
	real_rit += 1;
	print_fake_and_real((rit >= nc_rit), "ft::vector", (real_rit >= nc_real_rit), "std::vector");
	print_fake_and_real((nc_rit >= rit), "ft::vector", (nc_real_rit >= real_rit), "std::vector");
	print_fake_and_real((rit <= nc_rit), "ft::vector", (real_rit <= nc_real_rit), "std::vector");
	print_fake_and_real((nc_rit <= rit), "ft::vector", (nc_real_rit <= real_rit), "std::vector");
	print_fake_and_real((rit < nc_rit), "ft::vector", (real_rit < nc_real_rit), "std::vector");
	print_fake_and_real((nc_rit < rit), "ft::vector", (nc_real_rit < real_rit), "std::vector");
	print_fake_and_real((rit > nc_rit), "ft::vector", (real_rit > nc_real_rit), "std::vector");
	print_fake_and_real((nc_rit > rit), "ft::vector", (nc_real_rit > real_rit), "std::vector");

	print_info(BLUE, "Assignment with =");
	rit2 = rit;
	real_rit2 = real_rit;
	print_fake_and_real(*rit2, "ft::vector", *real_rit2, "std::vector");
}

template <typename T>
void	reverse_modification_tests(ft::vector<T> &vec, std::vector<T> &realvec,
		void (*f1)(int &n), void (*f2)(int &n), void (*f3)(int &n)) {
	typename ft::vector<T>::reverse_iterator	nc_rit(vec.rbegin());
	typename std::vector<T>::reverse_iterator	nc_real_rit(realvec.rbegin());

	print_info(WHITE, "Edits with non-const reverse iterators");

	print_fake_and_real_collection(vec, "ft::vector", realvec, "std::vector");
	std::cout << std::endl;

	if (!f1)
		return ;

	print_info(BLUE, "Addition to all values");
	for (nc_rit = vec.rbegin(); nc_rit != vec.rend(); nc_rit++)
		*(nc_rit) += 2;
	for (nc_real_rit = realvec.rbegin(); nc_real_rit != realvec.rend(); nc_real_rit++)
		*(nc_real_rit) += 2;
	print_fake_and_real_collection(vec, "ft::vector", realvec, "std::vector");
	std::cout << std::endl;

	if (!f2)
		return ;

	print_info(BLUE, "Subtraction to all values");
	for (nc_rit = vec.rbegin(); nc_rit != vec.rend(); nc_rit++)
		(*nc_rit) -= 4;
	for (nc_real_rit = realvec.rbegin(); nc_real_rit != realvec.rend(); nc_real_rit++)
		*(nc_real_rit) -= 4;
	print_fake_and_real_collection(vec, "ft::vector", realvec, "std::vector");
	std::cout << std::endl;

	if (!f3)
		return ;

	print_info(BLUE, "Multiplication to all values");
	for (nc_rit = vec.rbegin(); nc_rit != vec.rend(); nc_rit++)
		(*nc_rit) *= 4;
	for (nc_real_rit = realvec.rbegin(); nc_real_rit != realvec.rend(); nc_real_rit++)
		*(nc_real_rit) *= 4;
	print_fake_and_real_collection(vec, "ft::vector", realvec, "std::vector");
	std::cout << std::endl;
}

template <typename T>
void	reverse_base_tests(ft::vector<T> &vec, std::vector<T> &realvec) {
	typename ft::vector<T>::reverse_iterator	nc_rit(vec.rbegin());
	typename std::vector<T>::reverse_iterator	nc_real_rit(realvec.rbegin());
	typename ft::vector<T>::const_reverse_iterator	rit2(nc_rit);
	typename std::vector<T>::const_reverse_iterator	real_rit2(nc_real_rit);
	typename ft::vector<T>::const_reverse_iterator	rit3 = nc_rit;
	typename std::vector<T>::const_reverse_iterator	real_rit3 = nc_real_rit;

	nc_rit = vec.rbegin() + 1;
	nc_real_rit = realvec.rbegin() + 1;
	print_info(WHITE, "base() test");
	print_fake_and_real(*nc_rit, "ft::vector", *nc_real_rit, "std::vector");
	print_fake_and_real(*(nc_rit.base()), "ft::vector", *(nc_real_rit.base()), "std::vector");
	print_fake_and_real(*(rit2.base() - 1), "ft::vector", *(real_rit2.base() - 1), "std::vector");
	print_fake_and_real(*(rit3.base() - 4), "ft::vector", *(real_rit3.base() - 4), "std::vector");
}

template <typename T>
void	reverse_iteration_tests(ft::vector<T> &vec, std::vector<T> &realvec,
		void (*f1)(int &n), void (*f2)(int &n), void (*f3)(int &n)) {
	print_info(RED, "Reverse Iterator tests");

	reverse_increment_tests(vec, realvec);
	reverse_copy_comparison_tests(vec, realvec);
	reverse_modification_tests(vec, realvec, f1, f2, f3);
	reverse_base_tests(vec, realvec);
}

template <typename T>
void	iterator_tests(ft::vector<T> &vec, std::vector<T> &realvec,
		void (*f1)(int &n), void (*f2)(int &n), void (*f3)(int &n)) {
	ft::vector<T>	original_fake = vec;	// Also testing copy
	std::vector<T>	original_real = realvec;

	print_info(RED, "Iterator tests");

	print_fake_and_real_collection(vec, "ft::vector", realvec, "std::vector");
	std::cout << std::endl;

	increment_tests(vec, realvec);
	operation_tests(vec, realvec);
	copy_comparison_tests(vec, realvec);
	modification_tests(vec, realvec, f1, f2, f3);
	vec = original_fake;
	realvec = original_real;

	reverse_iteration_tests(vec, realvec, f1, f2, f3);

	return ;
}

template <typename T>
void	algorithm_tests(ft::vector<T> &vec, std::vector<T> &realvec) {
	print_info(RED, "Algorithm function tests");

}

void	int_vector_tests(void (*f1)(int &n), void (*f2)(int &n), void (*f3)(int &n))
{
	print_divider(CYAN, "ft::vector<int> tests");

	ft::vector<int>			vec;
	std::vector<int>		realvec;
	std::vector<int>		newvals;
	// ft::vector<int>			original;
	// std::vector<int>		real_original;

	for (unsigned int i = 5; i <= 30; i += 5)
		newvals.push_back(i);

	(void)f1;(void)f2;(void)f3;
	basic_method_tests(vec, realvec, newvals, f1, f2);

	// iterator_tests(vec, realvec, f1, f2, f3);

	print_line(CYAN);
}

void	string_vector_tests(void (*f1)(std::string &s), void (*f2)(std::string &s)) {
	print_divider(MAGENTA, "ft::vector<std::string> tests");

	ft::vector<std::string>		vec;
	std::vector<std::string>	realvec;
	std::vector<std::string>	newvals;

	newvals.push_back("Lorem");
	newvals.push_back("ipsum");
	newvals.push_back("dolor");
	newvals.push_back("sit");
	newvals.push_back("amet,");
	newvals.push_back("consectetur");

	basic_method_tests(vec, realvec, newvals, f1, f2);

	print_line(MAGENTA);
}

class Example {
	public:
		Example(void) : _val(3) {}
		Example(int x) : _val(x) {}
		int		getVal(void) const {
			return (_val);
		}
	private:
		int		_val;
};

void	any_object_tests(void) {
	print_divider(RED, "ft::vector<Example> tests");

	Example				three;
	Example				five(5);
	Example				seven(7);
	ft::vector<Example>		vec;

	vec.push_back(three);
	vec.push_back(five);
	vec.push_back(seven);

	for (ft::vector<Example>::iterator i = vec.begin(); i != vec.end(); i++)
		std::cout << i->getVal() << std::endl;

	print_line(RED);
}

void	int_add_func(int &n) { n += 2; }
void	int_sub_func(int &n) { n -= 2; }
void	int_mul_func(int &n) { n *= 4; }
void	string_add_func(std::string &s) { if (s.size() == 0) { return ; } else { s[0] += 1; } }
void	string_sub_func(std::string &s) { if (s.size() == 0) { return ; } else { s[0] -= 1; } }

int		main(void)
{
	int_vector_tests(int_add_func, int_sub_func, int_mul_func);
	string_vector_tests(string_add_func, string_sub_func);
	// any_object_tests();

	return (0);
}
