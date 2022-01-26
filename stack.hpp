/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 16:32:47 by eoddish           #+#    #+#             */
/*   Updated: 2022/01/23 21:56:08 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

#include "vector.hpp"
#include <iostream>
#include "unistd.h"

namespace ft {

	template <class T, class Container = ft::vector<T> >
	class stack {
			
		public:

		typedef T value_type;
		typedef Container container_type;
		typedef size_t size_type;
		
		explicit stack (const container_type& ctnr = container_type()) : c( ctnr ) {};

		~stack() {

		}
 

		size_type size() const {
		
			return this->c.size();
		}

		bool empty() const {

			return this->c.empty();
		}

		value_type& top() {

			return this->c.back();
		}

		const value_type& top() const {

			return this->c.back();
		}

		void push (const value_type& val) {

			c.push_back( val );
			
		}
			
		void pop() {

			this->c.pop_back();
		}

		friend	bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
	
			return lhs.c == rhs.c;
		}

		friend	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {

			return lhs.c != rhs.c;
		}
	
		friend	bool operator< (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		
			return lhs.c < rhs.c;
		}
	
		friend	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {

			return lhs.c <= rhs.c;
		}
	
		friend	bool operator> (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {

			return lhs.c > rhs.c;
		}
	
		friend	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {

			return lhs.c >= rhs.c;
		}
	
		protected:
		
		container_type c;

	};

}

#endif
