/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <eoddish@student.21-school.ru      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 17:27:06 by eoddish           #+#    #+#             */
/*   Updated: 2022/01/13 03:19:35 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_HPP
# define UTILITIES_HPP

# include <typeinfo>
# include <iostream>

namespace ft {

	template <class InputIterator1, class InputIterator2>
		bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
				InputIterator2 first2, InputIterator2 last2) {
			while (first1!=last1) {
				if (first2==last2 || *first2<*first1) return false;
				else if (*first1<*first2) return true;
				++first1; ++first2;
			}
			return (first2!=last2);
		}

	template <class InputIterator1, class InputIterator2, class Compare>
		bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
				InputIterator2 first2, InputIterator2 last2, Compare comp) {
			while (first1!=last1) {
				if ( first2==last2 || !comp( *first1, *first2 ) ) return false;
				else if ( comp( *first1, *first2 ) ) return true;
				++first1; ++first2;
			}
			return (first2!=last2);
		}



	template <class InputIterator1, class InputIterator2>
		bool equal ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 ) {
			while (first1!=last1) {
				if (!(*first1 == *first2))   // or: if (!pred(*first1,*first2)), for version 2
					return false;
				++first1; ++first2;
			}
			return true;
		}

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
		bool equal (InputIterator1 first1, InputIterator1 last1,
				InputIterator2 first2, BinaryPredicate pred) {
			while (first1!=last1) {
				if (!pred(*first1,*first2))
					return false;
				++first1; ++first2;
			}
			return true;
		}



	template <bool Cond, class T = void>
		struct enable_if;

	template < class T >
		struct enable_if< true, T > {

			typedef T type;
		};



	template <class T>
		struct is_integral {

			typedef bool value_type;
			static bool const value = false;
		};
	;
	template<> struct is_integral<bool> {
		static bool const value = true;
	};
	template<> struct is_integral<char> {
		static bool const value = true;
	};
	template<> struct is_integral<char16_t> {
		static bool const value = true;
	};
	template<> struct is_integral<char32_t> {
		static bool const value = true;
	};
	template<> struct is_integral<wchar_t> {
		static bool const value = true;
	};
	template<> struct is_integral<signed char> {
		static bool const value = true;
	};
	template<> struct is_integral<short int> {
		static bool const value = true;
	};
	template<> struct is_integral<int> {
		static bool const value = true;
	};
	template<> struct is_integral<long int> {
		static bool const value = true;
	};
	template<> struct is_integral<long long int> {
		static bool const value = true;
	};
	template<> struct is_integral<unsigned char> {
		static bool const value = true;
	};
	template<> struct is_integral<unsigned short int> {
		static bool const value = true;
	};
	template<> struct is_integral<unsigned int> {
		static bool const value = true;
	};
	template<> struct is_integral<unsigned long int> {
		static bool const value = true;
	};
	template<> struct is_integral<unsigned long long int> {
		static bool const value = true;
	};



	template< class Iterator >
		struct iterator_traits {
			typedef typename Iterator::iterator_category iterator_category;
			typedef typename Iterator::value_type value_type;
			typedef typename Iterator::difference_type difference_type;
			typedef typename Iterator::pointer pointer;
			typedef typename Iterator::reference reference;

		};



	template <class T1, class T2>
		struct pair {

			typedef T1 first_type;
			typedef T2 second_type;

			first_type first;
			second_type second;

			public:

			pair() : first( first_type() ), second( second_type() ) {};

			template<class U, class V>
				pair (const pair<U,V>& pr) : first( first_type( pr.first ) ), second( second_type( pr.second ) ) {

				};

			pair (const first_type& a, const second_type& b) : first( first_type( a ) ), second ( second_type( b ) ) {};

		};

	template <class T1, class T2>
		bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return lhs.first==rhs.first && lhs.second==rhs.second; }

	template <class T1, class T2>
		bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return !(lhs==rhs); }

	template <class T1, class T2>
		bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); }

	template <class T1, class T2>
		bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return !(rhs<lhs); }

	template <class T1, class T2>
		bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return rhs<lhs; }

	template <class T1, class T2>
		bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return !(lhs<rhs); }



	template <class T1, class T2>
		pair<T1,T2> make_pair (T1 x, T2 y) {

			return ( pair<T1,T2>(x,y) );
		}



	template <class Iterator>
		class reverse_iterator {

			public:

				typedef Iterator iterator_type;
				typedef typename ft::iterator_traits<Iterator>::iterator_category iterator_category;
				typedef typename ft::iterator_traits<Iterator>::value_type value_type;
				typedef typename ft::iterator_traits<Iterator>::difference_type difference_type;
				typedef typename ft::iterator_traits<Iterator>::pointer pointer;
				typedef typename ft::iterator_traits<Iterator>::reference reference;

				reverse_iterator( ) : base_it( iterator_type() ) {}
				reverse_iterator( iterator_type it ) : base_it( it ) {}
				template <class Iter>
					reverse_iterator (const reverse_iterator<Iter>& rev_it) : base_it( rev_it.base_it ) {}

				iterator_type base( void ) const { return  base_it ; };
				reverse_iterator& operator++() { --base_it; return *this;}
				reverse_iterator operator++(int) {reverse_iterator tmp(*this); operator++(); return tmp;}
				reverse_iterator& operator--() { ++base_it; return *this;}
				reverse_iterator operator--(int) {reverse_iterator tmp(*this); operator--(); return tmp;}

				reverse_iterator operator+( const int & nbr ) { return reverse_iterator( base_it - nbr ) ;}
				reverse_iterator operator-( const int & nbr ) { return reverse_iterator( base_it + nbr ) ;}

				bool operator==(const reverse_iterator& rhs) const {return base_it==rhs.base_it;}
				bool operator!=(const reverse_iterator& rhs) const {return base_it!=rhs.base_it;}
				reference operator*() { iterator_type tmp = iterator_type(--base_it); base_it++; return *tmp; }
				pointer operator->() { iterator_type tmp = iterator_type(--base_it); base_it++; return &(*tmp); }

				iterator_type base_it;

		};

}



#endif
