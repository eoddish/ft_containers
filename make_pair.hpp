/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_pair.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 19:11:01 by eoddish           #+#    #+#             */
/*   Updated: 2021/12/18 11:08:27 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAKE_PAIR_HPP
# define MAKE_PAIR_HPP

namespace ft {

	template <class T1, class T2>
		pair<T1,T2> make_pair (T1 x, T2 y) {

			return ( pair<T1,T2>(x,y) );
		}
}

#endif
