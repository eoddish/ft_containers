#include "vector.hpp"

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
}
