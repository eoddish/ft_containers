/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 10:23:56 by eoddish           #+#    #+#             */
/*   Updated: 2022/01/13 03:29:22 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include "utilities.hpp"

namespace ft {

	template <class Category, class T, class Distance = ptrdiff_t,
		class Pointer = T*, class Reference = T&>
  		struct iterator  {
    
		public:

		typedef T         value_type;
	    typedef Distance  difference_type;
	    typedef Pointer   pointer;
	    typedef Reference reference;
	    typedef Category  iterator_category;



		pointer p;
		iterator() :p(0) {}
		iterator(T* x) :p(x) {}
		iterator(const iterator& mit) : p(mit.p) {}
		iterator & operator=( iterator const & other ) {
			
			if( this != &other ) {
				this->p = other.p;	
        	}

        return *this;
		}

		iterator& operator++() { ++p; return *this;}
		iterator operator++(int) {iterator tmp(*this); operator++(); return tmp;}
		iterator& operator--() { --p; return *this;}
		iterator operator--(int) {iterator tmp(*this); operator--(); return tmp;}
		bool operator==(const iterator& rhs) const {return p==rhs.p;}
		bool operator!=(const iterator& rhs) const {return p!=rhs.p;}
		bool operator<(const iterator& rhs) const {return p < rhs.p;}
		bool operator<=(const iterator& rhs) const {return p <= rhs.p;}
		bool operator>(const iterator& rhs) const {return p > rhs.p;}
		bool operator>=(const iterator& rhs) const {return p >= rhs.p;}
		reference operator*() {return *p;}
		iterator operator+( const int & nbr ) { return iterator( this->p + nbr ) ;}
		iterator operator+=( const int & nbr ) { return iterator( this->p + nbr ) ;}
		iterator operator-( const int & nbr ) { return iterator( this->p - nbr ) ;}
		iterator operator-=( const int & nbr ) { return iterator( this->p - nbr ) ;}
		difference_type operator-( const iterator & other ) { return this->p - other.p;}

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
		typedef typename iterator_traits<iterator>::difference_type difference_type;
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
			vector( InputIterator first, typename enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last,
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
	

		vector( const vector & other ) :  _capacity(0), _size(0), _p(0) , _alloc( other.get_allocator() ) {
		
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

			this->reserve( n );
		
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

			if ( n > this->max_size() ) {
			
				throw std::length_error( "vector::_M_fill_insert" );
			}

			if ( n > this->capacity() ) {
				
				this->_capacity = n;
				T* p = this->_alloc.allocate( this->capacity() );
				std::copy( this->_p, this->_p + this->size(), p );
					if ( this->capacity() )
				this->_alloc.deallocate( this->_p, this->capacity() );
				this->_p = p;
			}
		}

		reference operator[] (size_type n) {

			return *( this->_p + n );
		}
		
		const_reference operator[] (size_type n) const {

			return *( this->_p + n );
		}
		
		reference at (size_type n) {

			if ( n >= this->size() )
				throw std::out_of_range( "vector::_M_range_check" );
			return (*this)[n];	
		}

		const_reference at (size_type n) const {

			if ( n >= this->size() )
				throw std::out_of_range( "vector::_M_range_check" );
			return (*this)[n];	
		}

		reference front( void ) {
			
			return *( this->_p );
		}
		
		const_reference front() const {

			return *( this->_p );
		}

		reference back( void ) {
			
			return *( this->_p + this->size() - 1 ) ;
		}

		const_reference back() const {

			return *( this->_p + this->size() - 1 ) ;
		}

		template <class InputIterator>
			void assign (InputIterator first, typename enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last ) {

				size_type n = 0;
				for ( InputIterator it = first; it != last; ++it )
					++n;
				if ( n > this->capacity() ) {

					if ( this->capacity() )
						this->_alloc.deallocate( this->_p, this->capacity() );
					this->_capacity = n;
					this->_p = this->_alloc.allocate( this->capacity() );
				}

				this->_size = n;
				std::copy( first, last, this->_p );

		}

		void assign (size_type n, const value_type& val) {

				if ( n > this->capacity() ) {

					if ( this->capacity() )
						this->_alloc.deallocate( this->_p, this->capacity() );
					this->_capacity = n;
					this->_p = this->_alloc.allocate( this->capacity() );
				}

				this->_size = n;
				for ( iterator it = this->begin(); it != this->end(); ++it )
					*it = val;
		}

		void push_back( T const & val ) {
		
			if ( this->capacity() == 0 ) {

				this->_p = this->_alloc.allocate( this->capacity() );
				this->_capacity = 1;
			}
			else if ( this->size() == this->capacity() ) {

				this->reserve( this->capacity() * 2 );
			}
			*( this->_p + this->size() ) = val; 
			this->_size++;

		}

		void pop_back() {

			this->_size--;
		}

		iterator insert (iterator position, const value_type& val) {

			difference_type nbr = position - this->begin();
			if ( this->size() == this->capacity() )
				this->reserve( this->capacity() + 1 );
			this->_size++;
			position = this->begin() + nbr;
			std::copy_backward( position , this->end() - 1, this->end() );

			*position = val;

			return position; 
		}

    	void insert (iterator position, size_type n, const value_type& val) {

			difference_type nbr = position - this->begin();
			if ( this->size() + n > this->capacity() )
				this->reserve( this->size()  + n );
			iterator oldend = this->end();
			this->_size += n;
			position = this->begin() + nbr;
			std::copy_backward( position , oldend, this->end() );
			std::fill( position, position + n, val );
		}

		template <class InputIterator>
    		void insert (iterator position, InputIterator first, InputIterator last) {

			difference_type nbr = position - this->begin();
			size_t n = std::distance( first,last );
			if ( this->size() + n > this->capacity() )
				this->reserve( this->size() + n );
			iterator oldend = this->end();
			this->_size += n;
			position = this->begin() + nbr;
			std::copy_backward( position , oldend, this->end() );
			std::copy( first, last, position );
		}

		iterator erase (iterator position) {

			std::copy( position + 1, this->end(), position );
			this->_size--;

			return position;
		}
		
		iterator erase (iterator first, iterator last) {

			int n = last - first;
			std::copy( last, this->end(), first );
			this->_size -= n;

			return first;
		}

		void swap (vector& x) {

			vector tmp = x;
			x = *this;
			*this = tmp;

		}

		void clear() {
	
			this->_size = 0;
		}


		allocator_type get_allocator() const {

			return this->_alloc;
		}

	



		private:

		size_t _capacity;
		size_t _size;
		T * _p;
		Alloc _alloc; 	
	
	};

	template <class T, class Alloc>
		bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {

			if ( lhs.size() != rhs.size() )
				return false;
			return ft::equal( lhs.begin(), lhs.end(), rhs.begin() );
		}
	
	template <class T, class Alloc>
		bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return !( lhs == rhs ); }
	
	template <class T, class Alloc>
		bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {

			return ft::lexicographical_compare( lhs.begin(), lhs.end(), rhs.begin(), rhs.end() );
		}
	
	template <class T, class Alloc>
		bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return !( rhs < lhs ); };
	
	template <class T, class Alloc>
		bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return rhs < lhs; };
	
	template <class T, class Alloc>
		bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return !( lhs < rhs ); };

	template <class T, class Alloc>
		void swap (vector<T,Alloc>& x, vector<T,Alloc>& y) {

			x.swap( y );
		}
	
}
#endif
