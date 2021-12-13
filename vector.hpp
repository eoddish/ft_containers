/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 10:23:56 by eoddish           #+#    #+#             */
/*   Updated: 2021/12/13 03:06:02 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <memory>
# include <iterator>

namespace ft {


	template< class Iterator >
	struct iterator_traits {
		typedef typename Iterator::iterator_category iterator_category;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::difference_type difference_type;
	    typedef typename Iterator::pointer pointer;
	    typedef typename Iterator::reference reference;

		};

	template <class Iterator>
	class reverse_iterator {

		private:

		
		int* p;
	
		public:
	

		typedef Iterator iterator_type;
		
		reverse_iterator( ) :p( 0 ) {}
		reverse_iterator( iterator_type it ) :p( it.p - 1 ) {}
		template <class Iter>
		reverse_iterator (const reverse_iterator<Iter>& rev_it) :p( rev_it.p ){}	
		iterator_type base( void ) const { return iterator_type( this->p + 1 ); };
		reverse_iterator& operator++() { --p; return *this;}
		reverse_iterator operator++(int) {reverse_iterator tmp(*this); operator++(); return tmp;}
		bool operator==(const reverse_iterator& rhs) const {return p==rhs.p;}
		bool operator!=(const reverse_iterator& rhs) const {return p!=rhs.p;}
		int& operator*() {return *p;}
	
		
		typedef typename ft::iterator_traits<Iterator>::iterator_category iterator_category;
		typedef typename ft::iterator_traits<Iterator>::value_type value_type;
		typedef typename ft::iterator_traits<Iterator>::difference_type difference_type;
		typedef typename ft::iterator_traits<Iterator>::pointer pointer;
		typedef typename ft::iterator_traits<Iterator>::reference reference;

	};


	template< class T >
	class vector {
		
		public:

		class iterator {
		
			private:


			public:

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

			typedef  std::random_access_iterator_tag iterator_category;
			typedef  T value_type;
			typedef  ptrdiff_t difference_type;
			typedef  T* pointer;
			typedef  T& reference;
		};			



		vector( void ) : _capacity(0), _size(0), _p(0) {
				
			
			return;
		}

		vector( size_t n, const T & val ) : _capacity(n), _size(n), _p(0) {
			
			
			this->_p = this->_alloc.allocate( this->capacity() );
			for ( iterator it = this->begin() ; it != this->end(); ++it) {
				*it = val;	
			}
			return;
		}
	
		vector( iterator first , iterator last ) :  _p(0) {
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
	

		vector( vector const & other ) :  _capacity(0), _size(0), _p(0) {
		
		        *this = other;
		
		        return;
		}
		
		~vector( void ) {
		
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


		void push_back( T const & val ) {
		

			if ( this->size() == this->capacity() ) {
				this->_capacity++;
				T* p = this->_alloc.allocate( this->capacity() );
				std::copy( this->_p, this->_p + this->size(), p );
					if ( this->capacity() )
				this->_alloc.deallocate( this->_p, this->capacity() );
				this->_p = p;
			}
			*( this->_p + this->size() ) = val; 
			this->_size++;


		}


		size_t size( void ) const {

			return this->_size;	
		}

		size_t capacity( void ) const {
	
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
	


		iterator begin( void ) const {
			
			return iterator( this->_p ) ;
		}

		iterator end( void ) const {
			
			return iterator(  this->_p + this->size() ) ;
		}

		private:

		size_t _capacity;
		size_t _size;
		T * _p;
		std::allocator< T > _alloc; 	
	
	};

}
#endif
