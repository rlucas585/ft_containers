/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   stack.hpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/24 11:53:10 by rlucas        #+#    #+#                 */
/*   Updated: 2021/01/24 12:07:50 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft {
	template <typename T, typename Container = vector<T> >
		class stack {
			public:
				typedef T									value_type;
				typedef Container							container_type;
				typedef typename container_type::size_type	size_type;

				explicit stack(const container_type& cntr = container_type())
					: _c(cntr)
				{
				}

				bool	empty(void) const {
					return _c.empty();
				}

				size_type	size(void) const {
					return _c.size();
				}

				value_type&	top(void) {
					return _c.back();
				}

				const value_type&	top(void) const {
					return _c.back();
				}

				void	push(const value_type& val) {
					_c.push_back(val);
				}

				void	pop(void) {
					_c.pop_back();
				}

			protected:
				container_type		_c;
		};

	template <class T, class Container>
		bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
			return lhs._c == rhs._c;
		}

	template <class T, class Container>
		bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
			return !(lhs == rhs);
		}

	template <class T, class Container>
		bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
			return lhs._c < rhs._c;
		}

	template <class T, class Container>
		bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
			return !(rhs < lhs);
		}

	template <class T, class Container>
		bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
			return rhs < lhs;
		}

	template <class T, class Container>
		bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
			return !(lhs < rhs);
		}
}

#endif
