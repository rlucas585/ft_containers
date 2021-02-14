/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <ryanl585codam@gmail.com>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/06 12:52:10 by rlucas        #+#    #+#                 */
/*   Updated: 2021/02/14 18:13:49 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP 

# include <iterator>
# include <memory> /* allocator */
# include <stdexcept>
# include <algorithm>
# include <cmath>
# include <sstream>

# include "random_access_iterator.hpp"
# include "reverse_iterator.hpp"
# include "sfinae.hpp"

# ifndef SYSTEM_BITS
# ifdef __x86_64
# define SYSTEM_BITS 64
# else
# ifdef _M_AMD64
# define SYSTEM_BITS 64
# else
# define SYSTEM_BITS 32
# endif
# endif
# endif

namespace ft {
	template <typename T, typename A = std::allocator<T> >
		class vector {

			public:
				typedef A											allocator_type;
				typedef T											value_type;
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
				typedef ReverseIterator<iterator>					reverse_iterator;
				typedef ReverseIterator<const_iterator>				const_reverse_iterator;

				explicit vector(const allocator_type& alloc = allocator_type())
					: _data(0), _size(0), _capacity(0), _a(alloc) {
						this->reserve(4);
					};
				explicit vector(size_type n, const value_type& val = value_type(),
						const allocator_type &alloc = allocator_type())
					: _data(0), _size(0), _capacity(0), _a(alloc) {
						this->reserve(4);
						this->assign(n, val);
					}
				template <class InputIterator>
					vector (InputIterator first, InputIterator last,
							const allocator_type& alloc = allocator_type())
					: _data(0), _size(0), _capacity(0), _a(alloc) {
						this->reserve(4);
						this->assign(first, last);
					}
				vector(vector const &src) : _data(0), _size(0), _capacity(0) {
					*this = src;
				}
				~vector(void) {
					for (size_type i = 0; i < _size; i++) {
						_a.destroy(_data + i);
					}
					if (_data)
						_a.deallocate(_data, _capacity);
				}

				// Assignment operator
				vector		&operator=(vector const &rhs) {
					if (&rhs == this) { return *this; }

					_a = rhs._a;
					if (_data) {
						if (_capacity > rhs._capacity) {
							for (size_type i = 0; i < rhs._size; i++) {
								_a.destroy(_data + i);
								_a.construct(_data + i, *(rhs._data + i));
							}
							for (size_type i = rhs._size; i < _size; i++)
								_a.destroy(_data + i);
						} else {
							for (size_type i = 0; i < _size; i++)
								_a.destroy(_data + i);
							_a.deallocate(_data, _capacity);
							_data = _a.allocate(rhs._capacity);
							for (size_type i = 0; i < rhs._size; i++)
								_a.construct(_data + i, *(rhs._data + i));
							_capacity = rhs._capacity;
						}
					} else {
						_data = _a.allocate(rhs._size);
						for (size_type i = 0; i < rhs._size; i++)
								_a.construct(_data + i, *(rhs._data + i));
						_capacity = rhs._size;
					}
					_size = rhs._size;
					return (*this);
				}

				// Iterator functions.
				iterator	begin(void) {
					iterator	i(_data);
					return i;
				}

				const_iterator	begin(void) const {
					const_iterator	i(_data);
					return i;
				}

				iterator	end(void) {
					iterator	i(_data + _size);
					return (i);
				}

				const_iterator	end(void) const {
					const_iterator	i(_data + _size);
					return i;
				}

				reverse_iterator	rbegin(void) {
					reverse_iterator	ri(_data + _size - 1);
					return (ri);
				}

				const_reverse_iterator	rbegin(void) const {
					reverse_iterator	ri(_data + _size - 1);
				}

				reverse_iterator	rend(void) {
					reverse_iterator	ri(_data - 1);
					return (ri);
				}

				const_reverse_iterator	rend(void) const {
					const_reverse_iterator	ri(_data - 1);
					return (ri);
				}

				// Capacity functions.
				size_type	size(void) const {
					return (_size);
				}

				size_type	max_size(void) const {
					size_type	ans = std::floor(std::pow(2, SYSTEM_BITS) / sizeof(T));

					return (ans - 1);
				}

				void		resize(size_type n, value_type val = value_type()) {
					if (n < _size) {
						for (size_type i = n; i < _size; i++)
							_a.destroy(_data + i);
					}
					if (n > _capacity) {
						if (n > _size * 2)
							this->reserve(std::max(n, (_capacity * 2) - 2));
						else
							this->reserve(_size * 2);
					}
					for (; _size < n; _size++)
						_a.construct(_data + _size, val);
				}

				size_type	capacity(void) const {
					return _capacity;
				}

				bool		empty(void) const {
					return _size == 0;
				}

