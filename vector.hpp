/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 10:23:56 by eoddish           #+#    #+#             */
/*   Updated: 2021/12/09 01:26:45 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <memory>
# include <iterator>

namespace ft {

	template< class T >
	class vector {


		
		public:
	

		class iterator : public std::iterator<std::random_access_iterator_tag, T>
{
				int* p;
				public:
				iterator(T* x) :p(x) {}
				iterator(const iterator& mit) : p(mit.p) {}
				iterator& operator++() { ++p; return *this;}
				iterator operator++(int) {iterator tmp(*this); operator++(); return tmp;}
				bool operator==(const iterator& rhs) const {return p==rhs.p;}
				bool operator!=(const iterator& rhs) const {return p!=rhs.p;}
				int& operator*() {return *p;}
};			


		vector( void ) : _capacity(0), _size(0), _p(0) {
				
			
			return;
		}

		vector( size_t n, const T & val ) : _capacity(n), _size(n), _p(0) {
			
			std::allocator< T > alloc; 	
			this->_p = alloc.allocate( this->capacity() );
			for ( iterator it = this->begin() ; it != this->end(); ++it) {
				*it = val;	
			}
			return;
		}
		
		vector( vector const & other ) {
		
		        *this = other;
		
		        return;
		}
		
		~vector( void ) {
		
		        return;
		}
		
		vector & operator=( vector const & other ) {
		
		        if( this != &other ) {
		
		        }
		
		        return *this;
		}


		void push_back( T const & val ) {
		

			if ( this->size() == this->capacity() ) {
			std::allocator< T > alloc; 	
				this->_capacity++;
				T* p = alloc.allocate( this->capacity() );
				std::copy( this->_p, this->_p + this->size(), p );
				alloc.deallocate( this->_p, this->capacity() );
				this->_p = p;
			}
			*( this->_p + this->size() ) = val; 
			this->_size++;


		}


		size_t size( void ) {

			return this->_size;	
		}

		size_t capacity( void ) {
	
			return this->_capacity;	
		}

		bool empty( void ) const {

			if ( this->size() )
				return false;
			return true;		
		}

		T & back( void ) {
			
			return *( this->_p + this->size() - 1 ) ;
		}

		T & front( void ) {
			
			return *( this->_p );
		}
	


		iterator begin( void ) {
			
			return iterator( this->_p ) ;
		}

		iterator end( void ) {
			
			return iterator(  this->_p + this->size() ) ;
		}

		private:

		size_t _capacity;
		size_t _size;
		T * _p;

	};

}
#endif
