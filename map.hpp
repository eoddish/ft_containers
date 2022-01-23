/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <eoddish@student.21-school.ru      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 00:31:01 by eoddish           #+#    #+#             */
/*   Updated: 2022/01/23 01:07:55 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include "utilities.hpp"
# include <iterator>
# include <unistd.h>
# include <cmath>
# include <algorithm>

namespace ft {

		template <class T>
		struct s_node {

			T * content;
			struct s_node *left;	
			struct s_node *right;
			struct s_node *parent;
			
//			int rob;
		} ;

 template <class Category, class T, class Distance = ptrdiff_t,
        class Pointer = const T*, class Reference = const T&>
        struct m_const_iterator : std::iterator<Category, T> {

        public:

        typedef T         value_type;
        typedef Distance  difference_type;
        typedef Pointer   pointer;
        typedef Reference reference;
        typedef Category  iterator_category;

		typedef s_node<value_type>  t_node;

        m_const_iterator() : p(0), node(0), root(0) {}
        m_const_iterator( T* x, t_node *nd, t_node *rt ) : p( x ), node(nd), root( rt ) {}
        m_const_iterator(const m_const_iterator& mit) : p (mit.p), node(mit.node), root( mit.root)  {}
		virtual ~m_const_iterator() {}
        m_const_iterator & operator=( m_const_iterator const & other ) {

            if( this != &other ) {
                p = other.p;
				node = other.node;
				root = other.root;
            }

        return *this;
        }

		m_const_iterator& operator++() {

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
        m_const_iterator operator++(int) {m_const_iterator tmp(*this); operator++(); return tmp;}
       m_const_iterator& operator--()  {

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

       m_const_iterator operator--(int) {m_const_iterator tmp(*this); operator--(); return tmp;}

       virtual  bool operator==(const m_const_iterator& rhs) const {return p==rhs.p;}
       virtual  bool operator!=(const m_const_iterator& rhs) const {return p!=rhs.p;}
       virtual  bool operator<(const m_const_iterator& rhs) const {return p < rhs.p;}
       virtual  bool operator<=(const m_const_iterator& rhs) const {return p <= rhs.p;}
       virtual  bool operator>(const m_const_iterator& rhs) const {return p > rhs.p;}
       virtual  bool operator>=(const m_const_iterator& rhs) const {return p >= rhs.p;}
        const T& operator*() const {return *(p);}
        const T* operator->() const {return p;}
		
		protected:



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

		protected:

		T* p;

		public:

		t_node *node;
		protected:

		t_node *root;
    };

 template <class Category, class T, class Distance = ptrdiff_t,
        class Pointer = T*, class Reference = T&>
        struct m_iterator : m_const_iterator< Category, T > {

        public:

        typedef T         value_type;
        typedef Distance  difference_type;
        typedef Pointer   pointer;
        typedef Reference reference;
        typedef Category  iterator_category;
		typedef m_const_iterator< Category, T > m_const_iterator;

		typedef s_node<value_type>  t_node;

        m_iterator() : m_const_iterator( 0, 0, 0 ) {}
        m_iterator( pointer x, t_node *nd, t_node *rt ) : m_const_iterator( x, nd, rt ) {}
        m_iterator(const m_iterator& mit) : m_const_iterator( mit.p, mit.node, mit.root)  {}
		virtual ~m_iterator() {}
        m_iterator & operator=( m_iterator const & other ) {

            if( this != &other ) {
                this->p = other.p;
				this->node = other.node;
				this->root = other.root;
            }

        return *this;
        }

		m_iterator& operator++() {

			if ( !this->node ) {
				
				this->node = this->front( this->root ); 
				this->p = this->node->content; 
				return *this;
			}
			this->node = this->inc( this->node );
			if ( this->node )
				this->p = this->node->content;
			else {

				this->p = NULL;	
				}
					
			return *this;
		}
        m_iterator operator++(int) {m_iterator tmp(*this); operator++(); return tmp;}
        m_iterator& operator--()  {

			if ( !this->node ) {
				
				this->node = this->back( this->root ); 
				this->p = this->node->content; 
				return *this;
			}
			this->node = this->dec( this->node );
			if ( this->node )
				this->p = this->node->content;
			else
				this->p = NULL;	
					
			return *this;
    	}

        m_iterator operator--(int) {m_iterator tmp(*this); operator--(); return tmp;}

    //    bool operator==(const m_iterator& rhs) const {return this->p==rhs.p;}
    //    bool operator!=(const m_iterator& rhs) const {return this->p!=rhs.p;}
    //    bool operator<(const m_iterator& rhs) const {return this->p < rhs.p;}
    //    bool operator<=(const m_iterator& rhs) const {return this->p <= rhs.p;}
    //    bool operator>(const m_iterator& rhs) const {return this->p > rhs.p;}
    //    bool operator>=(const m_iterator& rhs) const {return this->p >= rhs.p;}
        reference operator*() const {return *(this->p);}
        pointer operator->() const {return this->p;}
		
		private:


//
//		t_node *inc( t_node * &x) {
//
//			if ( x->right != NULL )
//				return front( x->right );
//			
//			t_node *y = x->parent;
//
//			while( y != NULL && x == y->right ) {
//
//				x = y;
//				y = y->parent;
//			}
//
//			return y;
//
//		}
//
//
//		t_node *dec( t_node * &x) {
//
//			if ( x->left != NULL )
//				return back( x->left );
//			
//			t_node *y = x->parent;
//
//			while( y != NULL && x == y->left ) {
//
//				x = y;
//				y = y->parent;
//			}
//
//			return y;
//
//		}
//
//		t_node *  back( t_node *tmp ) {
//
//			while ( tmp && tmp->right )
//				tmp = tmp->right;
//
//			return tmp;
//		}
//
//		t_node *  front( t_node *tmp ) {
//
//			while ( tmp && tmp->left )
//				tmp = tmp->left;
//
//			return tmp;
//		}
//
    };

	template < class Key, class T, class Compare = std::less<Key>,
		class Alloc = std::allocator<ft::pair<const Key,T> > >
	class map {

		public:
	
		typedef Key key_type;
		typedef T mapped_type;	
		typedef ft::pair<const key_type,mapped_type> value_type;
		typedef Compare key_compare; 

		class value_compare {
			friend class map;
			protected:
			Compare comp;
			value_compare (Compare c) : comp(c) {}  
			public:
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;
			bool operator() (const value_type& x, const value_type& y) const {
				return comp(x.first, y.first);
			}
		};

		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef ft::m_iterator<std::random_access_iterator_tag, value_type> iterator;
		typedef ft::m_const_iterator<std::random_access_iterator_tag, value_type> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef typename iterator_traits<iterator>::difference_type difference_type;
		typedef size_t size_type;
		

		typedef  s_node<value_type> t_node;
	
		explicit map (const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()) : 
			_alloc( alloc ), _comp( comp ), _vcomp( value_compare( _comp ) ), _size( 0 ), _bst( 0 ) {
	
		}
	
		template <class InputIterator>
		map (InputIterator first, InputIterator last,
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()) :
			_alloc( alloc ), _comp( comp ), _vcomp( value_compare( _comp ) ),
			_size ( 0 ), _bst( 0 ) {
	
			insert( first, last );

			
		}
	
		map (const map& x) :
			_alloc( x.get_allocator() ), _comp( x.key_comp() ), _vcomp( x.value_comp() ),
			_size( 0 ), _bst( 0 ) {
	
			*this = x;
		}
	
		~map() {

			clear();
		}

		map& operator= (const map& x) {

			clear();
			insert( x.begin(), x.end() );
			_size = x.size();

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

		bool empty() const {

			return !size();
		}

		size_type size() const {

			return this->_size;
		}

		size_type max_size() const {
/*
			std::cout << "1. " << sizeof( t_node ) << std::endl;
			std::cout << "2. " << sizeof( value_type ) << std::endl;
			std::cout << "3. " << sizeof( pointer ) << std::endl;
			std::cout << "4. " << sizeof( Key ) << std::endl;
			std::cout << "5. " << sizeof( T ) << std::endl;


//			return (  _t_node_alloc.max_size() + _alloc.max_size() )/ 2;
*/
			return (std::powl(2, 64 ) - 1 ) / ( sizeof(t_node) +  sizeof( value_type ) )   ;


		}
		mapped_type& operator[] (const key_type& k) {

			return ( *( ( this->insert(ft::make_pair(k,mapped_type() ) ) ).first ) ).second;	
		}






		ft::pair<iterator,bool> insert (const value_type& val) {

			t_node *tmp = NULL;
			return ft_search( this->_bst, val, tmp );
		}


		iterator insert (iterator position, const value_type& val) {

			t_node *tmp = NULL;
			iterator temp = position;
			if ( _size == 0 || position == end() )
				return ft_search( this->_bst, val, tmp ).first;
			
			if ( !_vcomp( *position, val ) && ( !_vcomp( val, *position ) ) )
				return position;
			else if ( _vcomp( *position, val ) && ( _vcomp( val, *(++temp) ) ) ) 
				return ft_search( position.node, val, tmp ).first; 
			else
				return ft_search( this->_bst, val, tmp ).first;
			
			}

		template <class InputIterator>
  		void insert (InputIterator first, InputIterator last) {

			for ( InputIterator it = first; it != last; ++it ) {
			
				insert( *it );
			}
		}

		void erase (iterator position) {

			ft_delete ( _bst, position.node );

			_alloc.destroy( _alloc.address( *position ) );
			_alloc.deallocate( _alloc.address( *position ), 1 ); 
			_t_node_alloc.destroy( position.node );
			_t_node_alloc.deallocate( position.node, 1 );
			
			_size--;
		}

		size_type erase (const key_type& k) {

			iterator it = find( k );
			if ( it != end() ) {
				erase( it );
				return 1;
			}	
			return 0;
		}
     
	 	void erase (iterator first, iterator last) {

			for( ; first != last;  ) {

				iterator tmp = first;	
				++first;
				erase( tmp );
				}	
		}

		void swap (map& x) {

			t_node *tmp_bst = x._bst;
			size_type tmp_size = x._size;
			x._bst = this->_bst;
			x._size = this->_size;
			this->_bst = tmp_bst;
			this->_size = tmp_size;
		}
	
		void clear() {

			ft_clean( _bst );	
			_size = 0;
			_bst = NULL;
		}

		key_compare key_comp() const {
			
			return _comp;
		}

		value_compare value_comp() const {

			return _vcomp;  
		}

		iterator find (const key_type& k) {

			t_node *tmp = _tree_search( _bst, k );

			if ( tmp )
				return iterator( tmp->content, tmp, _bst );
			else
				return end();
		}

		const_iterator find (const key_type& k) const {

			t_node *tmp = _tree_search( _bst, k );

			if ( tmp )
				return iterator( tmp->content, tmp, _bst );
			else
				return end();
		}

		size_type count (const key_type& k) const {

			const_iterator it = find( k );
            if ( it != end() ) {
                return 1;
            }
            return 0;
		}

		iterator lower_bound (const key_type& k) {

			iterator it = begin();

			for ( ; it != end(); ++it ) {
				if ( !key_comp()( it->first, k ) )
					return it;
			}
			return it;
		}

		const_iterator lower_bound (const key_type& k) const {

			const_iterator it = begin();
			for ( ; it != end(); ++it ) {

				if ( !key_comp()( it->first, k ) )
					return it;
			}
			return it;
		}	

		iterator upper_bound (const key_type& k) {

			iterator it = begin();
			for ( ; it != end(); ++it ) {

				if ( key_comp()( k, it->first ) )
					return it;
			}

			return it;
		}

		const_iterator upper_bound (const key_type& k) const {

			const_iterator it = begin();
			for ( ; it != end(); ++it ) {

				if ( key_comp()( k, it->first ) )
					return it;
			}
			return it;

		}

		pair<const_iterator,const_iterator> equal_range (const key_type& k) const {

			return ft::make_pair( lower_bound( k ), upper_bound( k ) );
		}

		pair<iterator,iterator>             equal_range (const key_type& k) {

			return ft::make_pair( lower_bound( k ), upper_bound( k ) );
		}


		allocator_type get_allocator() const {
	
			return _alloc; 
		}

		protected:
	
		allocator_type _alloc;
		key_compare _comp;
		value_compare _vcomp;
		size_type _size;
		typedef typename allocator_type::template rebind<t_node>::other t_node_allocator_type;
		t_node_allocator_type _t_node_alloc;

		ft::pair <iterator, bool> ft_search( t_node * &tmp, const value_type& val, t_node *&parent ) {


			if ( !tmp ) {

				tmp = _t_node_alloc.allocate( 1 );
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

		void ft_delete( t_node *&tree, t_node *&z ) {

			if ( z->left == NULL ) {

				ft_shift( tree, z, z->right );}
			else if ( z->right == NULL ) {
				ft_shift( tree, z, z->left );}
			else {

				iterator it = find( z->content->first );
				t_node *y = (++it).node;
				if ( y->parent->content != z->content ) {
					ft_shift( tree, y, y->right );
					y->right = z->right;
					y->right->parent = y;
				}
				ft_shift( tree, z, y );
				y->left = z->left;
				y->left->parent = y;
			}
		}

		void ft_shift( t_node *&tree, t_node *&u, t_node *&v ) {

			if ( u->parent == NULL ) {

				tree = v;}
			else if ( u == u->parent->left ) {

				u->parent->left = v;}
			else {

				u->parent->right = v; }
			if ( v != NULL ) {
				v->parent = u->parent; }
		}

		t_node *_tree_search( t_node *x, const key_type &key ) const {

			if ( x == NULL || ( !_comp( key, x->content->first ) && !_comp( x->content->first, key ) ) )
				return x;
			if ( _comp( key, x->content->first ) )
				return _tree_search( x->left, key );
			else
				return _tree_search( x->right, key );
		}

		void ft_clean( t_node *& x ) {

			if ( x != NULL ) {

				ft_clean( x->left );
				ft_clean( x->right );
				
			_alloc.destroy( x->content );
			_alloc.deallocate( x->content, 1 ); 
			_t_node_alloc.destroy( x );
			_t_node_alloc.deallocate( x, 1 );
			
			}
		}

		public:

		t_node *_bst;

	};

	template <class Key, class T, class Compare, class Alloc>
		void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y) {
		
		x.swap( y );
	}

	template <class Key, class T, class Compare, class Alloc>
		bool operator== ( const map<Key,T,Compare,Alloc>& lhs,
			const map<Key,T,Compare,Alloc>& rhs ) {

		if ( lhs.size() != rhs.size() )
				return false;
		return ft::equal( lhs.begin(), lhs.end(), rhs.begin() );
	}

	template <class Key, class T, class Compare, class Alloc>
		bool operator!= ( const map<Key,T,Compare,Alloc>& lhs,
			const map<Key,T,Compare,Alloc>& rhs ) { return !( lhs == rhs ); }

	template <class Key, class T, class Compare, class Alloc>
		bool operator<  ( const map<Key,T,Compare,Alloc>& lhs,
			const map<Key,T,Compare,Alloc>& rhs ) {
		
		return ft::lexicographical_compare( lhs.begin(), lhs.end(), rhs.begin(), rhs.end() );
	}

	template <class Key, class T, class Compare, class Alloc>
		bool operator<= ( const map<Key,T,Compare,Alloc>& lhs,
			const map<Key,T,Compare,Alloc>& rhs ) { return !( rhs < lhs ); };

	template <class Key, class T, class Compare, class Alloc>
		bool operator>  ( const map<Key,T,Compare,Alloc>& lhs,
			const map<Key,T,Compare,Alloc>& rhs ) { return rhs < lhs; };
	template <class Key, class T, class Compare, class Alloc>
		bool operator>= ( const map<Key,T,Compare,Alloc>& lhs,
			const map<Key,T,Compare,Alloc>& rhs ) { return !( lhs < rhs ); };
}

#endif