				void		reserve(size_type n) {
					size_type	new_cap;	
					pointer		new_data;

					if (n <= _capacity)
						return ;
					// new_cap = std::max(n, _capacity * 2);	// Customization
					// Not in std::vector
					new_cap = n;
					new_data = _a.allocate(sizeof(T) * new_cap);
					for (size_type i = 0; i < _size; i++)
						_a.construct(new_data + i, *(_data + i));
					if (_data) {
						for (size_type i = 0; i < _size; i++)
							_a.destroy(_data + i);
						_a.deallocate(_data, _capacity);
					}
					_capacity = new_cap;
					_data = new_data;
				}

				// Element Access
				reference	operator[](size_type n) {
					return (*(_data + n));
				}

				const_reference	operator[](size_type n) const {
					return *(_data + n);
				}

				reference	at(size_type n) {
					if (_size == 0 || n > _size - 1)
						_runtimeThrow(n);
					return *(_data + n);
				}

				const_reference	at(size_type n) const {
					if (_size == 0 || n > _size - 1)
						_runtimeThrow(n);
					return *(_data + n);
				}

				reference	front(void) {
					return *_data;
				}

				const_reference	front(void) const {
					return *_data;
				}

				reference	back(void) {
					return *(_data + _size - 1);
				}

				const_reference	back(void) const {
					return *(_data + _size - 1);
				}

				// Modifier functions.
				template <class InputIterator>
					void	assign(InputIterator first, InputIterator last,
							typename ft::enable_if<ft::isIterator<InputIterator>::value, InputIterator>::type* = 0) {
						size_type		new_size = last - first;
						pointer			new_data;

						if (first >= last)
							return ;
						if (new_size > _capacity) {
							new_data = _a.allocate(sizeof(T) * new_size);
							for (size_type i = 0; first != last; first++, i++) {
								if (i < _size)
									_a.destroy(_data + i);
								_a.construct(new_data + i, *first);
							}
							_a.deallocate(_data, _capacity);
							_capacity = new_size;
							_data = new_data;
						} else {
							for (size_type i = 0; first != last; first++, i++) {
								if (i < _size)
									_a.destroy(_data + i);
								_a.construct(_data + i, *first);
							}
							for (size_type i = new_size - 1; i < _size; i++)
								_a.destroy(_data + i);
						}
						_size = new_size;
					}

				void		assign(size_type n, const value_type& val) {
					pointer			new_data;

					if (n > _capacity) {
						new_data = _a.allocate(sizeof(T) * n);
						for (size_type i = 0; i < n; i++) {
							if (i < _size)
								_a.destroy(_data + i);
							_a.construct(new_data + i, val);
						}
						_a.deallocate(_data, _capacity);
						_capacity = n;
						_data = new_data;
					} else {
						for (size_type i = 0; i < _size; i++) {
							if (i < n) {
								_a.destroy(_data + i);
								_a.construct(_data + i, val);
							}
							else
								_a.destroy(_data + i);
						}
						for (size_type i = _size; i < _size + n; i++)
							_a.construct(_data + i, val);
					}
					_size = n;
				}

				void		push_back(T val) {
					if (_size == _capacity) {
						this->reserve(_capacity * 2);
					}
					_a.construct(_data + _size, val);
					_size += 1;
				}

				void		pop_back(void) {
					if (_size == 0) { return ; }
					_a.destroy(_data + _size - 1);
					_size -= 1;
				}

				iterator	insert(iterator position, const value_type& val) {
					pointer		new_data;
					size_type	target = position - this->begin();
					size_type	new_cap = _capacity * 2;

					if (_size == _capacity) {	
						new_data = _a.allocate(sizeof(T) * new_cap);
						_size += 1;
						for (size_type i = 0; i < target; i++)	// Copy up to target pos
							_a.construct(new_data + i, *(_data + i));
						_a.construct(new_data + target, val);	// Insert new val
						for (size_type i = target + 1; i < _size; i++)	// Copy from target pos to end
							_a.construct(new_data + i, *(_data + i - 1));
						for (size_type i = 0; i < _size - 1; i++)	// Destroy prev vals
							_a.destroy(_data + i);
						_a.deallocate(_data, _capacity);
						_capacity = new_cap;
						_data = new_data;
					} else {
						_size += 1;
						for (size_type i = _size - 1; i > target; i--) {
							if (i != _size - 1)
								_a.destroy(_data + i);
							_a.construct(_data + i, *(_data + i - 1));
						}
						_a.destroy(_data + target);
						_a.construct(_data + target, val);
					}
					return iterator(_data + target);
				}

