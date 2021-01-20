/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.hpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/06 23:18:06 by rlucas        #+#    #+#                 */
/*   Updated: 2021/01/20 11:04:37 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include <string>
# include "vector.hpp"

void	print_divider(std::string color, std::string message);
void	print_info(std::string color, std::string message);
void	print_line(std::string color);
template <typename T>
void	try_index(ft::vector<T> &vec, size_t i);
template <typename T>
void	print_vector(T &vec);
template <typename T, typename U>
void	print_fake_and_real_collection(T &fake, const char *fake_name,
		U &real, const char *real_name);
template <typename T, typename U>
void	print_fake_and_real(T fake, const char *fake_name,
		U real, const char *real_name);
// template <typename T>
// void	print_list(T &list);

#endif
