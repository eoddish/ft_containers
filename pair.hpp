/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 20:33:46 by eoddish           #+#    #+#             */
/*   Updated: 2021/12/16 02:57:13 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			pair (const pair<U,V>& pr) {
	
			*this = pr;	
		};
	
		pair (const first_type& a, const second_type& b) : first( a ), second ( b ) {};
		pair& operator= (const pair& pr) {
	
			if( this != &pr ) {
	
				this->first = first_type( pr.first );
				this->second = second_type( pr.second );
			}
			return this;
		}
	
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
