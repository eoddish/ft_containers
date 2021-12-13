#include "vector.hpp"
#include <typeinfo>

template <typename T>
void	ft_print(ft::vector<T> & vct) {
	for( ft::vector<int>::iterator it = vct.begin(); it != vct.end(); ++it ) {
		std::cout << *it << " ";
	
	}

	std::cout << std::endl;
	}

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
}
