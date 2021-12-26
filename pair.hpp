/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 20:33:46 by eoddish           #+#    #+#             */
/*   Updated: 2021/12/24 01:21:37 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft {

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

//		template< class U1, class U2 >
//		pair& operator= (const pair<U1, U2 > & pr) {
//			this->first =  first_type( pr.first );
//			this->second = second_type( pr.second );
//			return *this;
//		}
	
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


}

#endif
