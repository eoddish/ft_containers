/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <eoddish@student.21-school.ru      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 00:31:01 by eoddish           #+#    #+#             */
/*   Updated: 2021/12/26 03:27:19 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include "pair.hpp"
# include "make_pair.hpp"
# include <iostream>
# include <unistd.h>

namespace ft {


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
		typedef ft::iterator<std::random_access_iterator_tag, value_type> iterator;
		typedef const ft::iterator<std::random_access_iterator_tag, value_type> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef typename iterator_traits<iterator>::difference_type difference_type;
		typedef size_t size_type;
		
	
		explicit map (const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()) : 
			_alloc( alloc ), _comp( comp ), _size( 0 ), _bst( 0 ) {
	
		}
	
		template <class InputIterator>
		map (InputIterator first, InputIterator last,
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()) :
			_alloc( alloc ), _comp( comp ), 
			_size ( std::distance( first, last ) ) , _bst( 0 ) {
	
			
		}
	
		map (const map& x) {
	
			*this = x;
		}

		size_type size() const {

			return this->_size;
		}
	
		mapped_type& operator[] (const key_type& k) {

			return ( *( ( this->insert(ft::make_pair(k,mapped_type() ) ) ).first ) ).second;	
		}

		ft::pair<iterator,bool> insert (const value_type& val) {



			return this->ft_search( this->_bst, val );
		}

//		iterator insert (iterator position, const value_type& val) {
//
//			
//		}
//
//		template <class InputIterator>
//  		void insert (InputIterator first, InputIterator last) {
//
//		}
	


		private:
	
		allocator_type _alloc;
		key_compare _comp;
		size_type _size;
		typedef struct s_node {

			pointer content;
			struct s_node *left;	
			struct s_node *right;
			
		} t_node;


		ft::pair <iterator, bool> ft_search( t_node * &tmp, const value_type& val ) {


			if ( !tmp ) {
	
				tmp = new t_node;  
				tmp->content = this->_alloc.allocate( 1 );
				this->_alloc.construct( tmp->content, val );
				tmp->left = 0;
				tmp->right = 0;
				this->_size++;

				return ft::make_pair<iterator, bool> ( tmp->content, true);
			}

			if ( val.first == tmp->content->first )
				return ft::make_pair<iterator, bool> ( tmp->content, false);
	

			if ( val.first < tmp->content->first )
				return	ft_search( tmp->left, val  );
			if ( val.first > tmp->content->first )
				return	ft_search( tmp->right, val );

			return ft::make_pair<iterator, bool> (tmp->content , false);
			}
			


		public:

		t_node *_bst;

	};
}

#endif
