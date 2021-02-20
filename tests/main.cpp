/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/13 17:58:20 by rlucas        #+#    #+#                 */
/*   Updated: 2021/02/20 13:22:38 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <gtest/gtest.h>
#include <iostream>

#include "test_fixture_classes.hpp"

int	main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);

	TYPED_TEST_CASE(vector_tester, Implementations);

	return RUN_ALL_TESTS();
}
