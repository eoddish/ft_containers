/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 11:16:57 by eoddish           #+#    #+#             */
/*   Updated: 2021/12/29 20:50:34 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

namespace ft {

 template <class Iterator>
    class reverse_iterator {

		public:

        typedef Iterator iterator_type;
        typedef typename ft::iterator_traits<Iterator>::iterator_category iterator_category;
        typedef typename ft::iterator_traits<Iterator>::value_type value_type;
        typedef typename ft::iterator_traits<Iterator>::difference_type difference_type;
        typedef typename ft::iterator_traits<Iterator>::pointer pointer;
        typedef typename ft::iterator_traits<Iterator>::reference reference;

        reverse_iterator( ) : base_it( 0 ) {}
        reverse_iterator( iterator_type it ) : base_it( it ) {}
        template <class Iter>
        reverse_iterator (const reverse_iterator<Iter>& rev_it) : base_it( rev_it.base_it ) {}

        iterator_type base( void ) const { return  base_it ; };
        reverse_iterator& operator++() { --base_it; return *this;}
        reverse_iterator operator++(int) {reverse_iterator tmp(*this); operator++(); return tmp;}
        bool operator==(const reverse_iterator& rhs) const {return base_it==rhs.base_it;}
        bool operator!=(const reverse_iterator& rhs) const {return base_it!=rhs.base_it;}
        reference operator*() { iterator_type tmp = iterator_type(--base_it); base_it++; return *tmp; }

        iterator_type base_it;
		
	};

}
#endif
