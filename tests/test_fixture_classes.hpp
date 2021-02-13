/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_fixture_classes.hpp                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/13 18:54:50 by rlucas        #+#    #+#                 */
/*   Updated: 2021/02/13 19:03:32 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_FIXTURE_CLASSES_HPP
#define TEST_FIXTURE_CLASSES_HPP

#include <gtest/gtest.h>

template <typename T>
class vector_tester : public ::testing::Test {
};

typedef testing::Types<int, std::string> Implementations;

#endif
