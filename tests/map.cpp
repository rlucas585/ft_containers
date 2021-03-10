/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map.cpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/21 15:01:14 by rlucas        #+#    #+#                 */
/*   Updated: 2021/03/10 17:36:44 by rlucas        ########   odam.nl         */
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

template <typename T, typename U>
ft::vector<ft::pair<T, U> >		zip(ft::vector<T>const& vec, ft::vector<U>const& vec2) {
	typename ft::vector<T>::const_iterator it1 = vec.begin();
	typename ft::vector<U>::const_iterator it2 = vec2.begin(); 
	ft::vector<ft::pair<T, U> >		pairs;

	for (; it1 != vec.end() && it2 != vec2.end(); it1++, it2++)
		pairs.push_back(ft::pair<T, U>(*it1, *it2));
	return pairs;
}

template <typename T, typename U>
std::vector<std::pair<T, U> >		zip(std::vector<T>const& vec, std::vector<U>const& vec2) {
	typename std::vector<T>::const_iterator it1 = vec.begin();
	typename std::vector<U>::const_iterator it2 = vec2.begin(); 
	std::vector<std::pair<T, U> >		pairs;

	for (; it1 != vec.end() && it2 != vec2.end(); it1++, it2++)
		pairs.push_back(std::pair<T, U>(*it1, *it2));
	return pairs;
}

template <typename Iterator>
static Iterator		incrementIterator(Iterator it, size_t n) {
	while (n > 0) {
		it++;
		n -= 1;
	}
	return it;
}

template <typename Iterator>
static Iterator		decrementIterator(Iterator it, size_t n) {
	while (n > 0) {
		it--;
		n -= 1;
	}
	return it;
}

