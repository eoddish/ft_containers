/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <eoddish@student.21-school.ru      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 00:31:01 by eoddish           #+#    #+#             */
/*   Updated: 2022/02/03 19:58:21 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include "utilities.hpp"
# include <iterator>
# include <cmath>
# include <algorithm>

namespace ft {

	template <class T>
		struct s_node {

			T * content;
			struct s_node *left;	
			struct s_node *right;
			struct s_node *parent;

			short bf;
		} ;

	template <class Category, class T, class Distance = ptrdiff_t, class Pointer = const T*, class Reference = const T&> struct m_const_iterator : public std::iterator<Category, T> {

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

			m_const_iterator operator--(int) {  m_const_iterator tmp(*this); operator--(); return tmp;}

			virtual  bool operator==(const m_const_iterator& rhs) const {return p==rhs.p;}
			virtual  bool operator!=(const m_const_iterator& rhs) const {return p!=rhs.p;}

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
			t_node *node;
			t_node *root;

	};

	template <class Category, class T, class Distance = ptrdiff_t,
			 class Pointer = T*, class Reference = T&>
				 struct m_iterator : public m_const_iterator< Category, T > {

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

								 if ( this->node )
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

						 m_iterator operator--(int) {

							 m_iterator tmp(*this);

							 operator--();

							 return tmp;}

						 reference operator*() const {return *(this->p);}
						 pointer operator->() const {return this->p;}



				 };

	template < class Key, class T, class Compare = std::less<Key>,
			 class Alloc = std::allocator<ft::pair<const Key,T> > >
				 class map {

					 public:

						 typedef Key key_type;
						 typedef T mapped_type;	
						 typedef ft::pair<const key_type,mapped_type> value_type;
						 typedef Compare key_compare; 

						 class value_compare : public std::binary_function<value_type,value_type,bool>{
							 friend class map;
							 protected:
							 Compare comp;
							 value_compare (Compare c) : comp(c) {}  
							 public:
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
							 return const_iterator( tmp->content, tmp, _bst );
						 }

						 iterator end() {

							 return iterator(  0,  0, _bst );
						 }

						 const_iterator end() const {

							 return const_iterator( 0, 0, _bst  );
						 }

						 reverse_iterator rbegin() {

							 return reverse_iterator(  end()  );
						 }

						 const_reverse_iterator rbegin() const {

							 return const_reverse_iterator(  end()  );
						 }

						 reverse_iterator rend() {

							 return reverse_iterator( begin() );
						 }

						 const_reverse_iterator rend() const {

							 return const_reverse_iterator( begin() );
						 }

						 bool empty() const {

							 return !size();
						 }

						 size_type size() const {

							 return this->_size;
						 }

						 size_type max_size() const {

							 return ( std::numeric_limits<size_type>::max()  ) / ( sizeof(t_node) +  sizeof( value_type ) ) ;
						 }

						 mapped_type& operator[] (const key_type& k) {

							 return ( *( ( this->insert(ft::make_pair(k,mapped_type() ) ) ).first ) ).second;	
						 }


						 T& at( const Key& key ) {

							 if ( find( key ) == end() )
								 throw std::out_of_range( "vector::_M_range_check" );

							 return ( *( ( this->insert(ft::make_pair(key,mapped_type() ) ) ).first ) ).second;	

						 }


						 const T& at( const Key& key ) const {

							 if ( find( key ) == end() )
								 throw std::out_of_range( "vector::_M_range_check" );

							 return ( *( ( this->insert(ft::make_pair(key,mapped_type() ) ) ).first ) ).second;	

						 }



						 ft::pair<iterator,bool> insert (const value_type& val) {

							 t_node *tmp = NULL;

							 ft::pair<iterator, bool> res = ft_search( this->_bst, val, tmp );
							 return res;
						 }


						 iterator insert (iterator position, const value_type& val) {
							 t_node *tmp = NULL;
							 iterator temp = position;
							 if ( _size == 0 || position == end() ) {

								 iterator res = ft_search( this->_bst, val, tmp ).first;

								 return res;
							 } else if ( !_vcomp( *position, val ) && ( !_vcomp( val, *position) ) ) {

								 return position;
							 } else if ( _vcomp( *position, val ) && ( _vcomp( val, *(++temp) ) ) ) {

							t_node *node = _tree_search( _bst, position->first );	
								 iterator res =  ft_search( node, val, tmp ).first; 

								 return res;
							 } else {

								 iterator res = ft_search( this->_bst, val, tmp ).first;

								 return res;
							 }
						 }

						 template <class InputIterator>
							 void insert (InputIterator first, InputIterator last) {

								 for ( InputIterator it = first; it != last; ++it ) {
									 insert( *it );
								 }
							 }

						 void erase (iterator position) {

							t_node *node = _tree_search( _bst, position->first );
							 ft_delete ( _bst, node );
							 _alloc.destroy( _alloc.address( *position ) );
							 _alloc.deallocate( _alloc.address( *position ), 1 ); 
							 _t_node_alloc.destroy( node );
							 _t_node_alloc.deallocate( node, 1 );

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

							 for ( ; it != end() && _comp( it->first, k ); ++it ) {
								 ;
							 }
							 return it;
						 }

						 const_iterator lower_bound (const key_type& k) const {

							 const_iterator it = begin();

							 for ( ; it != end() && _comp( it->first, k ); ++it ) {
								 ;
							 }
							 return it;
						 }	

						 iterator upper_bound (const key_type& k) {

							 iterator it = begin();
							 for ( ; it != end() && !_comp( k, it->first ); ++it ) {
								 ;
							 }

							 return it;
						 }

						 const_iterator upper_bound (const key_type& k) const {

							 const_iterator it = begin();

							 for ( ; it != end() && !_comp( k, it->first ); ++it ) {
								 ;
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
								 tmp->bf = 0;
								 tmp->parent = parent;
								 this->_size++;

								ft::pair<iterator, bool> res = 	ft::make_pair<iterator, bool> ( iterator( tmp->content, tmp, _bst ) , true);

								ft_rebalance( tmp );
								 return res;
							 }

							 if ( ( !_comp( val.first, tmp->content->first) )
									 && ( !_comp( tmp->content->first, val.first ) ) )
								 return ft::make_pair<iterator, bool> ( iterator( tmp->content, tmp, _bst ), false);
							 else if ( _comp( val.first, tmp->content->first) )
								 return	ft_search( tmp->left, val, tmp  );

							 return	ft_search( tmp->right, val, tmp );

						 } 

						 void ft_rebalance( t_node *Z) {
							 t_node *G = NULL;
							 t_node *N = NULL;

							 for ( t_node *X = Z->parent; X != NULL; X = Z->parent ) {


								 if ( Z == X->right ) {


									 if ( X->bf > 0 ) {




										 G = X->parent;
										 if ( Z->bf < 0 )
											 N = rotate_RL( X, Z );
										 else
											 N = rotate_L( X, Z );

									 } else {



										 if ( X->bf < 0 ) {

											 X->bf = 0;
											 break;
										 }

										 X->bf = 1;
										 Z = X;
										 continue;
									 }


								 } else {

									 if ( X->bf < 0 ) {

										 G = X->parent;
										 if ( Z->bf > 0 )
											 N = rotate_LR( X, Z );
										 else
											 N = rotate_R( X, Z );

									 } else {

										 if ( X->bf > 0 ) {

											 X->bf = 0;
											 break;
										 }
										 X->bf = -1;
										 Z = X;
										 continue;
									 }

								 }

								 N->parent = G;


								 if ( G != NULL ) {


									 if ( X == G->left )
										 G->left = N;
									 else
										 G->right = N;

								 } else {
									 _bst = N;


								 }
								 break;
							 }
						 }

						 void ft_retrace( t_node *N ) {
							 t_node *G = NULL;
							 t_node *Z = NULL;
							 int b = 0;

							 for ( t_node *X = N->parent; X != NULL; X = G ) {


								 G = X->parent;
								 if ( N == X->left ) {

									 if ( X->bf > 0 ) {

										 Z = X->right;	
										 b = Z->bf;
										 if ( b < 0 )
											 N = rotate_RL( X, Z );
										 else
											 N = rotate_L( X, Z );
									 } else {

										 if ( X->bf == 0 ) {

											 X->bf = 1;
											 break;
										 }
										 N = X;
										 N->bf = 0;
										 continue;
									 }
								 } else {

									 if ( X->bf < 0 ) {

										 Z = X->left;


										 b = Z->bf;

										 if ( b > 0 )
											 N = rotate_LR( X, Z );
										 else
											 N = rotate_R( X, Z );

									 } else {

										 if ( X->bf == 0 ) {

											 X->bf = -1;
											 break;
										 }
										 N = X;
										 N->bf = 0;
										 continue;
									 }
								 }

								 N->parent = G;
								 if ( G != NULL ) {

									 if ( X == G->left )
										 G->left = N;
									 else
										 G->right = N;
								 } else
									 _bst = N;
								 if ( b == 0 )
									 break;
							 }

						 }

						 t_node *rotate_L( t_node *X, t_node *Z ) {

							 t_node *T1 = Z->left;
							 X->right = T1;
							 if ( T1 != NULL )
								 T1->parent = X;
							 Z->left = X;
							 X->parent = Z;

							 if ( Z->bf == 0 ) {

								 X->bf = 1;
								 Z->bf = -1;

							 } else {

								 X->bf = 0;
								 Z->bf = 0;
							 }

							 return Z;
						 }

						 t_node *rotate_R( t_node *X, t_node *Z ) {

							 t_node *T1 = Z->right;
							 X->left = T1;
							 if ( T1 != NULL )
								 T1->parent = X;
							 Z->right = X;
							 X->parent = Z;

							 if ( Z->bf == 0 ) {

								 X->bf = -1;
								 Z->bf = 1;

							 } else {

								 X->bf = 0;
								 Z->bf = 0;
							 }

							 return Z;
						 }

						 t_node *rotate_RL( t_node *X, t_node *Z ) {

							 t_node *Y = Z->left;
							 t_node *T3 = Y->right;
							 Z->left = T3;

							 if ( T3 != NULL )
								 T3->parent= Z;
							 Y->right = Z;
							 Z->parent = Y;
							 t_node *T2 = Y->left;
							 X->right = T2;
							 if ( T2 != NULL )
								 T2->parent = X;
							 Y->left = X;
							 X->parent = Y;

							 if ( Y->bf == 0 ) {

								 X->bf = 0;
								 Z->bf = 0;
							 } else
								 if ( Y->bf > 0 ) {

									 X->bf = -1;
									 Z->bf = 0;
								 } else {

									 X->bf = 0;
									 Z->bf = 1;
								 }
							 Y->bf = 0;
							 return Y;
						 }


						 t_node *rotate_LR( t_node *X, t_node *Z ) {

							 t_node *Y = Z->right;
							 t_node *T3 = Y->left;
							 Z->right = T3;

							 if ( T3 != NULL )
								 T3->parent= Z;
							 Y->left = Z;
							 Z->parent = Y;
							 t_node *T2 = Y->right;
							 X->left = T2;
							 if ( T2 != NULL )
								 T2->parent = X;
							 Y->right = X;
							 X->parent = Y;

							 if ( Y->bf == 0 ) {

								 X->bf = 0;
								 Z->bf = 0;
							 } else
								 if ( Y->bf < 0 ) {

									 X->bf = -1;
									 Z->bf = 0;
								 } else {

									 X->bf = 0;
									 Z->bf = 1;
								 }
							 Y->bf = 0;
							 return Y;
						 }

						 void ft_delete( t_node *&tree, t_node *&z ) {

							 if (!z)
								 return;

							 if ( z->left == NULL ) {

								 ft_retrace( z );
								 ft_shift( tree, z, z->right );

							 }
							 else if ( z->right == NULL ) {

								 ft_retrace( z );
								 ft_shift( tree, z, z->left );

							 }
							 else {

								 t_node *y = inc( z );
								 t_node *p = y->parent;
								 if ( y->parent != z ) {
									 ft_shift( tree, y, y->right );
									 y->right = z->right;
									 y->right->parent = y;

									 ft_shift( tree, z, y );
									 y->left = z->left;
									 y->left->parent = y;

									 t_node *tmp = p->left;
									 p->left = z;
									 z->parent = p;

									 ft_retrace( z );

									 p->left = tmp;

									 return;
								 }

								 ft_shift( tree, z, y );
								 y->left = z->left;
								 y->left->parent = y;

								 t_node *tmp = y->right;
								 y->right = z;
								 z->parent = y;

								 ft_retrace( z );

								 y->right = tmp;

							 }

						 }
						 int findMax(int a, int b){
							 if(a >= b)
								 return a;
							 else
								 return b;
						 }

						 int findHeight(t_node* root){

							 if(root == NULL)
								 return 0;

							 return findMax(findHeight(root->left), findHeight(root->right)) + 1;
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


						 t_node *  front( t_node *tmp ) {

							 while ( tmp && tmp->left )
								 tmp = tmp->left;

							 return tmp;
						 }

					 protected:

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
