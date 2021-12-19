/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 10:23:56 by eoddish           #+#    #+#             */
/*   Updated: 2021/12/20 00:50:46 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <memory>
# include <iterator>
# include <type_traits>
# include <stdexcept>
# include "iterator_traits.hpp"
# include "reverse_iterator.hpp"

namespace ft {

	template <class Category, class T, class Distance = ptrdiff_t,
		class Pointer = T*, class Reference = T&>
  		struct iterator {
    
		public:

		typedef T         value_type;
	    typedef Distance  difference_type;
	    typedef Pointer   pointer;
	    typedef Reference reference;
	    typedef Category  iterator_category;



		int* p;
		iterator(T* x) :p(x) {}
		iterator(const iterator& mit) : p(mit.p) {}
		iterator& operator++() { ++p; return *this;}
		iterator operator++(int) {iterator tmp(*this); operator++(); return tmp;}
		iterator& operator--() { --p; return *this;}
		iterator operator--(int) {iterator tmp(*this); operator--(); return tmp;}
		bool operator==(const iterator& rhs) const {return p==rhs.p;}
		bool operator!=(const iterator& rhs) const {return p!=rhs.p;}
		int& operator*() {return *p;}

	};



	template < class T, class Alloc = std::allocator<T> >
		class vector {

		public:

		typedef T value_type;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef ft::iterator<std::random_access_iterator_tag, value_type> iterator;
		typedef const ft::iterator<std::random_access_iterator_tag, value_type> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;	
		typedef ptrdiff_t difference_type;
		typedef size_t size_type;
			


		explicit vector( const allocator_type& alloc = allocator_type() ) : _capacity(0), _size(0), _p(0), _alloc( alloc ) {
				
			
			return;
		}

		explicit vector( size_type n, const value_type& val = value_type(),
			const allocator_type& alloc = allocator_type() ) : _capacity(n), _size(n), _p(0), _alloc( alloc ) {
			
			
			this->_p = this->_alloc.allocate( this->capacity() );
			for ( iterator it = this->begin() ; it != this->end(); ++it) {
				*it = val;	
			}
			return;
		}

		template <class InputIterator>	
			vector( InputIterator first, InputIterator last,
                 const allocator_type& alloc = allocator_type() ) :  _p(0) , _alloc( alloc ) {
			int cnt = 0;
			for ( iterator it = first; it != last; ++it) {
				 cnt++;	
			}
			this->_capacity = cnt;
			this->_size = cnt;
			this->_p = this->_alloc.allocate( this->capacity() );
			std::copy( first, last, this->_p );
			return;
		}
	

		vector( const vector & other ) :  _capacity(0), _size(0), _p(0) {
		
		        *this = other;
		
		        return;
		}
		
		~vector( void ) {
	
				this->_alloc.destroy( this->_p );

		        return;
		}
		
		vector & operator=( vector const & other ) {
		
			if( this != &other ) {
				if ( this->capacity() )
					this->_alloc.deallocate( this->_p, this->capacity() );
				this->_capacity = other.capacity();
				this->_size = other.size();
				this->_p = this->_alloc.allocate( other.capacity() );
				std::copy( other.begin(), other.end(), this->_p );
		        }
		
		        return *this;
		}

		iterator begin( void ) {
			
			return iterator( this->_p ) ;
		}

		const_iterator begin( void ) const {
			
			return iterator( this->_p ) ;
		}

		iterator end( void ) {
			
			return iterator(  this->_p + this->size() ) ;
		}

		const_iterator end( void ) const {
			
			return iterator(  this->_p + this->size() ) ;
		}
		
		reverse_iterator rbegin() {
			
			return reverse_iterator( this->_p + this->size() );
		}
		
		const_reverse_iterator rbegin() const {

			return reverse_iterator( this->_p + this->size() );
		}
		
		reverse_iterator rend() {

			return reverse_iterator( this->_p );
		}

		const_reverse_iterator rend() const {

			return reverse_iterator( this->_p );
		}

		size_t size( void ) const {

			return this->_size;	
		}

		size_type max_size() const {

			return 1073741823;
		}

		void resize (size_type n, value_type val = value_type()) {

			if ( n > this->capacity() ) {
				
				this->_capacity = n;
				T* p = this->_alloc.allocate( this->capacity() );
				std::copy( this->_p, this->_p + this->size(), p );
					if ( this->capacity() )
				this->_alloc.deallocate( this->_p, this->capacity() );
				this->_p = p;
			}
		
			if ( n > this->size() ) {
				
				for ( iterator it = this->end() ; it != iterator( this->_p + this->size() + n ); ++it) {
				*it = val;
            	}
			}
			else if (n < this->size() ) {

				for ( iterator it = iterator( this->_p + n) ; it != this->end(); ++it) {
               		 *it = val;
           		 }

			}
			this->_size = n;
		}

		size_type capacity() const {
	
			return this->_capacity;	
		}

		bool empty() const {

			if ( this->size() )
				return false;
			return true;		
		}

		void reserve (size_type n) {

			if ( n > this->max_size() )
				throw std::length_error( "vector::_M_fill_insert" );
		
			if ( n > this->capacity() ) {
				
				this->_capacity = n;
				T* p = this->_alloc.allocate( this->capacity() );
				std::copy( this->_p, this->_p + this->size(), p );
					if ( this->capacity() )
				this->_alloc.deallocate( this->_p, this->capacity() );
				this->_p = p;
			}
		}

		void push_back( T const & val ) {
		
			if ( this->capacity() == 0 ) {

				this->_p = this->_alloc.allocate( this->capacity() );
				this->_capacity = 1;
			}
			else if ( this->size() == this->capacity() ) {

				this->_capacity *= 2;
				T* p = this->_alloc.allocate( this->capacity() );
				std::copy( this->_p, this->_p + this->size(), p );
					if ( this->capacity() )
				this->_alloc.deallocate( this->_p, this->capacity() );
				this->_p = p;
			}
			*( this->_p + this->size() ) = val; 
			this->_size++;


		}





		T & back( void ) {
			
			return *( this->_p + this->size() - 1 ) ;
		}

		T & front( void ) {
			
			return *( this->_p );
		}
	
		reference operator[] (size_type n) {

			return *( this->_p + n );
		}
		
		const_reference operator[] (size_type n) const {

			return *( this->_p + n );
		}


		private:

		size_t _capacity;
		size_t _size;
		T * _p;
		Alloc _alloc; 	
	
	};

}
#endif
