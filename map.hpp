/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <eoddish@student.21-school.ru      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 00:31:01 by eoddish           #+#    #+#             */
/*   Updated: 2021/12/31 02:11:12 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include "pair.hpp"
# include "make_pair.hpp"
# include <iostream>
# include <unistd.h>

namespace ft {

		template <class T>
		struct s_node {

			T * content;
			struct s_node *left;	
			struct s_node *right;
			struct s_node *parent;
			
		} ;

 template <class Category, class T, class Distance = ptrdiff_t,
        class Pointer = T*, class Reference = T&>
        struct m_iterator  {



		private: 


        public:

        typedef T         value_type;
        typedef Distance  difference_type;
        typedef Pointer   pointer;
        typedef Reference reference;
        typedef Category  iterator_category;

		typedef s_node<value_type>  t_node;

        m_iterator() : p(0), node(0), root(0) {}
        m_iterator( pointer x, t_node *nd, t_node *rt ) : p( x ), node(nd), root( rt ) {}
        m_iterator(const m_iterator& mit) : p (mit.p), node(mit.node), root( mit.root)  {}
        m_iterator & operator=( m_iterator const & other ) {

            if( this != &other ) {
                p = other.p;
				node = other.node;
				root = other.root;
            }

        return *this;
        }

		m_iterator& operator++() {

			if ( !node ) {
				
				node = front( root ); 
				p = node->content; 
				return *this;
			}
			node = inc( node );
			if ( node )
				p = node->content;
			else
				p = NULL;	
					
			return *this;
		}
        m_iterator operator++(int) {m_iterator tmp(*this); operator++(); return tmp;}
        m_iterator& operator--()  {

			if ( !node ) {
				
				node = back( root ); 
				p = node->content; 
				return *this;
			}
			node = dec( node );
			if ( node )
				p = node->content;
			else
				p = NULL;	
					
			return *this;
    	}

        m_iterator operator--(int) {m_iterator tmp(*this); operator--(); return tmp;}
        bool operator==(const m_iterator& rhs) const {return p==rhs.p;}
        bool operator!=(const m_iterator& rhs) const {return p!=rhs.p;}
        bool operator<(const m_iterator& rhs) const {return p < rhs.p;}
        bool operator<=(const m_iterator& rhs) const {return p <= rhs.p;}
        bool operator>(const m_iterator& rhs) const {return p > rhs.p;}
        bool operator>=(const m_iterator& rhs) const {return p >= rhs.p;}
        reference operator*() {return *(p);}
        pointer operator->() {return p;}
		
		private:



		t_node *inc( t_node * &x) {

			if ( x->right != NULL )
				return front( x->right );
			
			t_node *y = x->parent;

			while( y != NULL && x == y->right ) {

				x = y;
				y = y->parent;
			}

			return y;

		}


		t_node *dec( t_node * &x) {

			if ( x->left != NULL )
				return back( x->left );
			
			t_node *y = x->parent;

			while( y != NULL && x == y->left ) {

				x = y;
				y = y->parent;
			}

			return y;

		}

		t_node *  back( t_node *tmp ) {

			while ( tmp && tmp->right )
				tmp = tmp->right;

			return tmp;
		}

		t_node *  front( t_node *tmp ) {

			while ( tmp && tmp->left )
				tmp = tmp->left;

			return tmp;
		}

		public:

		pointer p;
		t_node *node;
		t_node *root;


    };

	template < class Key, class T, class Compare = std::less<Key>,
		class Alloc = std::allocator<ft::pair<const Key,T> > >
	class map {

		public:
	
		typedef Key key_type;
		typedef T mapped_type;	
		typedef ft::pair<const key_type,mapped_type> value_type;
		typedef Compare key_compare; 
		//typedef value_compare;	
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef ft::m_iterator<std::random_access_iterator_tag, value_type> iterator;
		typedef const ft::m_iterator<std::random_access_iterator_tag, value_type> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef typename iterator_traits<iterator>::difference_type difference_type;
		typedef size_t size_type;
		

		typedef  s_node<value_type> t_node;
	
		explicit map (const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()) : 
			_alloc( alloc ), _comp( comp ), _size( 0 ), _bst( 0 ) {
	
		}
	
		template <class InputIterator>
		map (InputIterator first, InputIterator last,
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()) :
			_alloc( alloc ), _comp( comp ), 
			_size ( 0 ), _bst( 0 ) {
	
			insert( first, last );

			
		}
	
		map (const map& x) :
			_alloc( x.get_allocator() ), _comp( x.key_comp() ),
			_size( 0 ), _bst( 0 ) {
	
			*this = x;
		}

		map& operator= (const map& x) {

			iterator xit = x.begin();
			for( iterator it = (*this).begin(); it != (*this).end(); ++it ) {
			
				this->_alloc.construct( &(*it), *xit );
				++xit;
			}
			
			insert( xit, x.end() );
			
			return *this;
		}


		iterator begin() {

			if ( !_bst )
				return iterator( 0, 0, 0 );
			t_node *tmp = _bst;
			while ( tmp->left )
				tmp = tmp->left;

			return iterator( tmp->content, tmp, _bst );
		}
		
		const_iterator begin() const {

			if ( !_bst )
				return iterator( 0, 0, 0 );
			t_node *tmp = _bst;
			while ( tmp->left )
				tmp = tmp->left;
			return iterator( tmp->content, tmp, _bst );
		}

		iterator end() {

			return iterator(  0,  0, _bst );
		}

		const_iterator end() const {

			return iterator( 0, 0, _bst  );
		}

		reverse_iterator rbegin() {

			return reverse_iterator( iterator( end() ) );
		}

		const_reverse_iterator rbegin() const {

			return reverse_iterator( iterator( end() ) );
		}

		reverse_iterator rend() {

			return reverse_iterator( begin() );
		}

		const_reverse_iterator rend() const {

			return reverse_iterator( begin() );
		}


		size_type size() const {

			return this->_size;
		}
	
		mapped_type& operator[] (const key_type& k) {

			return ( *( ( this->insert(ft::make_pair(k,mapped_type() ) ) ).first ) ).second;	
		}






		ft::pair<iterator,bool> insert (const value_type& val) {

			return this->ft_search( this->_bst, val, NULL );
		}


//		iterator insert (iterator position, const value_type& val) {
//
//			
//		}
//
		template <class InputIterator>
  		void insert (InputIterator first, InputIterator last) {

			for ( InputIterator it = first; it != last; ++it ) {
			
				insert( *it );
			}

		}
	

		key_compare key_comp() const {
			
			return _comp;
		}


		allocator_type get_allocator() const {
	
			return _alloc; 
		}

		private:
	
		allocator_type _alloc;
		key_compare _comp;
		size_type _size;
		//typedef struct s_node {

		//	pointer content;
		//	struct s_node *left;	
		//	struct s_node *right;
		//	
		//} t_node;


		ft::pair <iterator, bool> ft_search( t_node * &tmp, const value_type& val, t_node *parent ) {


			if ( !tmp ) {
	
				std::allocator< t_node > t_node_alloc;
				tmp = t_node_alloc.allocate( 1 );
				tmp->content = this->_alloc.allocate( 1 );
				this->_alloc.construct( tmp->content, val );
				tmp->left = 0;
				tmp->right = 0;
				tmp->parent = parent;
				this->_size++;

				return ft::make_pair<iterator, bool> ( iterator( tmp->content, tmp, _bst ) , true);
			}

			if ( ( !_comp( val.first, tmp->content->first) )
				&& ( !_comp( tmp->content->first, val.first ) ) )
				return ft::make_pair<iterator, bool> ( iterator( tmp->content, tmp, _bst ), false);
			else if ( _comp( val.first, tmp->content->first) )
				return	ft_search( tmp->left, val, tmp  );
				
			return	ft_search( tmp->right, val, tmp );

			}
			
		

		public:

		t_node *_bst;

	};
}

#endif
