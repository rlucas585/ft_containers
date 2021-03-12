/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_fixture_classes.hpp                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/13 18:54:50 by rlucas        #+#    #+#                 */
/*   Updated: 2021/03/12 16:29:09 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_FIXTURE_CLASSES_HPP
#define TEST_FIXTURE_CLASSES_HPP

#include <gtest/gtest.h>
#include "Example.hpp"

template <typename T>
class vector_tester : public ::testing::Test {
};

template <typename T>
class list_tester : public ::testing::Test {
};

template <typename T>
class map_tester : public ::testing::Test {
};

template <typename T>
class stack_tester : public ::testing::Test {
};

typedef testing::Types<int, std::string, Example> Implementations;

#endif
