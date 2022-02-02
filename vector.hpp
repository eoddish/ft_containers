/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 10:23:56 by eoddish           #+#    #+#             */
/*   Updated: 2022/02/02 22:32:02 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include "utilities.hpp"
#include <iterator>
#include <cmath>
#include <unistd.h>

namespace ft {


	template <class Category, class T, class Distance = ptrdiff_t,
		class Pointer = const T*, class Reference = const T&>
  		class const_iterator : public std::iterator<Category, T> {
    
		public:

		typedef T         value_type;
	    typedef Distance  difference_type;
	    typedef Pointer   pointer;
	    typedef Reference reference;
	    typedef pointer	iterator_type;
	    typedef Category  iterator_category;


		const_iterator() : p( 0 ) {}
		const_iterator( T* x ) : p(x){}
		const_iterator( const_iterator const &mit)  : p( mit.p ) {}
		virtual ~const_iterator() {}
		const_iterator & operator=( const_iterator const & other ) {
			
			if( this != &other ) {
				this->p = other.p;	
        	}

        return *this;
		}
		reference operator*() const {return *(this->p);}

		const_iterator operator+( difference_type n ) const { return const_iterator( this->p + n ) ;}
		friend const_iterator operator+( difference_type n, const_iterator it ) { return const_iterator( it.p + n ); }
		const_iterator& operator++() { ++this->p; return *this;}
		const_iterator operator++(int) {const_iterator tmp(*this); operator++(); return tmp;}
		const_iterator &operator+=( difference_type n ) { this->p += n; return *this; }

		const_iterator operator-( difference_type n ) const { return const_iterator( this->p - n ) ;}
		friend difference_type operator-( const const_iterator & lhs, const const_iterator & rhs ) { return lhs.p - rhs.p; }
		const_iterator& operator--() { --this->p; return *this;}
		const_iterator operator--(int) {const_iterator tmp(*this); operator--(); return tmp;}
		const_iterator &operator-=( difference_type n ) { this->p -= n; return *this; }

		pointer operator->() const {return this->p;}

		reference operator[] ( difference_type n ) { return *(this->p + n); }

		friend	bool operator==(const const_iterator&lhs, const const_iterator& rhs) {return lhs.p == rhs.p;}
		friend	bool operator!=(const const_iterator&lhs, const const_iterator& rhs) {return lhs.p !=rhs.p;}
		friend	bool operator<(const const_iterator&lhs, const const_iterator& rhs) {return lhs.p < rhs.p;}
		friend	bool operator<=(const const_iterator&lhs, const const_iterator& rhs) {return lhs.p <= rhs.p;}
		friend	bool operator>(const const_iterator&lhs, const const_iterator& rhs) {return lhs.p > rhs.p;}
		friend	bool operator>=(const const_iterator&lhs, const const_iterator& rhs) {return lhs.p >= rhs.p;}



		protected:

		T* p;
	};

	template <class Category, class T, class Distance = ptrdiff_t,
		class Pointer = T*, class Reference = T&>
  		class iterator : public ft::const_iterator< Category, T > {
    
		public:

		typedef T         value_type;
	    typedef Distance  difference_type;
	    typedef Pointer   pointer;
	    typedef Reference reference;
	    typedef Category  iterator_category;

	    typedef pointer iterator_type;
		typedef ft::const_iterator< Category, T > const_iterator;


		iterator() : const_iterator() {}
		iterator(T* x) : const_iterator(x) {}
		iterator(const iterator& mit) : const_iterator(mit.p) {}
		virtual ~iterator() {}
		iterator & operator=( iterator const & other ) {
			
			if( this != &other ) {
				this->p = other.p;	
        	}

        return *this;
		}

		reference operator*() const {return *(this->p);}

		iterator operator+( difference_type n ) const { return iterator( this->p + n ) ;}
		friend iterator operator+( difference_type n, iterator it ) { return iterator( it.p + n ); }
		iterator& operator++() { ++this->p; return *this;}
		iterator operator++(int) {iterator tmp(*this); operator++(); return tmp;}
		iterator &operator+=( difference_type n ) { this->p += n; return *this; }

		iterator operator-( difference_type n ) const { return iterator( this->p - n ) ;}
		friend difference_type operator-( const iterator & lhs, const iterator & rhs ) { return lhs.p - rhs.p; }
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
			for ( iterator it = begin(); it != end(); ++it )
				_alloc.construct( _alloc.address( *it ), val );
		
			return;
		}

		template <class InputIterator>	
			vector( InputIterator first, typename enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last,
                 const allocator_type& alloc = allocator_type() ) :  _p(0) , _alloc( alloc ) {


			int cnt = std::distance( first, last );
			this->_capacity = cnt;
			this->_size = cnt;
			this->_p = this->_alloc.allocate( this->capacity() );
			for ( iterator it = begin(); first != last; ++it )
				_alloc.construct( _alloc.address( *it ), *first++ );

			return;
		}
	

		vector( const vector & other ) :  _capacity(0), _size(0), _p(0) , _alloc( other.get_allocator() ) {
		
		        *this = other;
		
		        return;
		}
		
		~vector( void ) {
	
			clear();
			if ( capacity() )
				_alloc.deallocate( _p, capacity() );

			return;
		}
		
		vector & operator=( vector const & other ) {
		
			if( this != &other ) {
				if ( this->capacity() ) {
					clear();	
					this->_alloc.deallocate( this->_p, this->capacity() );
				}
				this->_capacity = other.capacity();
				this->_size = other.size();
				if ( other.capacity() ) {
					this->_p = this->_alloc.allocate( other.capacity() );
					const_iterator first = other.begin();
					for ( iterator it = this->begin() ; it != this->end(); ++it) {
						_alloc.construct( _alloc.address(*it), *first );	
						++first;
					}
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

			if ( n > capacity() ) {
				if ( !capacity() )
					reserve( std::max( n, (size_type)1 ) );
				reserve( std::max( n, capacity() * 2 ) );
			}
			
			if ( n > size() ) {
				
				for ( iterator it = end(); it != begin() + n; ++it )
					_alloc.construct( _alloc.address( *it ), val );
			}
			else if ( n < this->size() ) {

				for ( iterator it = begin() + n ; it != this->end(); ++it ) {
					_alloc.destroy( _alloc.address(*it) );
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
			
				throw std::length_error( "vector" );
			}

			if ( n > this->capacity() ) {

				
				T* p = this->_alloc.allocate( n );
				size_type i = 0;
				for ( iterator it = begin(); it != end(); ++it ) {

					_alloc.construct( p + i, *it );
					++i;
				}
				if ( this->capacity() )
				{
					for ( iterator it = this->begin(); it != end(); ++it )
						_alloc.destroy( _alloc.address( *it ) );

					this->_alloc.deallocate( this->_p, this->capacity() );
				}
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

				clear();
				size_type n = std::distance( first, last );
				reserve( n );
				this->_size = n;
				
				for ( iterator it = begin(); first != last; ++it )
					_alloc.construct( _alloc.address( *it ), *first++ );
			
		}

		void assign (size_type n, const value_type& val) {

				clear();	
				reserve( n );
				this->_size = n;

				for ( iterator it = begin(); it != end(); ++it )
					_alloc.construct( _alloc.address( *it ), val );
		}

		void push_back( const value_type & val ) {

			if ( this->capacity() == 0 ) {
				this->reserve( 1 );

			}
			else if ( this->size() == this->capacity() ) {

				this->reserve( this->capacity() * 2 );

			}
			this->_alloc.construct( _alloc.address( *(end() ) ), val); 

			this->_size++;

		}

		void pop_back() {

			this->_size--;
			_alloc.destroy( _p + size() );
		}

		iterator insert (iterator position, const value_type& val) {

			difference_type nbr = std::distance(begin(), position);
			if ( !this->capacity() )
				this->reserve( 1 );
			else if ( this->size() == this->capacity() )
				this->reserve( this->capacity() * 2 );
			this->_size++;
			position = this->begin() + nbr;
			iterator it1 = end() - 1;
			for ( iterator it = end() - 2; it != position - 1; --it ) {

				_alloc.construct( _alloc.address( *it1 ), *it );
				--it1;
			}

			_alloc.construct( _alloc.address(*position), val );

			return position; 
		}

    	void insert (iterator position, size_type n, const value_type& val) {

			difference_type nbr = position - this->begin();
			if ( size() + n > capacity() )
				reserve( std::max( size() + n, capacity() * 2 ) );
			iterator oldend = this->end();
			this->_size += n;
			position = this->begin() + nbr;

			iterator it1 = end() - 1;
			for ( iterator it = oldend - 1; it != position - 1; --it ) {

				_alloc.construct( _alloc.address( *it1 ), *it );
				--it1;
			}

			for ( iterator it = position; it != position + n; ++it )
				_alloc.construct( _alloc.address(*it) , val );
		}

		template <class InputIterator>
    		void insert (iterator position, InputIterator first, typename enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last ) {

			difference_type offset = position - begin();
			size_type n = 0;
			for ( InputIterator it = first; it != last; ++it )
				n++;

			if ( size() + n > capacity() ) {
				pointer check = _alloc.allocate( std::max( size() + n, capacity() * 2 ) );
				position = check + offset;

				iterator it1 = position;
					try {
						
						for ( InputIterator it = first; it != last; ++it ) {

							_alloc.construct( _alloc.address( *it1 ), *it );
							++it1;
						}
					}

					catch( ... ) {

						for ( --it1; it1 != position - 1; --it1 )
							_alloc.destroy( _alloc.address( *it1 ) );
												
						_alloc.deallocate( check, std::max( size() + n, capacity() * 2 ) );
						throw "Error";
					}

				size_t i = 0;
				for ( iterator it = begin(); it != begin() + offset; ++it )
					_alloc.construct( check + i++, *it );
				i = 0;
				for ( iterator it = begin() + offset; it != end(); ++it )
					_alloc.construct( check + offset + n + i++, *it );
				_alloc.deallocate( _p, capacity() );
				_p = check;
				_capacity = std::max( size() + n, capacity() * 2 ); 
				_size += n;

			} else {

			iterator oldend = end();
			position = begin() + offset;

			iterator it1 = end() + n - 1;
			for ( iterator it = oldend - 1; it != position - 1; --it ) {

				_alloc.construct( _alloc.address( *it1 ), *it );
				--it1;
			}

			for ( iterator it = position; it != position + n; ++it ) {
				_alloc.construct( _alloc.address(*it), *first );
				++first;
			}
			_size += n;
			}
		}

		iterator erase (iterator position) {

			_alloc.destroy( _alloc.address(*position) );
			iterator it1 = position;
			for ( iterator it = position + 1; it != end(); ++it ) {

				_alloc.construct( _alloc.address( *it1 ), *it );
				++it1;
			}
			this->_size--;

			return position;
		}
		
		iterator erase (iterator first, iterator last) {

			int n = last - first;
			for ( iterator it = first; it != last; ++it )	
				_alloc.destroy( &(*it) );

			iterator it1 = first;
			for ( iterator it = last; it != end(); ++it ) {

				_alloc.construct( _alloc.address( *it1 ), *it );
				++it1;
			}
			this->_size -= n;

			return first;
		}

		void swap (vector& x) {

			T *tmp_p = x._p;
			size_type tmp_capacity = x.capacity();
			size_type tmp_size = x.size();

			x._capacity = this->capacity();
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
