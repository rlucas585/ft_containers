/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <ryanl585codam@gmail.com>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/06 12:49:55 by rlucas        #+#    #+#                 */
/*   Updated: 2021/03/13 15:56:39 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>

#include "test.hpp"

#include "map.hpp"

void introduce(void);

int		main(void)
{
    introduce();

    ft::map<int, std::string> my_map;

    my_map.insert(ft::make_pair(1, "Leeds"));
    my_map.insert(ft::make_pair(20, "Man Utd"));
    my_map.insert(ft::make_pair(19, "Liverpool"));
    my_map.insert(ft::make_pair(18, "Arsenal"));
    my_map.insert(ft::make_pair(2, "Newcastle"));

    for (ft::map<int, std::string>::const_iterator it = my_map.begin(); it != my_map.end(); ++it) {
        std::cout << "(" << it->first << ", " << it->second << ")" << std::endl;
    }

	return (0);
}

void introduce(void) {
    std::cout << "This is the ft_containers project, by Ryan Lucas\n";
    std::cout << "------------------------------------------------\n";
    std::cout << "If you're seeing this output, you've just compiled and run the ft_containers binary!\n";
    std::cout << "This project involved reimplementing several containers from the C++ standard\n"
        "template library, all in C++98\n\n";
    std::cout << "This output is determined by the code in src/main.cpp, feel free to change the code in this\n"
        "file, and experiment with the containers!\n";
    std::cout << "If you'd like to run an extensive test of all the features that ft_containers has\n"
        "to offer, and verify that they function in the same way as the std containers, then run ./test.sh\n\n";

    std::cout << "Finally, to remove this wordy introduction, simply comment out the introduce function\n"
        "in src/main.cpp\n\n";
    std::cout << "Output of experimental code:" << std::endl;
        
}
