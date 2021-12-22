/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <eoddish@student.21-school.ru      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 00:31:01 by eoddish           #+#    #+#             */
/*   Updated: 2021/12/23 02:03:31 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

namespace ft {

	template < class Key, class T, class Compare = less<Key,
		class Alloc = allocator<pair<const Key,T> > >
	class map {

	public:

	typedef Key key_type;
	typedef T mapped_type;	
	typedef pair<const key_type,mapped_type> value_type;
	typedef Compare key_compare; 
	typedef value_compare;	
	typedef Alloc allocator_type;
	typedef allocator_type::reference reference;
	typedef allocator_type::const_reference const_reference;
	typedef allocator_type::pointer pointer;
	typedef allocator_type::const_pointer const_pointer;
//	typedef iterator;
//	typedef const_iterator;
//	typedef reverse_iterator;
//	typedef const_reverse_iterator;
//	typedef iterator_traits<iterator>::difference_type difference_type;
	typedef size_t size_type;
	

	explicit map (const key_compare& comp = key_compare(),
		const allocator_type& alloc = allocator_type()) {

	}

	template <class InputIterator>
	map (InputIterator first, InputIterator last,
		const key_compare& comp = key_compare(),
		const allocator_type& alloc = allocator_type()) {

	}

	map (const map& x) {

	}




	}

	private:

	allocator_type _alloc;
	key_compare _comp;

}

#endif
