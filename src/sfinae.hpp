/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sfinae.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/15 17:27:19 by rlucas        #+#    #+#                 */
/*   Updated: 2021/01/15 17:30:56 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SFINAE_HPP
# define SFINAE_HPP

namespace ft {
	template <bool B, class T = void>
		struct enable_if {};

	template <class T>
		struct enable_if<true, T> { typedef T type; };

	template <class T>
		class isIterator {
			private:
				typedef char	_one;
				struct _two { char x[2]; };

				template <typename U> static _one _test(
						typename U::iterator_category* = 0
						);
				template <class U> static _two _test(...);
			public:
				enum { value = sizeof(_test<T>(0)) == sizeof(char) };
		};
}

#endif
