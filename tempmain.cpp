#include "vector.hpp"
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
	for( ft::vector<int>::iterator it = vct1.begin(); it != vct1.end(); ++it ) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}
