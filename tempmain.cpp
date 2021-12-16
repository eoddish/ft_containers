#include "vector.hpp"
#include "is_integral.hpp"
#include "lexicographical_compare.hpp"
#include "equal.hpp"
#include "pair.hpp"
#include <typeinfo>
#include <utility>

template <typename T>
void	ft_print(ft::vector<T> & vct) {
	for( ft::vector<int>::iterator it = vct.begin(); it != vct.end(); ++it ) {
		std::cout << *it << " ";
	
	}

	std::cout << std::endl;
	}


template <class T>
typename ft::enable_if<ft::is_integral<T>::value,bool>::type is_odd (T i) { return bool( i%2 ); }

bool mycomp (char c1, char c2)
{ return std::tolower(c1)<std::tolower(c2); }	

int main( void ) {

	ft::vector<int> vct1;
	vct1.push_back( 2 );
	std::cout << vct1.front() << " ";
	std::cout << vct1.back() << std::endl;

	vct1.push_back( 3 );
	std::cout << vct1.front() << " ";
	std::cout << vct1.back() << std::endl;

	vct1.push_back( 5 );
	std::cout << *vct1.begin() << " ";
	std::cout << *vct1.end() << std::endl;
	
	vct1.push_back( 8 );
	ft_print( vct1 );
	
	ft::vector<int> vct2( 10, 8 );
	ft_print( vct2 );	

	ft::vector<int> vct3( vct1.begin(), vct1.end()  );
	ft_print( vct3 );	
	
	ft::vector<int> vct4( vct2 );
	ft_print( vct4 );

	typedef ft::iterator_traits<ft::vector<int>::iterator> traits;
	if (typeid(traits::iterator_category)==typeid(std::random_access_iterator_tag))
    std::cout << "vct4.begin() is a random-access iterator" << std::endl;
	
	ft::vector<int> vct5;
	for (int i=0; i<10; i++) vct5.push_back(i);
	typedef ft::vector<int>::iterator iter_type;
	ft::reverse_iterator<iter_type> rev_end ( vct5.begin() ) ;
	ft::reverse_iterator<iter_type> rev_begin ( vct5.end() );
	std::cout << "vct5:";
	for (iter_type it = rev_end.base(); it != rev_begin.base(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
	std::cout << "reversed vct5:";
	for (; rev_begin != rev_end; ++rev_begin)
		std::cout << ' ' << *rev_begin;
	std::cout << '\n';


	std::cout << std::boolalpha;
//	short int i = 1;
	int i = 1;	
//	long int i = 1;

	std::cout << "float: " << ft::is_integral<float>::value << std::endl;
	std::cout << "intptr_t: " << ft::is_integral<intptr_t>::value << std::endl;
 	std::cout << "i is odd: " << is_odd(i) << std::endl;

	std::cout << ft::equal(vct2.begin(), vct2.end(), vct4.begin() ) << std::endl;

	std::cout << ft::equal(vct2.begin(), vct2.end(), vct3.begin() ) << std::endl;

	char foo[]="Apple";
	char bar[]="apartment";

	std::cout << "Using default comparison (operator<): ";
	std::cout << ft::lexicographical_compare(foo,foo+5,bar,bar+9);
	std::cout << '\n';
	
	std::cout << "Using mycomp as comparison object: ";
	std::cout << ft::lexicographical_compare(foo,foo+5,bar,bar+9,mycomp);
	std::cout << '\n';

	ft::pair <std::string,double> product1;                     // default constructor
	ft::pair <std::string,double> product2 ("tomatoes",2.30);   // value init
	ft::pair <std::string,double> product3 (product2);          // copy constructor
	
//	product1 = std::make_pair(std::string("lightbulbs"),0.99);   // using make_pair (move)
	
	product1.first = "shoes";                  // the type of first is string
	product1.second = 39.90;                   // the type of second is double
	
	std::cout << "The price of " << product1.first << " is $" << product1.second << '\n';
	std::cout << "The price of " << product2.first << " is $" << product2.second << '\n';
	std::cout << "The price of " << product3.first << " is $" << product3.second << '\n';
}
