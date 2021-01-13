/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Vector.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <ryanl585codam@gmail.com>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/06 12:52:10 by rlucas        #+#    #+#                 */
/*   Updated: 2021/01/10 16:22:09 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP 

# include <iterator>
# include <memory>
# include <stdexcept>
# include <algorithm>

# include "random_access_iterator.hpp"

template <typename T, typename A = std::allocator<T> >
class Vector {

	public:

		typedef A											allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename allocator_type::size_type			size_type;
		typedef typename allocator_type::difference_type	difference_type;
		typedef RandAccessIterator<T, difference_type,
				pointer, reference>							iterator;
		typedef RandAccessIterator<T, difference_type,
				const_pointer, const_reference>				const_iterator;

		Vector(const allocator_type &a = allocator_type())
			: _data(0), _size(0), _capacity(0), _a(a) {
				this->reserve(4);
			};
		Vector(Vector const &src) {
			*this = src;
		}
		~Vector(void) {
			for (size_type i = 0; i < _capacity; i++)
				_a.destroy(_data + i);
			if (_data)
				_a.deallocate(_data, _capacity);
		}

		// Assignment operator
		Vector		&operator=(Vector const &rhs) {
			if (&rhs == this) { return *this; }

			_a = rhs._a;
			if (_data) {
				for (size_type i = 0; i < _capacity; i++)
					_a.destroy(_data + i);
				_a.deallocate(_data, _capacity);
			}
			_data = _a.allocate(rhs._capacity);
			for (size_type i = 0; i < rhs._size; i++)
				_a.construct(_data + i, rhs._data[i]);
			_capacity = rhs._capacity;
			_size = rhs._size;
		}

		// Iterator functions.
		iterator	begin(void) {
			iterator	i(_data);
			return (i);
		}

		iterator	end(void) {
			iterator	i(_data + _size);
			return (i);
		}

		// Capacity functions.
		size_type	size(void) const {
			return (_size);
		}

		void		reserve(size_type n) {
			size_type	new_cap;
			pointer		new_data;
			T			initialized_obj;

			if (n <= _capacity)
				return ;
			new_cap = std::max(n, _capacity * 2);
			new_data = _a.allocate(sizeof(T) * new_cap);
			for (size_type i = 0; i < new_cap; i++) {
				if (i < _size)
					_a.construct(new_data + i, *(_data + i));
				else
					_a.construct(new_data + i, initialized_obj);
			}
			for (size_type i = 0; i < _capacity; i++)
				_a.destroy(_data + i);
			if (_data)
				_a.deallocate(_data, _capacity);
			_capacity = new_cap;
			_data = new_data;
		}

		// Modifier functions.
		void		push(T val) {
			if (_size == _capacity) {
				this->reserve(_capacity * 2);
			}
			*(_data + _size) = val;
			_size += 1;
		}

		// Element Access
		T			&operator[](size_type n) const {
			if (_size == 0 || n > _size - 1)
				throw Vector::OutOfBoundsException();
			return (*(_data + n));
		}

		// Relational operators.

		class	OutOfBoundsException : public std::exception {
			public:
				virtual const char 		*what() const throw() {
					return ("Accessing vector out of Bounds");
				}
		};

	private:
		pointer			_data;
		size_type		_size;
		size_type		_capacity;
		allocator_type	_a;
};

void		test(void);

#endif
