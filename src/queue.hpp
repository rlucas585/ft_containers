/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   queue.hpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/13 15:09:18 by rlucas        #+#    #+#                 */
/*   Updated: 2021/03/13 15:27:55 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "list.hpp"

namespace ft {
	template <typename T, typename Container = list<T> >
		class queue {
			public:
				typedef T									value_type;
				typedef Container							container_type;
				typedef typename container_type::size_type	size_type;

				explicit queue(const container_type& cntr = container_type())
					: _c(cntr)
				{
				}

				~queue(void) {
				}

				bool	empty(void) const {
					return _c.empty();
				}

				size_type	size(void) const {
					return _c.size();
				}

				value_type& front(void) {
					return _c.front();
				}

				const value_type& front(void) const {
					return _c.front();
				}

				value_type& back(void) {
					return _c.back();
				}

				const value_type& back(void) const {
					return _c.back();
				}

				void	push(const value_type& val) {
					_c.push_back(val);
				}

				void	pop(void) {
					_c.pop_front();
				}

			protected:
				container_type		_c;


				friend bool operator==(const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
					return lhs._c == rhs._c;
				}
				friend bool operator!= (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
					return !(lhs == rhs);
				}
				friend bool operator<  (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
					return lhs._c < rhs._c;
				}
				friend bool operator<= (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
					return !(rhs < lhs);
				}
				friend bool operator>  (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
					return rhs < lhs;
				}
				friend bool operator>= (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
					return !(lhs < rhs);
				}

		};
}

#endif
