/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integral.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 00:26:39 by eoddish           #+#    #+#             */
/*   Updated: 2021/12/15 00:52:50 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

namespace ft {

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
}
