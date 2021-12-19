/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 11:16:57 by eoddish           #+#    #+#             */
/*   Updated: 2021/12/18 11:27:15 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

namespace ft {

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

}
#endif