				void	insert(iterator position, size_type n, const value_type& val) {
					pointer		new_data;
					size_type	target = position - this->begin();
					// size_type	new_cap = std::max(_capacity * 2, _size + n);
					size_type	new_cap = _size + n;

					if (_size + n >= _capacity) {	
						new_data = _a.allocate(sizeof(T) * new_cap);
						_size += n;
						for (size_type i = 0; i < target; i++) {	// Copy up to target
							_a.construct(new_data + i, *(_data + i));
							_a.destroy(_data + i);
						}
						for (size_type i = target; i < target + n; i++)	// Construct from val in range
							_a.construct(new_data + i, val);
						for (size_type i = target + n; i < _size; i++) {	// Copy from past target + n
							_a.construct(new_data + i, *(_data + i - n));
							_a.destroy(_data + i - n);
						}
						_a.deallocate(_data, _capacity);
						_capacity = new_cap;
						_data = new_data;
					} else {
						_size += n;
						for (size_type i = _size - 1; i >= target + n; i--)
							_a.construct(_data + i, *(_data + i - n));
						for (size_type i = target; i < target + n; i++) {
							if (i < _size - n - 1)
								_a.destroy(_data + i);
							_a.construct(_data + i, val);
						}
					}
				}

				template <class InputIterator>
					void insert (iterator position, InputIterator first, InputIterator last,
							typename ft::enable_if<ft::isIterator<InputIterator>::value, InputIterator>::type* = 0) {
						pointer		new_data;
						size_type	target = position - this->begin();
						size_type	n = last - first;
						size_type	new_cap = std::max(_capacity * 2, _size + n);
						// size_type	new_cap = _size + n;

						if (_size + n >= _capacity) {
							new_data = _a.allocate(sizeof(T) * new_cap);
							_size += n;
							for (size_type i = 0; i < target; i++) {
								_a.construct(new_data + i, *(_data + i));
								_a.destroy(_data + i);
							}
							for (size_type i = target; i < target + n; i++, first++)
								_a.construct(new_data + i, *first);
							for (size_type i = target + n; i < _size; i++) {
								_a.construct(new_data + i, *(_data + i - n));
								_a.destroy(_data + i - n);
							}
							_a.deallocate(_data, _capacity);
							_capacity = new_cap;
							_data = new_data;
						} else {
							_size += n;
							for (size_type i = _size - 1; i >= target + n; i--)
								_a.construct(_data + i, *(_data + i - n));
							for (size_type i = target; i < target + n; i++, first++) {
								if (i < _size - n - 1)
									_a.destroy(_data + i);
								_a.construct(_data + i, *first);
							}
						}
					}

				iterator	erase(iterator position) {
					size_type	target = position - this->begin();

					_size -= 1;
					for (size_type i = target; i < _size; i++) {
						_a.destroy(_data + i);
						_a.construct(_data + i, *(_data + i + 1));
					}
					_a.destroy(_data + _size);
					return position;
				}

				iterator	erase(iterator first, iterator last) {
					size_type	n = last - first;
					size_type	target = first - this->begin();

					_size -= n;
					for (size_type i = target; i < target + n; i++) {
						_a.destroy(_data + i);
						_a.construct(_data + i, *(_data + i + n));
					}
					for (size_type i = target + n; i < _size; i++) {
						_a.destroy(_data + i);
						_a.construct(_data + i, *(_data + i + n));
					}
					for (size_type i = _size; i < _size + n; i++)
						_a.destroy(_data + i);
					return first;
				}

				void		swap(vector& x) {
					std::swap(_data, x._data);
					std::swap(_size, x._size);
					std::swap(_capacity, x._capacity);
				}

				void		clear(void) {
					for (size_type i = 0; i < _size; i++)
						_a.destroy(_data + i);
					_size = 0;
				}

			private:
				pointer			_data;
				size_type		_size;
				size_type		_capacity;
				allocator_type	_a;

				void		_runtimeThrow(size_type n) {
					std::stringstream	stream;
					std::string			msg;

					stream << "ft::vector::_rangeCheck: _n (which is ";
					stream << n;
					stream << ") >= this->size() (which is ";
					stream << _size;
					stream << ")";
					msg = stream.str();
					throw std::runtime_error(msg);
				}
		};

	template <class T, class Alloc>
		void	swap(vector<T,Alloc>& x, vector<T,Alloc>& y) {
			x.swap(y);
		}

	template <class T, class Alloc>
		bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
			if (lhs.size() != rhs.size())
				return false;
			return std::equal(lhs.begin(), lhs.end(), rhs.begin());
		}

	template <class T, class Alloc>
		bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
			return !(lhs == rhs);
		}

	template <class T, class Alloc>
		bool operator< (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
			return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
		}

	template <class T, class Alloc>
		bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
			return !(rhs < lhs);
		}

	template <class T, class Alloc>
		bool operator> (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
			return rhs < lhs;
		}

	template <class T, class Alloc>
		bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
			return !(lhs < rhs);
		}
}

#endif
