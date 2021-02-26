/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map.cpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/21 15:01:14 by rlucas        #+#    #+#                 */
/*   Updated: 2021/02/26 16:34:43 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <gtest/gtest.h>

#include <stdexcept>
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <iomanip>

#include "../src/map.hpp"
#include "../src/pair.hpp"
#include "test_fixture_classes.hpp"
#include "Example.hpp"
#include "test.hpp"

TEST(development_test, initialisation_test) {
	ft::map<int, std::string>		aMap;

	(void)aMap;
	std::cout << aMap.size() << std::endl;
	ASSERT_EQ(aMap.size(), 0);
}

TEST(development_test, insert_test) {
	ft::map<int, std::string>		aMap;

	aMap.insert(ft::pair<int, std::string>(3, "hello"));
	ASSERT_EQ(aMap.size(), 1);
}

TEST(development_test, basic_iterator_test) {
	typedef typename ft::map<int, std::string>::iterator	mapIter;
	ft::map<int, std::string>				aMap;
	ft::pair<mapIter, bool>					ret;

	ret = aMap.insert(ft::pair<int, std::string>(5, "Leeds"));
	ASSERT_TRUE(ret.second);
	ASSERT_EQ((*ret.first).second, "Leeds");
	ret = aMap.insert(ft::pair<int, std::string>(3, "Arsenal"));
	ASSERT_TRUE(ret.second);
	ASSERT_EQ((*ret.first).second, "Arsenal");
	ret = aMap.insert(ft::pair<int, std::string>(-1, "Man Utd"));
	ASSERT_TRUE(ret.second);
	ASSERT_EQ((*ret.first).second, "Man Utd");
	ret = aMap.insert(ft::pair<int, std::string>(15, "Newcastle"));
	ASSERT_TRUE(ret.second);
	ASSERT_EQ((*ret.first).second, "Newcastle");
	ret = aMap.insert(ft::pair<int, std::string>(12, "Everton"));
	ASSERT_TRUE(ret.second);
	ASSERT_EQ((*ret.first).second, "Everton");
	ret = aMap.insert(ft::pair<int, std::string>(4, "West Brom"));
	ASSERT_TRUE(ret.second);
	ASSERT_EQ((*ret.first).second, "West Brom");
	ret = aMap.insert(ft::pair<int, std::string>(50, "Netherlands"));
	ASSERT_TRUE(ret.second);
	ASSERT_EQ((*ret.first).second, "Netherlands");
	ret = aMap.insert(ft::pair<int, std::string>(55, "Germany"));
	ASSERT_TRUE(ret.second);
	ASSERT_EQ((*ret.first).second, "Germany");
	ret = aMap.insert(ft::pair<int, std::string>(45, "France"));
	ASSERT_TRUE(ret.second);
	ASSERT_EQ((*ret.first).second, "France");

	// Existing key
	ret = aMap.insert(ft::pair<int, std::string>(4, "Another West Brom"));
	ASSERT_FALSE(ret.second);
	ASSERT_EQ((*ret.first).second, "West Brom");

	mapIter		it = aMap.begin();
	while (it != aMap.end()) {
		std::cout << "(" << (*it).first << ", " << (*it).second << ")" << std::endl;
		it++;
	}
}

TEST(development_test, pair_test) {
	ft::pair<int, int>		example;

	ASSERT_EQ(example.first, 0);
	ASSERT_EQ(example.second, 0);

	ft::pair<int, std::string>	example2 = ft::make_pair(5, "Devon");

	ASSERT_EQ(example2.first, 5);
	ASSERT_EQ(example2.second, "Devon");
}

template <typename Map>
std::string	map_to_str(Map const& map) {
	std::stringstream	ss;

	ss << "[";
	for (typename Map::const_iterator it = map.begin(); it != map.end(); it++) {
		ss << "(" << (*it).first << ", " << (*it).second << "), ";
	}
	ss << "]";
	return ss.str();
}

template <typename Map>
void	print_map_info(Map const& map, const char *name) {
	std::string		mapStr = map_to_str(map);
	if (mapStr.size() >= 60)
		mapStr.erase(mapStr.begin() + 60, mapStr.end());

	std::cout << std::setw(10) << std::right << std::setfill(' ')
		<< name;
	std::cout << "|";
	std::cout << std::setw(10) << std::right << std::setfill(' ')
		<< map.size();
	std::cout << "|";
	std::cout << std::setw(60) << std::right << std::setfill(' ')
		<< mapStr;
	std::cout << "|";
	std::cout << std::endl;
}

template <typename T, typename U>
void	print_table(ft::map<T,U> const& map, std::map<T,U> const& realmap) {
	for (size_t i = 0; i < 10 + 10 + 60 + 3; i++)
		std::cout << "-";
	std::cout << std::endl;
	std::cout << std::setw(10) << std::right << std::setfill(' ')
		<< "name";
	std::cout << "|";
	std::cout << std::setw(10) << std::right << std::setfill(' ')
		<< "size";
	std::cout << "|";
	std::cout << std::setw(60) << std::right << std::setfill(' ')
		<< "content";
	std::cout << "|";
	std::cout << std::endl;
	for (size_t i = 0; i < 10 + 10 + 60 + 3; i++)
		std::cout << "-";
	std::cout << std::endl;
	print_map_info(map, "map");
	print_map_info(realmap, "realmap");
	for (size_t i = 0; i < 10 + 10 + 60 + 3; i++)
		std::cout << "-";
	std::cout << std::endl;
}

template <typename T, typename U>
void	initialise_default_map(ft::map<T, U>& map, std::map<T, U>& realmap) {
	ft::vector<T>		t_vec1;
	std::vector<T>		t_vec2;
	ft::vector<U>		u_vec1;
	std::vector<U>		u_vec2;
	initialise_default_vector(t_vec1, t_vec2);
	initialise_default_vector(u_vec1, u_vec2);
	std::reverse(u_vec1.begin(), u_vec1.end());
	for (size_t i = 0; i != t_vec1.size() && i != u_vec1.size(); i++) {
		ft::pair<T,U>		pair(t_vec1[i], u_vec1[i]);
		std::pair<T,U>		realpair(t_vec1[i], u_vec1[i]);
		map.insert(pair);
		realmap.insert(realpair);
	}
}

template <typename T, typename U>
void	testMaps(ft::map<T,U>const& map, std::map<T,U>const& realmap) {
	typedef typename ft::map<T, U>::const_iterator	mapIter;
	typedef typename std::map<T, U>::const_iterator	realMapIter;
	if (PRINTED_OUTPUT)
		print_table(map, realmap);
	ASSERT_EQ(map.size(), realmap.size());
	mapIter it = map.begin();
	realMapIter realit = realmap.begin();
	for (; it != map.end(); it++, realit++) {
		ASSERT_EQ((*it).first, (*realit).first);
		ASSERT_EQ((*it).second, (*realit).second);
	}
}

TYPED_TEST_CASE(map_tester, Implementations);

TYPED_TEST(map_tester, empty_test) {
	ft::map<int, TypeParam>		map1;
	std::map<int, TypeParam>	realmap1;
	ft::map<TypeParam, int>		map2;
	std::map<TypeParam, int>	realmap2;

	ASSERT_TRUE(map1.empty());
	ASSERT_TRUE(realmap1.empty());
	ASSERT_TRUE(map2.empty());
	ASSERT_TRUE(realmap2.empty());
	ASSERT_EQ(map1.empty(), realmap1.empty());
	ASSERT_EQ(map2.empty(), realmap2.empty());

	testMaps(map1, realmap1);
	testMaps(map2, realmap2);

	initialise_default_map(map1, realmap1);
	initialise_default_map(map2, realmap2);

	testMaps(map1, realmap1);
	testMaps(map2, realmap2);

	ASSERT_FALSE(map1.empty());
	ASSERT_FALSE(realmap1.empty());
	ASSERT_FALSE(map2.empty());
	ASSERT_FALSE(realmap2.empty());
	ASSERT_EQ(map1.empty(), realmap1.empty());
	ASSERT_EQ(map2.empty(), realmap2.empty());
}

TYPED_TEST(map_tester, insert_single_element_test) {
	ft::map<int, TypeParam>		map1;
	std::map<int, TypeParam>	realmap1;
	ft::map<TypeParam, int>		map2;
	std::map<TypeParam, int>	realmap2;
	ft::vector<int>				i_vec;
	std::vector<int>			i_vec_real;
	ft::vector<TypeParam>		type_vec;
	std::vector<TypeParam>		type_vec_real;
	initialise_default_vector(i_vec, i_vec_real);
	initialise_default_vector(type_vec, type_vec_real);

	for (size_t i = 0; i != i_vec.size() && i != type_vec.size(); i++) {
		ft::pair<int,TypeParam>			pair1(i_vec[i], type_vec[i]);
		std::pair<int,TypeParam>		realpair1(i_vec[i], type_vec[i]);
		ft::pair<TypeParam,int>			pair2(type_vec[i], i_vec[i]);
		std::pair<TypeParam,int>		realpair2(type_vec[i], i_vec[i]);
		map1.insert(pair1);
		realmap1.insert(realpair1);
		map2.insert(pair2);
		realmap2.insert(realpair2);
	}

	testMaps(map1, realmap1);
	testMaps(map2, realmap2);
}

TYPED_TEST(map_tester, insert_hint_test) {
	typedef typename ft::map<int, TypeParam>::iterator	mapIter1;
	typedef typename std::map<int, TypeParam>::iterator	realMapIter1;
	typedef typename ft::map<TypeParam, int>::iterator	mapIter2;
	typedef typename std::map<TypeParam, int>::iterator	realMapIter2;
	ft::map<int, TypeParam>		map1;
	std::map<int, TypeParam>	realmap1;
	ft::map<TypeParam, int>		map2;
	std::map<TypeParam, int>	realmap2;
	ft::vector<int>				i_vec;
	std::vector<int>			i_vec_real;
	ft::vector<TypeParam>		type_vec;
	std::vector<TypeParam>		type_vec_real;
	initialise_default_vector(i_vec, i_vec_real);
	initialise_default_vector(type_vec, type_vec_real);
	mapIter1	it1 = map1.end();
	realMapIter1	realit1 = realmap1.end();
	mapIter2	it2 = map2.end();
	realMapIter2	realit2 = realmap2.end();

	for (size_t i = 0; i != i_vec.size() && i != type_vec.size(); i++) {
		ft::pair<int,TypeParam>			pair1(i_vec[i], type_vec[i]);
		std::pair<int,TypeParam>		realpair1(i_vec[i], type_vec[i]);
		ft::pair<TypeParam,int>			pair2(type_vec[i], i_vec[i]);
		std::pair<TypeParam,int>		realpair2(type_vec[i], i_vec[i]);
		std::cout << "hello" << std::endl;
		if (it1 == map1.end()) {
			std::cout << "default insert called" << std::endl;
			it1 = map1.insert(pair1).first;
		}
		else {
			std::cout << "hint insert called" << std::endl;
			it1 = map1.insert(it1, pair1);
		}
		std::cout << "hello" << std::endl;
		if (realit1 == realmap1.end()) {
			std::cout << "default insert called" << std::endl;
			realit1 = realmap1.insert(realpair1).first;
		}
		else {
			std::cout << "hint insert called" << std::endl;
			realit1 = realmap1.insert(realit1, realpair1);
		}
		std::cout << "hi" << std::endl;
		if (it2 == map2.end())
			it2 = map2.insert(pair2).first;
		else
			it2 = map2.insert(it2, pair2);
		if (realit2 != realmap2.end())
			realit2 = realmap2.insert(realpair2).first;
		else
			realit2 = realmap2.insert(realit2, realpair2);
	}

	testMaps(map1, realmap1);
	testMaps(map2, realmap2);
}
