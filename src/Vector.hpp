/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Vector.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <ryanl585codam@gmail.com>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/06 12:52:10 by rlucas        #+#    #+#                 */
/*   Updated: 2021/01/06 12:53:46 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP 

class Vector {

	public:

		Vector(void);
		Vector(Vector const &src);
		~Vector(void);
		Vector		&operator=(Vector const &rhs);

	private:


};

#endif
