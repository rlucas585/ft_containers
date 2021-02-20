/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Example.hpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/20 12:45:33 by rlucas        #+#    #+#                 */
/*   Updated: 2021/02/20 13:19:08 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXAMPLE_HPP
# define EXAMPLE_HPP 

# include <iostream>
# include <string>

class Example {
	public:
		Example(void);
		Example(Example const &src);
		~Example(void);
		Example		&operator=(Example const &rhs);

		static Example		createWithNameAndValue(const char *name, int val);

		std::string const&	getName(void) const;
		int	const&			getVal(void) const;

		void				addToName(int n);
		void				subName(int n);
		void				multName(int n);

		bool				operator==(Example const& other) const;
		bool				operator!=(Example const& other) const;
		bool				operator<(Example const& other) const;
		bool				operator<=(Example const& other) const;
		bool				operator>(Example const& other) const;
		bool				operator>=(Example const& other) const;

	private:
		std::string	_name;
		int			_val;

		Example(const char *name, int val);
};

std::ostream		&operator<<(std::ostream &o, Example const &i);

#endif

