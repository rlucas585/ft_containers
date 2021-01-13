/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <ryanl585codam@gmail.com>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/06 12:49:55 by rlucas        #+#    #+#                 */
/*   Updated: 2021/01/13 15:44:05 by rlucas        ########   odam.nl         */
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
	std::cout << " | " << real_name << ": ";
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
void	basic_method_tests(ft::vector<T> &vec, std::vector<T> &realvec) {
	print_info(RED, "Basic tests");

	print_fake_and_real_collection(vec, "ft::vector", realvec, "std::vector");
	std::cout << std::endl;
	print_info(WHITE, "push_back() tests");
	for (unsigned int i = 5; i <= 30; i += 5) {
		vec.push_back(i);
		realvec.push_back(i);
	}
	print_fake_and_real_collection(vec, "ft::vector", realvec, "std::vector");
	std::cout << std::endl;
	print_info(WHITE, "size() tests");
	print_fake_and_real(vec.size(), "ft::vector", realvec.size(), "std::vector");
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
	std::vector<int>	realvec;

	basic_method_tests(vec, realvec);
	iterator_tests(vec, realvec, f1, f2, f3);

	print_line(CYAN);
}

void	string_vector_tests(void) {
	print_divider(MAGENTA, "ft::vector<std::string> tests");

	ft::vector<std::string>		vec;

	vec.push_back("hello");
	try_index(vec, 0);
	try_index(vec, 1);
	vec.push_back("there");
	try_index(vec, 1);
	vec.push_back("!");
	vec.push_back("General");
	vec.push_back("Kenobi");
	vec.push_back("!");
	try_index(vec, 1);
	try_index(vec, 2);
	try_index(vec, 3);
	try_index(vec, 4);
	try_index(vec, 5);

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

int		main(void)
{
	int_vector_tests(int_add_func, int_sub_func, int_mul_func);
	// string_vector_tests();
	// any_object_tests();

	return (0);
}