template <typename T, typename U, typename Comp>
void	addition_to_map(ft::map<T,U,Comp>& map, std::map<T,U,Comp>& realmap,
		U val) {
	if (map.size() == 0 || realmap.size() == 0)
		return ;

	typename ft::map<T,U,Comp>::iterator	it1 = map.begin();
	typename std::map<T,U,Comp>::iterator	realit1 = realmap.begin();
	(*it1).second += val;
	(*realit1).second += val;
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

template <typename T, typename U, typename Comp>
void	print_table(ft::map<T,U,Comp> const& map, std::map<T,U,Comp> const& realmap) {
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

template <typename T, typename U, typename Comp>
void	initialise_default_map(ft::map<T, U, Comp>& map, std::map<T, U, Comp>& realmap) {
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

template <typename T, typename U, typename Comp>
void	testMaps(ft::map<T,U,Comp>const& map, std::map<T,U,Comp>const& realmap) {
	typedef typename ft::map<T, U,Comp>::const_iterator	mapIter;
	typedef typename std::map<T, U,Comp>::const_iterator	realMapIter;
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

TYPED_TEST(map_tester, range_constructor_test) {
	typedef typename ft::pair<int, TypeParam>			pairType1;
	typedef typename std::pair<int, TypeParam>			realPairType1;
	typedef typename ft::pair<TypeParam, int>			pairType2;
	typedef typename std::pair<TypeParam, int>			realPairType2;
	ft::vector<int>				i_vec;
	std::vector<int>			i_vec_real;
	ft::vector<TypeParam>		type_vec;
	std::vector<TypeParam>		type_vec_real;
	initialise_default_vector(i_vec, i_vec_real);
	initialise_default_vector(type_vec, type_vec_real);
	ft::vector<pairType1>		pairsvec1 = zip(i_vec, type_vec);
	std::vector<realPairType1>	realpairsvec1 = zip(i_vec_real, type_vec_real);
	ft::vector<pairType2>		pairsvec2 = zip(type_vec, i_vec);
	std::vector<realPairType2>	realpairsvec2 = zip(type_vec_real, i_vec_real);

	ft::map<int, TypeParam>		map1(pairsvec1.begin(), pairsvec1.end());
	std::map<int, TypeParam>	realmap1(realpairsvec1.begin(), realpairsvec1.end());
	ft::map<TypeParam, int>		map2(pairsvec2.begin(), pairsvec2.end());
	std::map<TypeParam, int>	realmap2(realpairsvec2.begin(), realpairsvec2.end());

	testMaps(map1, realmap1);
	testMaps(map2, realmap2);

	// Attempts to insert duplicate values, all should be ignored
	map1.insert(pairsvec1.begin(), pairsvec1.end());
	realmap1.insert(realpairsvec1.begin(), realpairsvec1.end());
	map2.insert(pairsvec2.begin(), pairsvec2.end());
	realmap2.insert(realpairsvec2.begin(), realpairsvec2.end());

	testMaps(map1, realmap1);
	testMaps(map2, realmap2);
}

TYPED_TEST(map_tester, copy_constructor_test) {
	typedef typename ft::pair<int, TypeParam>			pairType1;
	typedef typename std::pair<int, TypeParam>			realPairType1;
	typedef typename ft::pair<TypeParam, int>			pairType2;
	typedef typename std::pair<TypeParam, int>			realPairType2;
	ft::vector<int>				i_vec;
	std::vector<int>			i_vec_real;
	ft::vector<TypeParam>		type_vec;
	std::vector<TypeParam>		type_vec_real;
	initialise_default_vector(i_vec, i_vec_real);
	initialise_default_vector(type_vec, type_vec_real);
	ft::vector<pairType1>		pairsvec1 = zip(i_vec, type_vec);
	std::vector<realPairType1>	realpairsvec1 = zip(i_vec_real, type_vec_real);
	ft::vector<pairType2>		pairsvec2 = zip(type_vec, i_vec);
	std::vector<realPairType2>	realpairsvec2 = zip(type_vec_real, i_vec_real);

	ft::map<int, TypeParam>		map1(pairsvec1.begin(), pairsvec1.end());
	std::map<int, TypeParam>	realmap1(realpairsvec1.begin(), realpairsvec1.end());
	ft::map<TypeParam, int>		map2(pairsvec2.begin(), pairsvec2.end());
	std::map<TypeParam, int>	realmap2(realpairsvec2.begin(), realpairsvec2.end());

	testMaps(map1, realmap1);
	testMaps(map2, realmap2);

	ft::map<int, TypeParam>		map3(map1);
	std::map<int, TypeParam>	realmap3(realmap1);
	ft::map<TypeParam, int>		map4 = map2;
	std::map<TypeParam, int>	realmap4 = realmap2;

	testMaps(map3, realmap3);
	testMaps(map4, realmap4);
	testMaps(map1, realmap3);
	testMaps(map2, realmap4);
	testMaps(map3, realmap1);
	testMaps(map4, realmap2);
}

TYPED_TEST(map_tester, insert_single_element_test) {
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
	ft::pair<mapIter1,bool>			returnpair1;
	std::pair<realMapIter1,bool>	returnrealpair1;
	ft::pair<mapIter2,bool>			returnpair2;
	std::pair<realMapIter2,bool>	returnrealpair2;

	for (size_t i = 0; i != i_vec.size() && i != type_vec.size(); i++) {
		ft::pair<int,TypeParam>			pair1(i_vec[i], type_vec[i]);
		std::pair<int,TypeParam>		realpair1(i_vec[i], type_vec[i]);
		ft::pair<TypeParam,int>			pair2(type_vec[i], i_vec[i]);
		std::pair<TypeParam,int>		realpair2(type_vec[i], i_vec[i]);
		returnpair1 = map1.insert(pair1);
		returnrealpair1 = realmap1.insert(realpair1);
		returnpair2 = map2.insert(pair2);
		returnrealpair2 = realmap2.insert(realpair2);
		ASSERT_EQ((*(returnpair1.first)).first, (*(returnrealpair1.first)).first);
		ASSERT_EQ((*(returnpair1.first)).second, (*(returnrealpair1.first)).second);
		ASSERT_EQ(returnpair1.second, returnrealpair1.second);
		ASSERT_EQ((*(returnpair2.first)).first, (*(returnrealpair2.first)).first);
		ASSERT_EQ((*(returnpair2.first)).second, (*(returnrealpair2.first)).second);
		ASSERT_EQ(returnpair2.second, returnrealpair2.second);
	}

	// Attempt to insert duplicate element
	ft::pair<int,TypeParam>			pair1(i_vec[3], type_vec[3]);
	std::pair<int,TypeParam>		realpair1(i_vec[3], type_vec[3]);
	ft::pair<TypeParam,int>			pair2(type_vec[3], i_vec[3]);
	std::pair<TypeParam,int>		realpair2(type_vec[3], i_vec[3]);
	map1.insert(pair1);
	realmap1.insert(realpair1);
	map2.insert(pair2);
	realmap2.insert(realpair2);

	testMaps(map1, realmap1);
	testMaps(map2, realmap2);
}

TYPED_TEST(map_tester, insert_correct_hint_test) {
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
	std::sort(i_vec.begin(), i_vec.end());
	std::sort(i_vec_real.begin(), i_vec_real.end());
	std::sort(type_vec.begin(), type_vec.end());
	std::sort(type_vec_real.begin(), type_vec_real.end());
	mapIter1	it1 = map1.end();
	realMapIter1	realit1 = realmap1.end();
	mapIter2	it2 = map2.end();
	realMapIter2	realit2 = realmap2.end();

	for (size_t i = 0; i != i_vec.size() && i != type_vec.size(); i++) {
		ft::pair<int,TypeParam>			pair1(i_vec[i], type_vec[i]);
		std::pair<int,TypeParam>		realpair1(i_vec[i], type_vec[i]);
		ft::pair<TypeParam,int>			pair2(type_vec[i], i_vec[i]);
		std::pair<TypeParam,int>		realpair2(type_vec[i], i_vec[i]);
		if (it1 == map1.end()) {
			it1 = map1.insert(pair1).first;
		}
		else {
			it1 = map1.insert(it1, pair1);
		}
		if (realit1 == realmap1.end())
			realit1 = realmap1.insert(realpair1).first;
		else
			realit1 = realmap1.insert(realit1, realpair1);
		ASSERT_EQ((*it1).first, (*realit1).first);
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

TYPED_TEST(map_tester, insert_incorrect_hint_test) {
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
		if (it1 == map1.end())
			it1 = map1.insert(pair1).first;
		else
			it1 = map1.insert(it1, pair1);
		if (realit1 == realmap1.end())
			realit1 = realmap1.insert(realpair1).first;
		else
			realit1 = realmap1.insert(realit1, realpair1);
		ASSERT_EQ((*it1).first, (*realit1).first);
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

TYPED_TEST(map_tester, insert_range_test) {
	typedef typename ft::pair<int, TypeParam>			pairType1;
	typedef typename std::pair<int, TypeParam>			realPairType1;
	typedef typename ft::pair<TypeParam, int>			pairType2;
	typedef typename std::pair<TypeParam, int>			realPairType2;
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
	ft::vector<pairType1>		pairsvec1 = zip(i_vec, type_vec);
	std::vector<realPairType1>	realpairsvec1 = zip(i_vec_real, type_vec_real);
	ft::vector<pairType2>		pairsvec2 = zip(type_vec, i_vec);
	std::vector<realPairType2>	realpairsvec2 = zip(type_vec_real, i_vec_real);

	map1.insert(pairsvec1.begin(), pairsvec1.end());
	realmap1.insert(realpairsvec1.begin(), realpairsvec1.end());
	map2.insert(pairsvec2.begin(), pairsvec2.end());
	realmap2.insert(realpairsvec2.begin(), realpairsvec2.end());

	testMaps(map1, realmap1);
	testMaps(map2, realmap2);
}

TYPED_TEST(map_tester, erase_by_iterator_test) {
	ft::map<int, TypeParam>		map1;
	std::map<int, TypeParam>	realmap1;
	ft::map<TypeParam, int>		map2;
	std::map<TypeParam, int>	realmap2;
	size_t						initial_size;

	initialise_default_map(map1, realmap1);
	initialise_default_map(map2, realmap2);

	initial_size = map1.size();
	for (size_t i = 0; i < initial_size; i++) {
		map1.erase(map1.begin());
		realmap1.erase(realmap1.begin());
		map2.erase(map2.begin());
		realmap2.erase(realmap2.begin());
		testMaps(map1, realmap1);
		testMaps(map2, realmap2);
	}

	initialise_default_map(map1, realmap1);
	initialise_default_map(map2, realmap2);
	initial_size = realmap1.size();
	for (size_t i = 0; i < initial_size - 2; i++) {
		map1.erase(incrementIterator(map1.begin(), 2));
		realmap1.erase(incrementIterator(realmap1.begin(), 2));
		map2.erase(incrementIterator(map2.begin(), 2));
		realmap2.erase(incrementIterator(realmap2.begin(), 2));
		testMaps(map1, realmap1);
		testMaps(map2, realmap2);
	}
	map1.clear();
	realmap1.clear();
	map2.clear();
	realmap2.clear();

	initialise_default_map(map1, realmap1);
	initialise_default_map(map2, realmap2);
	initial_size = realmap1.size();
	for (size_t i = 0; i < initial_size - 4; i++) {
		map1.erase(incrementIterator(map1.begin(), map1.size() - 1));
		realmap1.erase(incrementIterator(realmap1.begin(), realmap1.size() - 1));
		map2.erase(incrementIterator(map2.begin(), map2.size() - 1));
		realmap2.erase(incrementIterator(realmap2.begin(), realmap2.size() - 1));
		testMaps(map1, realmap1);
		testMaps(map2, realmap2);
	}
}

TYPED_TEST(map_tester, erase_by_key_test) {
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

	initialise_default_map(map1, realmap1);
	initialise_default_map(map2, realmap2);

	for (size_t i = 0; i < i_vec.size(); i += 2) {
		ASSERT_EQ(map1.erase(i_vec[i]), realmap1.erase(i_vec_real[i]));
		testMaps(map1, realmap1);
	}
	for (size_t i = 0; i < type_vec.size(); i += 2) {
		ASSERT_EQ(map2.erase(type_vec[i]), realmap2.erase(type_vec_real[i]));
		testMaps(map2, realmap2);
	}
}

TYPED_TEST(map_tester, erase_range_test) {
	typedef typename ft::map<int, TypeParam>::iterator			mapIter1;
	typedef typename std::map<int, TypeParam>::iterator			realMapIter1;
	typedef typename ft::map<TypeParam, int>::iterator	mapIter2;
	typedef typename std::map<TypeParam, int>::iterator	realMapIter2;
	ft::map<int, TypeParam>		map1;
	std::map<int, TypeParam>	realmap1;
	ft::map<TypeParam, int>		map2;
	std::map<TypeParam, int>	realmap2;

	initialise_default_map(map1, realmap1);
	initialise_default_map(map2, realmap2);

	mapIter1		tmp1 = map1.begin();
	realMapIter1	realtmp1 = realmap1.begin();
	mapIter2		tmp2 = map2.begin();
	realMapIter2	realtmp2 = realmap2.begin();
	mapIter1		tmp3 = tmp1;
	realMapIter1	realtmp3 = realtmp1;
	mapIter2		tmp4 = tmp2;
	realMapIter2	realtmp4 = realtmp2;

	// Prepare iterators
	for (size_t i = 0; i <= map1.size() / 4; i++) {
		tmp1++;
		realtmp1++;
	}
	tmp3 = tmp1;
	realtmp3 = realtmp1;
	for (size_t i = map1.size() / 4; i <= map1.size() * 3 / 4; i++) {
		tmp3++;
		realtmp3++;
	}
	for (size_t i = 0; i <= map2.size() / 4; i++) {
		tmp2++;
		realtmp2++;
	}
	tmp4 = tmp2;
	realtmp4 = realtmp2;
	for (size_t i = map2.size() / 4; i <= map2.size() * 3 / 4; i++) {
		tmp4++;
		realtmp4++;
	}

	map1.erase(tmp1, tmp3);
	realmap1.erase(realtmp1, realtmp3);
	map2.erase(tmp2, tmp4);
	realmap2.erase(realtmp2, realtmp4);
	testMaps(map1, realmap1);
	testMaps(map2, realmap2);

	map1.erase(map1.begin(), map1.end());
	realmap1.erase(realmap1.begin(), realmap1.end());
	map2.erase(map2.begin(), map2.end());
	realmap2.erase(realmap2.begin(), realmap2.end());
	testMaps(map1, realmap1);
	testMaps(map2, realmap2);

	initialise_default_map(map1, realmap1);
	initialise_default_map(map2, realmap2);

	tmp1 = map1.begin();
	realtmp1 = realmap1.begin();
	tmp2 = map2.begin();
	realtmp2 = realmap2.begin();
	tmp3 = tmp1;
	realtmp3 = realtmp1;
	tmp4 = tmp2;
	realtmp4 = realtmp2;
	// Prepare iterators
	for (size_t i = 0; i <= map1.size() / 6; i++) {
		tmp1++;
		realtmp1++;
	}
	tmp3 = tmp1;
	realtmp3 = realtmp1;
	for (size_t i = map1.size() / 6; i <= map1.size() / 2; i++) {
		tmp3++;
		realtmp3++;
	}
	for (size_t i = 0; i <= map2.size() / 6; i++) {
		tmp2++;
		realtmp2++;
	}
	tmp4 = tmp2;
	realtmp4 = realtmp2;
	for (size_t i = map2.size() / 6; i <= map2.size() / 2; i++) {
		tmp4++;
		realtmp4++;
	}

	map1.erase(tmp1, tmp3);
	realmap1.erase(realtmp1, realtmp3);
	map2.erase(tmp2, tmp4);
	realmap2.erase(realtmp2, realtmp4);
	testMaps(map1, realmap1);
	testMaps(map2, realmap2);

	map1.erase(map1.begin(), map1.end());
	realmap1.erase(realmap1.begin(), realmap1.end());
	map2.erase(map2.begin(), map2.end());
	realmap2.erase(realmap2.begin(), realmap2.end());
	testMaps(map1, realmap1);
	testMaps(map2, realmap2);
}

TYPED_TEST(map_tester, swap_test) {
	ft::map<int, TypeParam>		map1;
	std::map<int, TypeParam>	realmap1;
	ft::map<int, TypeParam>		map3;
	std::map<int, TypeParam>	realmap3;
	ft::map<TypeParam, int>		map2;
	std::map<TypeParam, int>	realmap2;
	ft::map<TypeParam, int>		map4;
	std::map<TypeParam, int>	realmap4;

	initialise_default_map(map1, realmap1);
	initialise_default_map(map2, realmap2);

	ft::vector<int>				i_vec;
	std::vector<int>			i_vec_real;
	ft::vector<TypeParam>		type_vec;
	std::vector<TypeParam>		type_vec_real;
	initialise_default_vector(i_vec, i_vec_real);
	initialise_default_vector(type_vec, type_vec_real);

	for(int i = std::min(i_vec.size(), type_vec.size()) - 1; i >= 0; i--) {
		map3.insert(ft::make_pair(i_vec[i], type_vec[i]));
		realmap3.insert(std::make_pair(i_vec_real[i], type_vec_real[i]));
	}
	for (int i = std::min(type_vec.size(), i_vec.size()) - 1; i >= 0; i--) {
		map4.insert(ft::make_pair(type_vec[i], i_vec[i]));
		realmap4.insert(std::make_pair(type_vec_real[i], i_vec_real[i]));
	}
	map1.swap(map3);
	realmap1.swap(realmap3);
	map2.swap(map4);
	realmap2.swap(realmap4);
	testMaps(map1, realmap1);
	testMaps(map2, realmap2);
}

TYPED_TEST(map_tester, count_test) {
	ft::map<int, TypeParam>		map1;
	std::map<int, TypeParam>	realmap1;
	ft::map<TypeParam, int>		map2;
	std::map<TypeParam, int>	realmap2;

	initialise_default_map(map1, realmap1);
	initialise_default_map(map2, realmap2);

	ft::vector<int>				i_vec;
	std::vector<int>			i_vec_real;
	ft::vector<TypeParam>		type_vec;
	std::vector<TypeParam>		type_vec_real;
	initialise_default_vector(i_vec, i_vec_real);
	initialise_default_vector(type_vec, type_vec_real);

	for(int i = std::min(i_vec.size(), type_vec.size()) - 1; i >= 0; i--) {
		ASSERT_EQ(map1.count(i_vec[i]), realmap1.count(i_vec_real[i]));
	}
	for (int i = std::min(type_vec.size(), i_vec.size()) - 1; i >= 0; i--) {
		ASSERT_EQ(map2.count(type_vec[i]), realmap2.count(type_vec_real[i]));
	}
}

TYPED_TEST(map_tester, lower_bound_test) {
	typedef typename ft::map<int, TypeParam>::iterator			mapIter1;
	typedef typename std::map<int, TypeParam>::iterator			realMapIter1;
	typedef typename ft::map<TypeParam, int>::iterator	mapIter2;
	typedef typename std::map<TypeParam, int>::iterator	realMapIter2;
	ft::map<int, TypeParam>		map1;
	std::map<int, TypeParam>	realmap1;
	ft::map<TypeParam, int>		map2;
	std::map<TypeParam, int>	realmap2;

	initialise_default_map(map1, realmap1);
	initialise_default_map(map2, realmap2);

	ft::vector<int>				i_vec;
	std::vector<int>			i_vec_real;
	ft::vector<TypeParam>		type_vec;
	std::vector<TypeParam>		type_vec_real;
	initialise_default_vector(i_vec, i_vec_real);
	initialise_default_vector(type_vec, type_vec_real);

	for(int i = std::min(i_vec.size(), type_vec.size()) - 1; i >= 0; i--) {
		mapIter1 		it1 = map1.lower_bound(i_vec[i]);
		realMapIter1	realit1 = realmap1.lower_bound(i_vec_real[i]);
		if (it1 == map1.end()) {
			ASSERT_TRUE(realit1 == realmap1.end());
			continue ;
		}
		ASSERT_EQ((*it1).first, (*realit1).first);
		ASSERT_EQ((*it1).second, (*realit1).second);
	}
	for (int i = std::min(type_vec.size(), i_vec.size()) - 1; i >= 0; i--) {
		mapIter2 		it2 = map2.lower_bound(type_vec[i]);
		realMapIter2	realit2 = realmap2.lower_bound(type_vec_real[i]);
		if (it2 == map2.end()) {
			ASSERT_TRUE(realit2 == realmap2.end());
			continue ;
		}
		ASSERT_EQ((*it2).first, (*realit2).first);
		ASSERT_EQ((*it2).second, (*realit2).second);
	}
}

TYPED_TEST(map_tester, upper_bound_test) {
	typedef typename ft::map<int, TypeParam>::iterator			mapIter1;
	typedef typename std::map<int, TypeParam>::iterator			realMapIter1;
	typedef typename ft::map<TypeParam, int>::iterator	mapIter2;
	typedef typename std::map<TypeParam, int>::iterator	realMapIter2;
	ft::map<int, TypeParam>		map1;
	std::map<int, TypeParam>	realmap1;
	ft::map<TypeParam, int>		map2;
	std::map<TypeParam, int>	realmap2;

	initialise_default_map(map1, realmap1);
	initialise_default_map(map2, realmap2);

	ft::vector<int>				i_vec;
	std::vector<int>			i_vec_real;
	ft::vector<TypeParam>		type_vec;
	std::vector<TypeParam>		type_vec_real;
	initialise_default_vector(i_vec, i_vec_real);
	initialise_default_vector(type_vec, type_vec_real);

	for(int i = std::min(i_vec.size(), type_vec.size()) - 1; i >= 0; i--) {
		mapIter1 		it1 = map1.upper_bound(i_vec[i]);
		realMapIter1	realit1 = realmap1.upper_bound(i_vec_real[i]);
		if (it1 == map1.end()) {
			ASSERT_TRUE(realit1 == realmap1.end());
			continue ;
		}
		ASSERT_EQ((*it1).first, (*realit1).first);
		ASSERT_EQ((*it1).second, (*realit1).second);
	}
	for (int i = std::min(type_vec.size(), i_vec.size()) - 1; i >= 0; i--) {
		mapIter2 		it2 = map2.upper_bound(type_vec[i]);
		realMapIter2	realit2 = realmap2.upper_bound(type_vec_real[i]);
		if (it2 == map2.end()) {
			ASSERT_TRUE(realit2 == realmap2.end());
			continue ;
		}
		ASSERT_EQ((*it2).first, (*realit2).first);
		ASSERT_EQ((*it2).second, (*realit2).second);
	}
}

TYPED_TEST(map_tester, equal_range_test) {
	typedef typename ft::map<int, TypeParam>::iterator			mapIter1;
	typedef typename std::map<int, TypeParam>::iterator			realMapIter1;
	typedef typename ft::map<TypeParam, int>::iterator	mapIter2;
	typedef typename std::map<TypeParam, int>::iterator	realMapIter2;
	typedef typename ft::pair<mapIter1, mapIter1>				pair1;
	typedef typename std::pair<realMapIter1, realMapIter1>		realPair1;
	typedef typename ft::pair<mapIter2, mapIter2>				pair2;
	typedef typename std::pair<realMapIter2, realMapIter2>		realPair2;
	ft::map<int, TypeParam>		map1;
	std::map<int, TypeParam>	realmap1;
	ft::map<TypeParam, int>		map2;
	std::map<TypeParam, int>	realmap2;

	initialise_default_map(map1, realmap1);
	initialise_default_map(map2, realmap2);

	ft::vector<int>				i_vec;
	std::vector<int>			i_vec_real;
	ft::vector<TypeParam>		type_vec;
	std::vector<TypeParam>		type_vec_real;
	initialise_default_vector(i_vec, i_vec_real);
	initialise_default_vector(type_vec, type_vec_real);

	for(int i = std::min(i_vec.size(), type_vec.size()) - 1; i >= 0; i--) {
		pair1 		p1 = map1.equal_range(i_vec[i]);
		realPair1	realp1 = realmap1.equal_range(i_vec_real[i]);
		mapIter1	it1 = p1.first;
		mapIter1	it3 = p1.second;
		realMapIter1	realit1 = realp1.first;
		realMapIter1	realit3 = realp1.second;
		if (it1 == map1.end()) {
			ASSERT_TRUE(realit1 == realmap1.end());
			continue ;
		}
		ASSERT_EQ((*it1).first, (*realit1).first);
		ASSERT_EQ((*it1).second, (*realit1).second);
		if (it3 == map1.end()) {
			ASSERT_TRUE(realit3 == realmap1.end());
			continue ;
		}
		ASSERT_EQ((*it3).first, (*realit3).first);
		ASSERT_EQ((*it3).second, (*realit3).second);
	}
	for (int i = std::min(type_vec.size(), i_vec.size()) - 1; i >= 0; i--) {
		pair2 		p2 = map2.equal_range(type_vec[i]);
		realPair2	realp2 = realmap2.equal_range(type_vec_real[i]);
		mapIter2	it2 = p2.first;
		mapIter2	it4 = p2.second;
		realMapIter2	realit2 = realp2.first;
		realMapIter2	realit4 = realp2.second;
		if (it2 == map2.end()) {
			ASSERT_TRUE(realit2 == realmap2.end());
			continue ;
		}
		ASSERT_EQ((*it2).first, (*realit2).first);
		ASSERT_EQ((*it2).second, (*realit2).second);
		if (it4 == map2.end()) {
			ASSERT_TRUE(realit4 == realmap2.end());
			continue ;
		}
		ASSERT_EQ((*it4).first, (*realit4).first);
		ASSERT_EQ((*it4).second, (*realit4).second);
	}
}

TYPED_TEST(map_tester, find_test) {
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

	initialise_default_map(map1, realmap1);
	initialise_default_map(map2, realmap2);

	for (size_t i = 0; i < i_vec.size(); i += 2) {
		mapIter1 it1 = map1.find(i_vec[i]);
		realMapIter1 real_it1 = realmap1.find(i_vec_real[i]);
		if (it1 == map1.end()) {
			ASSERT_TRUE(real_it1 == realmap1.end());
			continue ;
		} else {
			ASSERT_EQ((*map1.find(i_vec[i])).first, (*realmap1.find(i_vec_real[i])).first);
			ASSERT_EQ((*map1.find(i_vec[i])).second, (*realmap1.find(i_vec_real[i])).second);
		}
	}
	for (size_t i = 0; i < type_vec.size(); i += 2) {
		mapIter2 it2 = map2.find(type_vec[i]);
		realMapIter2 real_it2 = realmap2.find(type_vec_real[i]);
		if (it2 == map2.end()) {
			ASSERT_TRUE(real_it2 == realmap2.end());
			continue ;
		} else {
			ASSERT_EQ((*map2.find(type_vec[i])).first, (*realmap2.find(type_vec_real[i])).first);
			ASSERT_EQ((*map2.find(type_vec[i])).second, (*realmap2.find(type_vec_real[i])).second);
		}
	}
}

TYPED_TEST(map_tester, max_size_test) {
	ft::map<int, TypeParam>		map1;
	std::map<int, TypeParam>	realmap1;
	ft::map<TypeParam, int>		map2;
	std::map<TypeParam, int>	realmap2;

	size_t						diff;

	diff = std::max(map1.max_size(), realmap1.max_size()) -
		std::min(map1.max_size(), realmap1.max_size());
	ASSERT_TRUE(diff < 100);
	diff = std::max(map2.max_size(), realmap2.max_size()) -
		std::min(map2.max_size(), realmap2.max_size());
	ASSERT_TRUE(diff < 100);
}

TYPED_TEST(map_tester, default_key_compare_test) {
	ft::map<int, TypeParam>		map1;
	std::map<int, TypeParam>	realmap1;
	ft::map<TypeParam, int>		map2;
	std::map<TypeParam, int>	realmap2;
	ft::vector<int>				i_vec;
	std::vector<int>			i_vec_real;
	initialise_default_vector(i_vec, i_vec_real);

	std::sort(i_vec.begin(), i_vec.end());
	std::sort(i_vec_real.begin(), i_vec_real.end());
	initialise_default_map(map1, realmap1);
	initialise_default_map(map2, realmap2);

	typename ft::map<int, TypeParam>::key_compare	comp1 = realmap1.key_comp();
	typename std::map<int, TypeParam>::key_compare	realcomp1 = realmap1.key_comp();

	for (size_t i = 0; i < i_vec.size() - 1; i++) {
		ASSERT_TRUE(comp1(i_vec[i], i_vec[i + 1]));
		ASSERT_TRUE(realcomp1(i_vec_real[i], i_vec_real[i + 1]));
	}
}

TYPED_TEST(map_tester, custom_key_compare_test) {
	ft::map<int, TypeParam, std::greater<int> >		map1;
	std::map<int, TypeParam, std::greater<int> >	realmap1;
	ft::map<TypeParam, int, std::greater<TypeParam> >		map2;
	std::map<TypeParam, int, std::greater<TypeParam> >	realmap2;
	ft::vector<int>				i_vec;
	std::vector<int>			i_vec_real;
	initialise_default_vector(i_vec, i_vec_real);

	std::sort(i_vec.begin(), i_vec.end());
	std::sort(i_vec_real.begin(), i_vec_real.end());
	initialise_default_map(map1, realmap1);
	initialise_default_map(map2, realmap2);

	testMaps(map1, realmap1);
	testMaps(map2, realmap2);

	typename ft::map<int, TypeParam, std::greater<int> >::key_compare	comp1 = realmap1.key_comp();
	typename std::map<int, TypeParam, std::greater<int> >::key_compare	realcomp1 = realmap1.key_comp();

	for (size_t i = i_vec.size() - 1; i > 1; i--) {
		ASSERT_TRUE(comp1(i_vec[i], i_vec[i - 1]));
		ASSERT_TRUE(realcomp1(i_vec_real[i], i_vec_real[i - 1]));
	}
}

TYPED_TEST(map_tester, value_compare_test) {
	typedef typename ft::map<int, TypeParam, std::greater<int> >::iterator			mapIter1;
	typedef typename std::map<int, TypeParam, std::greater<int> >::iterator			realMapIter1;
	typedef typename ft::map<TypeParam, int, std::greater<TypeParam> >::iterator	mapIter2;
	typedef typename std::map<TypeParam, int, std::greater<TypeParam> >::iterator	realMapIter2;
	ft::map<int, TypeParam, std::greater<int> >			map1;
	std::map<int, TypeParam, std::greater<int> >		realmap1;
	ft::map<TypeParam, int, std::greater<TypeParam> >	map2;
	std::map<TypeParam, int, std::greater<TypeParam> >	realmap2;
	mapIter1 		it1 = map1.begin();
	realMapIter1 	realit1 = realmap1.begin();
	mapIter2 		it2 = map2.begin();
	realMapIter2 	realit2 = realmap2.begin();
	mapIter1		tmp1;
	realMapIter1	realtmp1;
	mapIter2		tmp2;
	realMapIter2	realtmp2;
	mapIter1		tmp3;
	realMapIter1	realtmp3;
	mapIter2		tmp4;
	realMapIter2	realtmp4;
	while (it1 != map1.end()) {
		tmp1 = it1;
		realtmp1 = realit1;
		it1++;
		realit1++;
	}
	it1 = tmp1;
	realit1 = realtmp1;
	while (it2 != map2.end()) {
		tmp2 = it2;
		realtmp2 = realit2;
		it2++;
		realit2++;
	}
	it2 = tmp2;
	realit2 = realtmp2;

	initialise_default_map(map1, realmap1);
	initialise_default_map(map2, realmap2);

	for (; it1 != tmp1 && realit1 != realtmp1; it1++, realit1++) {
		tmp3 = it1;
		tmp3++;
		realtmp3 = realit1;
		realtmp3++;
		ASSERT_EQ(map1.value_comp()(*it1, *tmp3), realmap1.value_comp()(*realit1, *realtmp3));
	}
	for (; it2 != tmp2 && realit2 != realtmp2; it2++, realit2++) {
		tmp4 = it2;
		tmp4++;
		realtmp4 = realit2;
		realtmp4++;
		ASSERT_EQ(map2.value_comp()(*it2, *tmp4), realmap2.value_comp()(*realit2, *realtmp4));
	}
}

TYPED_TEST(map_tester, element_access_test) {
	ft::map<int, TypeParam, std::greater<int> >			map1;
	std::map<int, TypeParam, std::greater<int> >		realmap1;
	ft::map<TypeParam, int, std::greater<TypeParam> >	map2;
	std::map<TypeParam, int, std::greater<TypeParam> >	realmap2;
	ft::vector<int>				i_vec;
	std::vector<int>			i_vec_real;
	initialise_default_vector(i_vec, i_vec_real);
	ft::vector<TypeParam>		type_vec;
	std::vector<TypeParam>		type_vec_real;
	initialise_default_vector(type_vec, type_vec_real);

	for (size_t i = 0; i < i_vec.size() / 2; i++) {
		ft::pair<int,TypeParam>			pair1(i_vec[i], type_vec[i]);
		std::pair<int,TypeParam>		realpair1(i_vec[i], type_vec[i]);
		ft::pair<TypeParam,int>			pair2(type_vec[i], i_vec[i]);
		std::pair<TypeParam,int>		realpair2(type_vec[i], i_vec[i]);

		map1.insert(pair1);
		realmap1.insert(realpair1);
		map2.insert(pair2);
		realmap2.insert(realpair2);
	}
	// Accessing existing elements
	for (size_t i = 0; i < i_vec.size() / 2; i++) {
		ASSERT_EQ(map1[i_vec[i]], realmap1[i_vec[i]]);
		ASSERT_EQ(map2[type_vec[i]], realmap2[type_vec[i]]);
	}
	ASSERT_EQ(map1.size(), realmap1.size());
	ASSERT_EQ(map2.size(), realmap2.size());

	// Accessing newly created elements
	for (size_t i = i_vec.size() / 2; i < i_vec.size(); i++) {
		ASSERT_EQ(map1[i_vec[i]], realmap1[i_vec[i]]);
		ASSERT_EQ(map2[type_vec[i]], realmap2[type_vec[i]]);
	}
	ASSERT_EQ(map1.size(), realmap1.size());
	ASSERT_EQ(map2.size(), realmap2.size());
}

TYPED_TEST(map_tester, iteration_test) {
	typedef typename ft::map<int, TypeParam>::iterator	mapIter1;
	typedef typename std::map<int, TypeParam>::iterator	realMapIter1;
	typedef typename ft::map<TypeParam, int>::iterator	mapIter2;
	typedef typename std::map<TypeParam, int>::iterator	realMapIter2;
	ft::map<int, TypeParam>		map1;
	std::map<int, TypeParam>	realmap1;
	ft::map<TypeParam, int>		map2;
	std::map<TypeParam, int>	realmap2;

	initialise_default_map(map1, realmap1);
	initialise_default_map(map2, realmap2);

	mapIter1 		it1 = map1.begin();
	realMapIter1 	realit1 = realmap1.begin();
	mapIter2 		it2 = map2.begin();
	realMapIter2 	realit2 = realmap2.begin();
	for (; it1 != map1.end() && realit1 != realmap1.end(); it1++, realit1++) {
		ASSERT_EQ((*it1).first, (*realit1).first);
		ASSERT_EQ((*it1).second, (*realit1).second);
	}
	for (; it2 != map2.end() && realit2 != realmap2.end(); it2++, realit2++) {
		ASSERT_EQ((*it2).first, (*realit2).first);
		ASSERT_EQ((*it2).second, (*realit2).second);
	}
}

TYPED_TEST(map_tester, decremental_iteration_test) {
	typedef typename ft::map<int, TypeParam>::iterator	mapIter1;
	typedef typename std::map<int, TypeParam>::iterator	realMapIter1;
	typedef typename ft::map<TypeParam, int>::iterator	mapIter2;
	typedef typename std::map<TypeParam, int>::iterator	realMapIter2;
	ft::map<int, TypeParam>		map1;
	std::map<int, TypeParam>	realmap1;
	ft::map<TypeParam, int>		map2;
	std::map<TypeParam, int>	realmap2;

	initialise_default_map(map1, realmap1);
	initialise_default_map(map2, realmap2);

	mapIter1		it1 = map1.begin();
	realMapIter1	realit1 = realmap1.begin();
	mapIter2		it2 = map2.begin();
	realMapIter2	realit2 = realmap2.begin();
	mapIter1		tmp1;
	realMapIter1	realtmp1;
	mapIter2		tmp2;
	realMapIter2	realtmp2;
	// Iterate to end of map, then decrement by one
	while (it1 != map1.end()) {
		tmp1 = it1;
		realtmp1 = realit1;
		it1++;
		realit1++;
	}
	it1 = tmp1;
	realit1 = realtmp1;
	while (it2 != map2.end()) {
		tmp2 = it2;
		realtmp2 = realit2;
		it2++;
		realit2++;
	}
	it2 = tmp2;
	realit2 = realtmp2;
	for (; it1 != map1.begin() && realit1 != realmap1.begin(); it1--, realit1--) {
		ASSERT_EQ((*it1).first, (*realit1).first);
		ASSERT_EQ((*it1).second, (*realit1).second);
	}
	for (; it2 != map2.begin() && realit2 != realmap2.begin(); it2--, realit2--) {
		ASSERT_EQ((*it2).first, (*realit2).first);
		ASSERT_EQ((*it2).second, (*realit2).second);
	}
	it1 = map1.end();
	realit1 = realmap1.end();
	it2 = map2.end();
	realit2 = realmap2.end();
	it1--;
	realit1--;
	it2--;
	realit2--;
	ASSERT_TRUE(it1 == tmp1);
	ASSERT_TRUE(realit1 == realtmp1);
	ASSERT_TRUE(it2 == tmp2);
	ASSERT_TRUE(realit2 == realtmp2);
}

TYPED_TEST(map_tester, reverse_iteration_test) {
	typedef typename ft::map<int, TypeParam>::reverse_iterator	mapIter1;
	typedef typename std::map<int, TypeParam>::reverse_iterator	realMapIter1;
	typedef typename ft::map<TypeParam, int>::reverse_iterator	mapIter2;
	typedef typename std::map<TypeParam, int>::reverse_iterator	realMapIter2;
	ft::map<int, TypeParam>		map1;
	std::map<int, TypeParam>	realmap1;
	ft::map<TypeParam, int>		map2;
	std::map<TypeParam, int>	realmap2;

	initialise_default_map(map1, realmap1);
	initialise_default_map(map2, realmap2);

	mapIter1		it1 = map1.rbegin();
	realMapIter1	realit1 = realmap1.rbegin();
	mapIter2		it2 = map2.rbegin();
	realMapIter2	realit2 = realmap2.rbegin();
	for (; it1 != map1.rend() && realit1 != realmap1.rend(); it1++, realit1++) {
		ASSERT_EQ((*it1).first, (*realit1).first);
		ASSERT_EQ((*it1).second, (*realit1).second);
	}
	for (; it2 != map2.rend() && realit2 != realmap2.rend(); it2++, realit2++) {
		ASSERT_EQ((*it2).first, (*realit2).first);
		ASSERT_EQ((*it2).second, (*realit2).second);
	}
}

TYPED_TEST(map_tester, reverse_decremental_iteration_test) {
	typedef typename ft::map<int, TypeParam>::reverse_iterator	mapIter1;
	typedef typename std::map<int, TypeParam>::reverse_iterator	realMapIter1;
	typedef typename ft::map<TypeParam, int>::reverse_iterator	mapIter2;
	typedef typename std::map<TypeParam, int>::reverse_iterator	realMapIter2;
	ft::map<int, TypeParam>		map1;
	std::map<int, TypeParam>	realmap1;
	ft::map<TypeParam, int>		map2;
	std::map<TypeParam, int>	realmap2;

	initialise_default_map(map1, realmap1);
	initialise_default_map(map2, realmap2);

	mapIter1		it1 = map1.rbegin();
	realMapIter1	realit1 = realmap1.rbegin();
	mapIter2		it2 = map2.rbegin();
	realMapIter2	realit2 = realmap2.rbegin();
	mapIter1		tmp1;
	realMapIter1	realtmp1;
	mapIter2		tmp2;
	realMapIter2	realtmp2;
	while (it1 != map1.rend()) {
		tmp1 = it1;
		realtmp1 = realit1;
		it1++;
		realit1++;
	}
	it1 = tmp1;
	realit1 = realtmp1;
	while (it2 != map2.rend()) {
		tmp2 = it2;
		realtmp2 = realit2;
		it2++;
		realit2++;
	}
	it2 = tmp2;
	realit2 = realtmp2;
	for (; it1 != map1.rbegin() && realit1 != realmap1.rbegin(); it1--, realit1--) {
		ASSERT_EQ((*it1).first, (*realit1).first);
		ASSERT_EQ((*it1).second, (*realit1).second);
	}
	for (; it2 != map2.rbegin() && realit2 != realmap2.rbegin(); it2--, realit2--) {
		ASSERT_EQ((*it2).first, (*realit2).first);
		ASSERT_EQ((*it2).second, (*realit2).second);
	}
}

TYPED_TEST(map_tester, iterator_relational_operators_tests) {
	typedef typename ft::map<int, TypeParam>::const_iterator	mapIter1;
	typedef typename std::map<int, TypeParam>::const_iterator	realMapIter1;
	typedef typename ft::map<TypeParam, int>::const_iterator	mapIter2;
	typedef typename std::map<TypeParam, int>::const_iterator	realMapIter2;
	typedef typename ft::map<int, TypeParam>::iterator	nc_mapIter1;
	typedef typename std::map<int, TypeParam>::iterator	nc_realMapIter1;
	typedef typename ft::map<TypeParam, int>::iterator	nc_mapIter2;
	typedef typename std::map<TypeParam, int>::iterator	nc_realMapIter2;
	ft::map<int, TypeParam>		map1;
	std::map<int, TypeParam>	realmap1;
	ft::map<TypeParam, int>		map2;
	std::map<TypeParam, int>	realmap2;

	initialise_default_map(map1, realmap1);
	initialise_default_map(map2, realmap2);

	nc_mapIter1		nc_it1(map1.begin());
	mapIter1		it1(nc_it1);
	nc_realMapIter1	nc_realit1(realmap1.begin());
	realMapIter1	realit1(nc_realit1);

	ASSERT_EQ((nc_it1 == it1), (nc_realit1 == realit1));
	ASSERT_EQ((nc_it1 != it1), (nc_realit1 != realit1));
	ASSERT_EQ((it1 == nc_it1), (realit1 == nc_realit1));
	ASSERT_EQ((it1 != nc_it1), (realit1 != nc_realit1));
	nc_it1++;
	nc_realit1++;
	ASSERT_EQ((nc_it1 == it1), (nc_realit1 == realit1));
	ASSERT_EQ((nc_it1 != it1), (nc_realit1 != realit1));
	ASSERT_EQ((it1 == nc_it1), (realit1 == nc_realit1));
	ASSERT_EQ((it1 != nc_it1), (realit1 != nc_realit1));

	nc_mapIter2		nc_it2(map2.begin());
	mapIter2		it2(nc_it2);
	nc_realMapIter2	nc_realit2(realmap2.begin());
	realMapIter2	realit2(nc_realit2);

	ASSERT_EQ((nc_it2 == it2), (nc_realit2 == realit2));
	ASSERT_EQ((nc_it2 != it2), (nc_realit2 != realit2));
	ASSERT_EQ((it2 == nc_it2), (realit2 == nc_realit2));
	ASSERT_EQ((it2 != nc_it2), (realit2 != nc_realit2));
	nc_it2++;
	nc_realit2++;
	ASSERT_EQ((nc_it2 == it2), (nc_realit2 == realit2));
	ASSERT_EQ((nc_it2 != it2), (nc_realit2 != realit2));
	ASSERT_EQ((it2 == nc_it2), (realit2 == nc_realit2));
	ASSERT_EQ((it2 != nc_it2), (realit2 != nc_realit2));
}

TYPED_TEST(map_tester, reverse_iterator_relational_operators_tests) {
	typedef typename ft::map<int, TypeParam>::const_reverse_iterator	mapIter1;
	typedef typename std::map<int, TypeParam>::const_reverse_iterator	realMapIter1;
	typedef typename ft::map<TypeParam, int>::const_reverse_iterator	mapIter2;
	typedef typename std::map<TypeParam, int>::const_reverse_iterator	realMapIter2;
	typedef typename ft::map<int, TypeParam>::reverse_iterator	nc_mapIter1;
	typedef typename std::map<int, TypeParam>::reverse_iterator	nc_realMapIter1;
	typedef typename ft::map<TypeParam, int>::reverse_iterator	nc_mapIter2;
	typedef typename std::map<TypeParam, int>::reverse_iterator	nc_realMapIter2;
	ft::map<int, TypeParam>		map1;
	std::map<int, TypeParam>	realmap1;
	ft::map<TypeParam, int>		map2;
	std::map<TypeParam, int>	realmap2;

	initialise_default_map(map1, realmap1);
	initialise_default_map(map2, realmap2);

	nc_mapIter1		nc_it1(map1.rbegin());
	mapIter1		it1(nc_it1);
	nc_realMapIter1	nc_realit1(realmap1.rbegin());
	realMapIter1	realit1(nc_realit1);

	ASSERT_EQ((nc_it1 == it1), (nc_realit1 == realit1));
	ASSERT_EQ((nc_it1 != it1), (nc_realit1 != realit1));
	ASSERT_EQ((it1 == nc_it1), (realit1 == nc_realit1));
	ASSERT_EQ((it1 != nc_it1), (realit1 != nc_realit1));
	nc_it1++;
	nc_realit1++;
	ASSERT_EQ((nc_it1 == it1), (nc_realit1 == realit1));
	ASSERT_EQ((nc_it1 != it1), (nc_realit1 != realit1));
	ASSERT_EQ((it1 == nc_it1), (realit1 == nc_realit1));
	ASSERT_EQ((it1 != nc_it1), (realit1 != nc_realit1));

	nc_mapIter2		nc_it2(map2.rbegin());
	mapIter2		it2(nc_it2);
	nc_realMapIter2	nc_realit2(realmap2.rbegin());
	realMapIter2	realit2(nc_realit2);

	ASSERT_EQ((nc_it2 == it2), (nc_realit2 == realit2));
	ASSERT_EQ((nc_it2 != it2), (nc_realit2 != realit2));
	ASSERT_EQ((it2 == nc_it2), (realit2 == nc_realit2));
	ASSERT_EQ((it2 != nc_it2), (realit2 != nc_realit2));
	nc_it2++;
	nc_realit2++;
	ASSERT_EQ((nc_it2 == it2), (nc_realit2 == realit2));
	ASSERT_EQ((nc_it2 != it2), (nc_realit2 != realit2));
	ASSERT_EQ((it2 == nc_it2), (realit2 == nc_realit2));
	ASSERT_EQ((it2 != nc_it2), (realit2 != nc_realit2));
}

TYPED_TEST(map_tester, relational_operators_test) {
	ft::map<int, TypeParam>		map1;
	std::map<int, TypeParam>	realmap1;
	ft::map<TypeParam, int>		map2;
	std::map<TypeParam, int>	realmap2;

	initialise_default_map(map1, realmap1);
	initialise_default_map(map2, realmap2);

	ft::vector<int>				i_vec;
	std::vector<int>			i_vec_real;
	ft::vector<TypeParam>		type_vec;
	std::vector<TypeParam>		type_vec_real;
	initialise_default_vector(i_vec, i_vec_real);
	initialise_default_vector(type_vec, type_vec_real);

	ft::map<int, TypeParam>		map3(map1);
	std::map<int, TypeParam>	realmap3(realmap1);
	ft::map<TypeParam, int>		map4(map2);
	std::map<TypeParam, int>	realmap4(realmap2);

	ASSERT_EQ((map1 == map3), (realmap1 == realmap3));
	ASSERT_EQ((map1 != map3), (realmap1 != realmap3));
	ASSERT_EQ((map1 < map3), (realmap1 < realmap3));
	ASSERT_EQ((map3 < map1), (realmap3 < realmap1));
	ASSERT_EQ((map1 <= map3), (realmap1 <= realmap3));
	ASSERT_EQ((map3 <= map1), (realmap3 <= realmap1));
	ASSERT_EQ((map1 >= map3), (realmap1 >= realmap3));
	ASSERT_EQ((map3 >= map1), (realmap3 >= realmap1));
	ASSERT_EQ((map1 > map3), (realmap1 > realmap3));
	ASSERT_EQ((map3 > map1), (realmap3 > realmap1));
	addition_to_map(map1, realmap1, type_vec[0]);
	ASSERT_EQ((map1 == map3), (realmap1 == realmap3));
	ASSERT_EQ((map1 != map3), (realmap1 != realmap3));
	ASSERT_EQ((map1 < map3), (realmap1 < realmap3));
	ASSERT_EQ((map3 < map1), (realmap3 < realmap1));
	ASSERT_EQ((map1 <= map3), (realmap1 <= realmap3));
	ASSERT_EQ((map3 <= map1), (realmap3 <= realmap1));
	ASSERT_EQ((map1 >= map3), (realmap1 >= realmap3));
	ASSERT_EQ((map3 >= map1), (realmap3 >= realmap1));
	ASSERT_EQ((map1 > map3), (realmap1 > realmap3));
	ASSERT_EQ((map3 > map1), (realmap3 > realmap1));
	
	ASSERT_EQ((map2 == map4), (realmap2 == realmap4));
	ASSERT_EQ((map2 != map4), (realmap2 != realmap4));
	ASSERT_EQ((map2 < map4), (realmap2 < realmap4));
	ASSERT_EQ((map4 < map2), (realmap4 < realmap2));
	ASSERT_EQ((map2 <= map4), (realmap2 <= realmap4));
	ASSERT_EQ((map4 <= map2), (realmap4 <= realmap2));
	ASSERT_EQ((map2 >= map4), (realmap2 >= realmap4));
	ASSERT_EQ((map4 >= map2), (realmap4 >= realmap2));
	ASSERT_EQ((map2 > map4), (realmap2 > realmap4));
	ASSERT_EQ((map4 > map2), (realmap4 > realmap2));
	addition_to_map(map2, realmap2, i_vec[0]);
	ASSERT_EQ((map2 == map4), (realmap2 == realmap4));
	ASSERT_EQ((map2 != map4), (realmap2 != realmap4));
	ASSERT_EQ((map2 < map4), (realmap2 < realmap4));
	ASSERT_EQ((map4 < map2), (realmap4 < realmap2));
	ASSERT_EQ((map2 <= map4), (realmap2 <= realmap4));
	ASSERT_EQ((map4 <= map2), (realmap4 <= realmap2));
	ASSERT_EQ((map2 >= map4), (realmap2 >= realmap4));
	ASSERT_EQ((map4 >= map2), (realmap4 >= realmap2));
	ASSERT_EQ((map2 > map4), (realmap2 > realmap4));
	ASSERT_EQ((map4 > map2), (realmap4 > realmap2));
}
