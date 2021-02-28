/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map.cpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/21 15:01:14 by rlucas        #+#    #+#                 */
/*   Updated: 2021/02/28 12:20:37 by rlucas        ########   odam.nl         */
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

// TYPED_TEST(map_tester, single_element_iteration_test) {
// 	typedef typename ft::map<int, TypeParam>::iterator	mapIter1;
// 	// typedef typename std::map<int, TypeParam>::iterator	realMapIter1;
// 	ft::map<int, TypeParam>		map1;
// 	std::map<int, TypeParam>	realmap1;
// 	ft::vector<int>				i_vec;
// 	std::vector<int>			i_vec_real;
// 	ft::vector<TypeParam>		type_vec;
// 	std::vector<TypeParam>		type_vec_real;
// 	initialise_default_vector(i_vec, i_vec_real);
// 	initialise_default_vector(type_vec, type_vec_real);
// 	ft::pair<int,TypeParam>			pair1(i_vec[0], type_vec[0]);
// 	std::pair<int,TypeParam>		realpair1(i_vec[0], type_vec[0]);
//
// 	map1.insert(pair1);
// 	realmap1.insert(realpair1);
// 	mapIter1	it1 = map1.begin();
// }
//
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
