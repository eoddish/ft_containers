/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 16:32:47 by eoddish           #+#    #+#             */
/*   Updated: 2021/12/23 00:08:14 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

#include "vector.hpp"
#include <iostream>

namespace ft {

	template <class T, class Container = ft::vector<T> >
	class stack {
			
		public:

		typedef T value_type;
		typedef Container container_type;
		typedef size_t size_type;
		
		explicit stack (const container_type& ctnr = container_type()) : _ctnr( ctnr ) {};

		size_type size() const {
		
			return this->_ctnr.size();
		}

		bool empty() const {

			return this->_ctnr.empty();
		}

		value_type& top() {

			return this->_ctnr.back();
		}

		const value_type& top() const {

			return this->_ctnr.back();
		}

		void push (const value_type& val) {

			return this->_ctnr.push_back( val );
		}
			
		void pop() {

			return this->_ctnr.pop_back();
		}

		friend	bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
	
			return lhs._ctnr == rhs._ctnr;
		}

		friend	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {

			return lhs._ctnr != rhs._ctnr;
		}
	
		friend	bool operator< (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		
			return lhs._ctnr < rhs._ctnr;
		}
	
		friend	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {

			return lhs._ctnr <= rhs._ctnr;
		}
	
		friend	bool operator> (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {

			return lhs._ctnr > rhs._ctnr;
		}
	
		friend	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {

			return lhs._ctnr >= rhs._ctnr;
		}
	
		private:
		
		container_type _ctnr;

	};

}

#endif
