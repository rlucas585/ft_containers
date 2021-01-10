/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <ryanl585codam@gmail.com>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/06 12:49:55 by rlucas        #+#    #+#                 */
/*   Updated: 2021/01/10 15:59:52 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <algorithm>

#include "colors.hpp"
#include "utils.hpp"
#include "Vector.hpp"

template <typename T>
void	try_index(Vector<T> &vec, size_t i) {
	T		val;
	try {
		val = vec[i];
		std::cout << "Index " << i << ": " << val << std::endl;
	} catch (std::exception &e) {
		std::cerr << "Error " << ": " << e.what() << std::endl;
	}
}

template <typename T>
void	print_vector(Vector<T> &vec) {
	std::cout << "[";
	for (unsigned int i = 0; i < vec.size(); i++) {
		if (i == vec.size() - 1)
			std::cout << vec[i] << "]" << std::endl;
		else
			std::cout << vec[i] << ", ";
	}
}

template <typename T>
void	iterator_tests(Vector<T> &vec) {
	print_info(WHITE, "Iterator tests");

	print_info(WHITE, "Basic tests");
	std::cout << "Vector: ";
	print_vector(vec);
	print_info(WHITE, "Incrementing towards end");
	for	(typename Vector<T>::iterator i = vec.begin(); i != vec.end(); i++)
		std::cout << *i << std::endl;
	print_info(WHITE, "Incrementing with += 1");
	for	(typename Vector<T>::iterator i = vec.begin(); i != vec.end(); i++)
		*i += 1;
	print_vector(vec);
	print_info(WHITE, "Decrementing towards end");
	for	(typename Vector<int>::iterator i = vec.end() - 1; i >= vec.begin(); --i)
		std::cout << *i << std::endl;
	print_info(WHITE, "Offsetting with addition");
	typename Vector<T>::iterator i = vec.begin();
	std::cout << *(i + 2) << std::endl;
	print_info(WHITE, "Offsetting with []");
	std::cout << i[2] << std::endl;
	print_info(WHITE, "Testing with algorithms");
	print_vector(vec);
	print_info(WHITE, "Reverse vector");
	reverse(vec.begin(), vec.end());
	print_vector(vec);
	print_info(WHITE, "Rotate vector");
	rotate(vec.begin(), vec.begin() + 2, vec.end());
	print_vector(vec);
}

template <typename T>
void	const_iterator_tests(Vector<T> &vec) {
	print_info(WHITE, "Const Iterator tests");

	print_info(WHITE, "Basic tests");
	std::cout << "Vector: ";
	print_vector(vec);
	print_info(WHITE, "Incrementing towards end");
	for	(typename Vector<T>::const_iterator i = vec.begin(); i != vec.end(); i++)
		std::cout << *i << std::endl;
	print_info(WHITE, "Incrementing with += 1 (DOES NOT COMPILE)");
	// for	(typename Vector<T>::const_iterator i = vec.begin(); i != vec.end(); i++)
	// 	*i += 1;
	print_vector(vec);
	print_info(WHITE, "Decrementing towards end");
	for	(typename Vector<T>::const_iterator i = vec.end() - 1; i >= vec.begin(); --i)
		std::cout << *i << std::endl;
	print_info(WHITE, "Offsetting with addition");
	typename Vector<T>::const_iterator i = vec.begin();
	std::cout << *(i + 2) << std::endl;
	print_info(WHITE, "Offsetting with []");
	std::cout << i[2] << std::endl;
	print_info(WHITE, "Testing with algorithms");
	print_vector(vec);
	print_info(WHITE, "Reverse vector");
	reverse(vec.begin(), vec.end());
	print_vector(vec);
	print_info(WHITE, "Rotate vector");
	rotate(vec.begin(), vec.begin() + 2, vec.end());
	print_vector(vec);

	typename Vector<T>::iterator				it1 = vec.begin();
	typename Vector<T>::const_iterator			it2 = vec.begin();

	std::cout << std::boolalpha <<
		(it1 == it2)
		<< std::endl;
	std::cout << std::boolalpha <<
		(it2 == it1)
		<< std::endl;
	it2 += 1;
	std::cout << std::boolalpha <<
		(it1 == it2)
		<< std::endl;
	std::cout << std::boolalpha <<
		(it1 >= it2)
		<< std::endl;
	std::cout << std::boolalpha <<
		(it2 >= it1)
		<< std::endl;
	std::cout << std::boolalpha <<
		(it2 != it1)
		<< std::endl;
	return ;
}

void	int_vector_tests(void)
{
	print_divider(CYAN, "Vector<int> tests");

	Vector<int>		vec;

	vec.push(5);
	vec.push(10);
	vec.push(15);
	vec.push(20);
	vec.push(25);
	vec.push(30);

	for	(Vector<int>::iterator i = vec.begin(); i != vec.end(); i++)
		std::cout << *i << std::endl;

	// iterator_tests(vec);
	const_iterator_tests(vec);

	print_line(CYAN);
}

void	string_vector_tests(void) {
	print_divider(MAGENTA, "Vector<std::string> tests");

	Vector<std::string>		vec;

	vec.push("hello");
	try_index(vec, 0);
	try_index(vec, 1);
	vec.push("there");
	try_index(vec, 1);
	vec.push("!");
	vec.push("General");
	vec.push("Kenobi");
	vec.push("!");
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
	print_divider(RED, "Vector<Example> tests");

	Example				three;
	Example				five(5);
	Example				seven(7);
	Vector<Example>		vec;

	vec.push(three);
	vec.push(five);
	vec.push(seven);

	for (Vector<Example>::iterator i = vec.begin(); i != vec.end(); i++)
		std::cout << i->getVal() << std::endl;

	print_line(RED);
}

int		main(void)
{
	int_vector_tests();
	// string_vector_tests();
	// any_object_tests();

	return (0);
}
