/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   reverse_bi_iterator.hpp                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/20 16:31:39 by rlucas        #+#    #+#                 */
/*   Updated: 2021/02/27 17:25:18 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_BI_ITERATOR_HPP
# define REVERSE_BI_ITERATOR_HPP 

# include <iterator>
# include "list_iterator.hpp"

namespace ft {
	template <typename Iter>
		class ReverseBiIterator {
			private:
				typedef Iter										iterator_type;

			public:
				typedef typename iterator_type::iterator_category	iterator_category;
				typedef typename iterator_type::value_type			value_type;
				typedef typename iterator_type::difference_type		difference_type;
				typedef typename iterator_type::pointer				pointer;
				typedef typename iterator_type::reference			reference;
				typedef typename iterator_type::node_pointer		node_pointer;
				typedef ReverseBiIterator<iterator_type>			this_type;
				typedef ReverseBiIterator<typename iterator_type::const_type>
					const_type;

			private:
				iterator_type	_it;

			public:
				ReverseBiIterator(void) : _it(0) {}
				ReverseBiIterator(node_pointer p) : _it(iterator_type(p)) {}
				explicit ReverseBiIterator(iterator_type const& src) : _it(src) {
					_it--;
				}
				ReverseBiIterator(const ReverseBiIterator &src) : _it(src._it) {}
                ReverseBiIterator& operator=(const ReverseBiIterator &rhs) {
                    if (this == &rhs) { return *this; }
                    _it = rhs._it;
                    return *this;
                }
				iterator_type	base(void) const {
					iterator_type	tmp(_it);

					tmp++;
					return tmp;
				}

				this_type		&operator++() {
					_it--;
					return *this;
				}
				this_type		operator++(int) {
					this_type	tmp(*this);
					operator++();
					return tmp;
				}
				this_type		&operator--() {
					_it++;
					return *this;
				}
				this_type		operator--(int) {
					this_type	tmp(*this);
					operator--();
					return tmp;
				}
				reference		operator*() {
					return *_it;
				}
				pointer			operator->() {
					return &(operator*());
				}
				template <typename Iter1, typename Iter2>
				friend bool operator==(const ReverseBiIterator<Iter1>&, const ReverseBiIterator<Iter2>&);
				template <typename Iter1, typename Iter2>
				friend bool operator!=(const ReverseBiIterator<Iter1>&, const ReverseBiIterator<Iter2>&);
				// bool			operator==(const this_type &rhs) const {
				// 	return _it == rhs._it;
				// }
				// bool		operator!=(const this_type &rhs) const {
				// 	return _it != rhs._it;
				// }
				operator	const_type() const {
					typename iterator_type::const_type	c_it(_it);
					c_it++;

					return (ReverseBiIterator<typename iterator_type::const_type>(c_it));
				}
		};

	template <typename Iter1, typename Iter2>
		inline bool operator==(const ReverseBiIterator<Iter1> &it1,
				const ReverseBiIterator<Iter2> &it2) {
			return it1._it == it2._it;
			// return it1.base() == it2.base();
		}
	template <typename Iter1, typename Iter2>
		inline bool operator!=(const ReverseBiIterator<Iter1> &it1,
				const ReverseBiIterator<Iter2> &it2) {
			return it1._it != it2._it;
			// return it1.base() == it2.base();
		}
}

#endif
