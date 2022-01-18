/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 10:23:56 by eoddish           #+#    #+#             */
/*   Updated: 2022/01/18 18:02:20 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include "utilities.hpp"
#include <iterator>
#include <cmath>

namespace ft {


	template <class Category, class T, class Distance = ptrdiff_t,
			 class Pointer = T*, class Reference = T&>
				 class base_iterator : std::iterator<Category, T> {


   
		public:

		typedef T         value_type;
	    typedef Distance  difference_type;
	    typedef Pointer   pointer;
	    typedef Reference reference;
	    typedef Category  iterator_category;



		base_iterator() :p(0) {}
		base_iterator( T* x ) :p(x) {}
		base_iterator( base_iterator const &mit) : p(mit.m()) {}
		~base_iterator(){}
		virtual base_iterator & operator=( base_iterator const & other ) {
			
			if( this != &other ) {
				p = other.m();	
        	}

        return *this;
		}

		pointer m( void ) const { return p; };	

		friend	bool operator==(const base_iterator&lhs, const base_iterator& rhs) {return lhs.m() == rhs.m();}
		friend	bool operator!=(const base_iterator&lhs, const base_iterator& rhs) {return lhs.m() !=rhs.m();}
		friend	bool operator<(const base_iterator&lhs, const base_iterator& rhs) {return lhs.m() < rhs.m();}
		friend	bool operator<=(const base_iterator&lhs, const base_iterator& rhs) {return lhs.m() <= rhs.m();}
		friend	bool operator>(const base_iterator&lhs, const base_iterator& rhs) {return lhs.m() > rhs.m();}
		friend	bool operator>=(const base_iterator&lhs, const base_iterator& rhs) {return lhs.m() >= rhs.m();}


		protected:

		pointer p;
	};

	template <class Category, class T, class Distance = ptrdiff_t,
		class Pointer = const T*, class Reference = const T&>
  		class const_iterator : public ft::base_iterator<Category, T> {
    
		public:

		typedef T         value_type;
	    typedef Distance  difference_type;
	    typedef Pointer   pointer;
	    typedef Reference reference;
	    typedef Category  iterator_category;
		typedef ft::base_iterator< Category, T > base_iterator;


		const_iterator() : base_iterator() {}
		const_iterator( T* x ) : base_iterator(x){}
		const_iterator( base_iterator const &mit) : base_iterator( mit.m() ) {}
		~const_iterator() {}
		const_iterator & operator=( base_iterator const & other ) {
			
			if( this != &other ) {
				this->p = other.m();	
        	}

        return *this;
		}
		pointer m( void ) const { return this->p; };	
		reference operator*() const {return *this->p;}

		const_iterator operator+( difference_type n ) const { return const_iterator( this->base_iterator::m() + n ) ;}
		friend const_iterator operator+( difference_type n, const_iterator it ) { return const_iterator( it.base_iterator::m() + n ); }
		const_iterator& operator++() { ++this->p; return *this;}
		const_iterator operator++(int) {const_iterator tmp(*this); operator++(); return tmp;}
		const_iterator &operator+=( difference_type n ) { this->p += n; return *this; }

		const_iterator operator-( difference_type n ) const { return const_iterator( this->p - n ) ;}
		friend difference_type operator-( const const_iterator & lhs, const const_iterator & rhs ) { return lhs.m() - rhs.m(); }
		const_iterator& operator--() { --this->p; return *this;}
		const_iterator operator--(int) {const_iterator tmp(*this); operator--(); return tmp;}
		const_iterator &operator-=( difference_type n ) { this->p -= n; return *this; }

		pointer operator->() const {return this->p;}

		reference operator[] ( difference_type n ) { return *(this->p + n); }


	};

	template <class Category, class T, class Distance = ptrdiff_t,
		class Pointer = T*, class Reference = T&>
  		class iterator : public ft::base_iterator< Category, T > {
    
		public:

		typedef T         value_type;
	    typedef Distance  difference_type;
	    typedef Pointer   pointer;
	    typedef Reference reference;
	    typedef Category  iterator_category;
		typedef ft::base_iterator< Category, T > base_iterator;


		iterator() : base_iterator() {}
		iterator(T* x) : base_iterator(x) {}
		iterator(const iterator& mit) : base_iterator(mit.m()) {}
		~iterator() {}
		iterator & operator=( iterator const & other ) {
			
			if( this != &other ) {
				this->p = other.m();	
        	}

        return *this;
		}

		pointer m( void ) const { return this->p; };	
		reference operator*() const {return *this->p;}

		iterator operator+( difference_type n ) const { return iterator( this->m() + n ) ;}
		friend iterator operator+( difference_type n, iterator it ) { return iterator( it.m() + n ); }
		iterator& operator++() { ++this->p; return *this;}
		iterator operator++(int) {iterator tmp(*this); operator++(); return tmp;}
		iterator &operator+=( difference_type n ) { this->p += n; return *this; }

		iterator operator-( difference_type n ) const { return iterator( this->p - n ) ;}
		friend difference_type operator-( const iterator & lhs, const iterator & rhs ) { return lhs.m() - rhs.m(); }
		iterator& operator--() { --this->p; return *this;}
		iterator operator--(int) {iterator tmp(*this); operator--(); return tmp;}
		iterator &operator-=( difference_type n ) { this->p -= n; return *this; }

		pointer operator->() const {return this->p;}

		reference operator[] ( difference_type n ) { return *(this->p + n); }

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
		typedef ft::const_iterator<std::random_access_iterator_tag, value_type> const_iterator;
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
				_alloc.construct( it.m(), val );	
			}
			return;
		}

		template <class InputIterator>	
			vector( InputIterator first, typename enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last,
                 const allocator_type& alloc = allocator_type() ) :  _p(0) , _alloc( alloc ) {


			int cnt = std::distance( first, last );
			this->_capacity = cnt;
			this->_size = cnt;
			this->_p = this->_alloc.allocate( this->capacity() );
			for ( iterator it = this->begin() ; it != this->end(); ++it) {
				_alloc.construct( &(*it), *first );	
				++first;
			}
			return;
		}
	

		vector( const vector & other ) :  _capacity(0), _size(0), _p(0) , _alloc( other.get_allocator() ) {
		
		        *this = other;
		
		        return;
		}
		
		~vector( void ) {
	
			for ( iterator it = this->begin() ; it != this->end(); ++it)
				_alloc.destroy( &(*it) );
			
			_alloc.deallocate( _p, capacity() );

			return;
		}
		
		vector & operator=( vector const & other ) {
		
			if( this != &other ) {
				if ( this->capacity() )
					this->_alloc.deallocate( this->_p, this->capacity() );
				this->_capacity = other.capacity();
				this->_size = other.size();
				this->_p = this->_alloc.allocate( other.capacity() );
				const_iterator first = other.begin();
				for ( iterator it = this->begin() ; it != this->end(); ++it) {
					_alloc.construct( &(*it), *first );	
					++first;
				}
			}
		
		        return *this;
		}

		iterator begin( void ) {
			
			return iterator( this->_p ) ;
		}

		const_iterator begin( void ) const {
			
			return const_iterator( this->_p ) ;
		}

		iterator end( void ) {
			
			return iterator(  this->_p + this->size() ) ;
		}

		const_iterator end( void ) const {
			
			return const_iterator(  this->_p + this->size() ) ;
		}
		
		reverse_iterator rbegin() {
			
			return reverse_iterator( this->_p + this->size() );
		}
		
		const_reverse_iterator rbegin() const {

			return const_reverse_iterator( this->_p + this->size() );
		}
		
		reverse_iterator rend() {

			return reverse_iterator( this->_p );
		}

		const_reverse_iterator rend() const {

			return const_reverse_iterator( this->_p );
		}

		size_t size( void ) const {

			return this->_size;	
		}

		size_type max_size() const {

			return _alloc.max_size();
		}

		void resize (size_type n, value_type val = value_type()) {

			this->reserve( n );
			
			if ( n > size() ) {
				
				for ( iterator it = end(); it != begin() + n; ++it )
					_alloc.construct( &(*it), val );
			}
			else if ( n < this->size() ) {

				for ( iterator it = begin() + n ; it != this->end(); ++it) {
					_alloc.destroy( &(*it) );
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
				
				T* p = this->_alloc.allocate( n );
				std::copy( begin(), end(), p );
					if ( this->capacity() )
				this->_alloc.deallocate( this->_p, this->capacity() );
				this->_p = p;
				this->_capacity = n;
			}
		}

		reference operator[] (size_type n) {

			return *( this->_p + n );
		}
		
		const_reference operator[] (size_type n) const {

			return *( this->_p + n );
		}
		
		reference at (size_type n) {

			if ( n >= this->size() ) {
				throw std::out_of_range( "vector::_M_range_check" );
			}
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

				for ( iterator it = begin(); it != end(); ++it )
					_alloc.destroy( &(*it) );

				size_type n = std::distance( first, last );;
				reserve( n );
				this->_size = n;

				for ( iterator it = begin(); it != end(); ++it ) {

					_alloc.construct( &(*it), *first );
					++first;
				}
		}

		void assign (size_type n, const value_type& val) {

				clear();	
				reserve( n );
				this->_size = n;

				for ( iterator it = this->begin(); it != this->end(); ++it )
					_alloc.construct( &(*it), val);
		}

		void push_back( T const & val ) {
		
			if ( this->capacity() == 0 ) {

				this->_capacity = 1;
				this->_p = this->_alloc.allocate( this->capacity() );
			}
			else if ( this->size() == this->capacity() ) {

				this->reserve( this->capacity() * 2 );
			}
			_alloc.construct( this->_p + this->size(), val); 
			this->_size++;

		}

		void pop_back() {

			this->_size--;
			_alloc.destroy( _p + size() );
		}

		iterator insert (iterator position, const value_type& val) {

			difference_type nbr = position - this->begin();
			if ( this->size() == this->capacity() )
				this->reserve( this->capacity() + 1 );
			this->_size++;
			position = this->begin() + nbr;
			std::copy_backward( position , this->end() - 1, this->end() );

			_alloc.construct( &(*position), val );

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
			for ( iterator it = position; it != position + n; ++it )
				_alloc.construct( &(*it) , val );
		}

		template <class InputIterator>
    		void insert (iterator position, InputIterator first, typename enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last ) {

			difference_type offset = position - begin();
			size_type n = 0;
			for ( InputIterator it = first; it != last; ++it )
				n++;
			reserve( size() + n );
			iterator oldend = end();
			position = begin() + offset;
			_size += n;
			std::copy_backward( position, oldend, end() );
			for ( iterator it = position; it != position + n; ++it )
			{
				_alloc.construct( &(*it), *first );
				++first;
			}
		}

		iterator erase (iterator position) {

			_alloc.destroy( &(*position) );
			std::copy( position + 1, this->end(), position );
			this->_size--;

			return position;
		}
		
		iterator erase (iterator first, iterator last) {

			int n = last - first;
			for ( iterator it = first; it != last; ++it )	
				_alloc.destroy( &(*it) );

			std::copy( last, this->end(), first );
			this->_size -= n;

			return first;
		}

		void swap (vector& x) {

			T *tmp_p = x._p;
			size_type tmp_capacity = x.capacity();
			size_type tmp_size = x.size();

			x._capacity = this->capacity();;
			x._size =  this->size() ;
			x._p = this->_p;

			this->_capacity = tmp_capacity;
			this->_size =  tmp_size; 
			this->_p = tmp_p;;

		}

		void clear() {
	

			for ( iterator it = this->begin(); it != this->end(); ++it )
				_alloc.destroy( &(*it) );

			this->_size = 0;
		}


		allocator_type get_allocator() const {

			return this->_alloc;
		}

		T* data() { return &(*_p) ; }

		const T* data() const { return &(*_p) ; }



		protected:

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
