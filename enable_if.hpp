/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 11:27:54 by eoddish           #+#    #+#             */
/*   Updated: 2021/12/18 11:29:16 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENABLE_IF_HPP
# define ENABLE_IF_HPP

namespace ft {

template <bool Cond, class T = void>
    struct enable_if;

    template < class T >
    struct enable_if< true, T > {

        typedef T type;
    };

}



#endif
