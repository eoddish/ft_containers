#include <iostream>
#include <string>
#include <deque>
#include <list>
#include <vector>

#if 0 //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft = std;
#else
	#include "map.hpp"
	#include "stack.hpp"
	#include "vector.hpp"

#endif

#include <stdlib.h>

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};


#define COUNT (MAX_RAM / (int)sizeof(Buffer))

template<typename T>
class MutantStack : public ft::stack<T>
{
public:
	MutantStack() {}
	MutantStack(const MutantStack<T>& src) { *this = src; }
	MutantStack<T>& operator=(const MutantStack<T>& rhs) 
	{
		this->c = rhs.c;
		return *this;
	}
	~MutantStack() {}

	typedef typename ft::stack<T>::container_type::iterator iterator;

	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c.end(); }
};


template <class T>
typename ft::enable_if<ft::is_integral<T>::value,bool>::type is_odd (T i) { return bool( i%2 ); }

bool mycomp (char c1, char c2)
{ return std::tolower(c1)<std::tolower(c2); }	

template <typename T>
void	ft_print(ft::vector<T> & vct) {
	for( ft::vector<int>::iterator it = vct.begin(); it != vct.end(); ++it ) {
		std::cout << *it << " ";

	}

	std::cout << std::endl;
}


int main(int argc, char** argv) {
	if (argc != 2)
	{
		std::cerr << "Usage: ./test seed" << std::endl;
		std::cerr << "Provide a seed please" << std::endl;
		std::cerr << "Count value:" << COUNT << std::endl;
		return 1;
	}
	const int seed = atoi(argv[1]);
	srand(seed);

	ft::vector<std::string> vector_str;
	ft::vector<int> vector_int;
	ft::stack<int> stack_int;
	ft::vector<Buffer> vector_buffer;
	ft::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
	ft::map<int, int> map_int;

	for (int i = 0; i < COUNT; i++)
	{
		vector_buffer.push_back(Buffer());
	}

	for (int i = 0; i < COUNT; i++)
	{
		const int idx = rand() % COUNT;
		vector_buffer[idx].idx = 5;
	}
	ft::vector<Buffer>().swap(vector_buffer);

	try
	{
		for (int i = 0; i < COUNT; i++)
		{
			const int idx = rand() % COUNT;
			vector_buffer.at(idx);
			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
		}
	}
	catch(const std::exception& e)
	{
		//NORMAL ! :P
	}
	
	for (int i = 0; i < COUNT; ++i)
	{
		map_int.insert(ft::make_pair(rand(), rand()));
	}

	int sum = 0;
	for (int i = 0; i < 10000; i++)
	{
		int access = rand();
		sum += map_int[access];
	}
	std::cout << "should be constant with the same seed: " << sum << std::endl;

	{
		ft::map<int, int> copy = map_int;
	}
	MutantStack<char> iterable_stack;
	for (char letter = 'a'; letter <= 'z'; letter++)
		iterable_stack.push(letter);
	for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
	{
		std::cout << *it;
	}
	std::cout << std::endl;


	//++++++++++ VECTOR +++++++++++++++

	// ===== CONSTRUCTORS & PUSH_BACK =======

	ft::vector<int> vct1;

	vct1.push_back( 2 );

	std::cout << "vct1 front: " << vct1.front() << " ";
	std::cout << "vct1 back: " << vct1.back() << std::endl;

	vct1.push_back( 3 );

	// ===== FRONT & BACK =====

	std::cout << "vct1 front: " << vct1.front() << " ";
	std::cout << "vct1.back: " << vct1.back() << std::endl;

	// ===== BEGIN & END =====

	vct1.push_back( 5 );

	std::cout << "vct1 begin: " << *vct1.begin() << " ";
	std::cout << "vct1 end - 1: " << *(--vct1.end()) << std::endl;

	vct1.push_back( 8 );
	std::cout << "vct1: ";
	ft_print( vct1 );

	ft::vector<int> vct2( 10, 8 );
	std::cout << "vct2: ";
	ft_print( vct2 );	

	ft::vector<int> vct3( vct1.begin(), vct1.end()  );
	std::cout << "vct3: ";
	ft_print( vct3 );	

	ft::vector<int> vct4( vct2 );
	std::cout << "vct4: ";
	ft_print( vct4 );

	// ===== OPERATOR= =====

	vct4 = vct3;
	std::cout << "vct4: ";
	ft_print( vct4 );

	// ++++++ UTILITIES ++++++

	// ===== ITERATOR_TRAITS =====

	typedef ft::iterator_traits<ft::vector<int>::iterator> traits;
	if (typeid(traits::iterator_category)==typeid(std::random_access_iterator_tag))
		std::cout << "vct4.begin() is a random-access iterator" << std::endl;

	// ===== REVERSE_ITERATOR =====

	ft::vector<int> vct5;
	for (int i=0; i<10; i++) vct5.push_back(i);
	typedef ft::vector<int>::iterator iter_type;
	ft::reverse_iterator<iter_type> rev_end ( vct5.begin() );
	ft::reverse_iterator<iter_type> rev_begin ( vct5.end() );
	std::cout << "vct5:";
	for (iter_type it = rev_end.base(); it != rev_begin.base(); ++it)
		std::cout << ' ' << *it;
	std::cout << std::endl;
	std::cout << "reversed vct5:";
	for (; rev_begin != rev_end; ++rev_begin)
		std::cout << ' ' << *rev_begin;
	std::cout << std::endl;


	std::cout << std::boolalpha;
	int i = 1;	

	//===== IS_INTEGRAL ===== 	

	std::cout << "float: " << ft::is_integral<float>::value << std::endl;
	std::cout << "intptr_t: " << ft::is_integral<intptr_t>::value << std::endl;
	std::cout << "i is odd: " << is_odd(i) << std::endl;

	if ( ft::is_integral<int>() )
		std::cout << "int is an integral type" << std::endl;

	if ( ft::is_integral<int>::value )
		std::cout << "int is an integral type" << std::endl;


	//===== EQUAL ===== 	

	std::cout << ft::equal(vct2.begin(), vct2.end(), vct4.begin() ) << std::endl;

	std::cout << ft::equal(vct2.begin(), vct2.end(), vct3.begin() ) << std::endl;


	//===== LEXICOGRAPHICAL_COMPARE ===== 	

	char foo[]="Android";
	char bar[]="apple";

	std::cout << "operator<: ";
	std::cout << ft::lexicographical_compare(foo, foo + 7, bar, bar + 5);
	std::cout << std::endl;

	std::cout << "mycomp: ";
	std::cout << ft::lexicographical_compare(foo, foo + 7, bar, bar + 5, mycomp);
	std::cout << std::endl;

	//===== PAIR =====

	ft::pair <std::string,double> p1;                     
	ft::pair <std::string,double> p2 ("peaches",2.30);   
	ft::pair <std::string,double> p3 (p2);          

	//===== MAKE_PAIR =====

	p1 = ft::make_pair(std::string("matches"),0.99);   

	p2.first = "shirts";                  
	p2.second = 39.90;                   

	std::cout << "The price of " << p1.first << " is $" << p1.second << std::endl;
	std::cout << "The price of " << p2.first << " is $" << p2.second << std::endl;
	std::cout << "The price of " << p3.first << " is $" << p3.second << std::endl;

	ft::pair <int,int> foo1;
	ft::pair <int,int> bar1;

	foo1 = ft::make_pair (20,30);
	bar1 = ft::make_pair (26, 39); 

	std::cout << "foo1: " << foo1.first << ", " << foo1.second << std::endl;
	std::cout << "bar1: " << bar1.first << ", " << bar1.second << std::endl;

	//===== RBEGIN & REND =====

	ft::vector<int> vct6 (5); 

	ft::vector<int>::reverse_iterator rit = vct6.rbegin();

	i=0;
	for (rit = vct6.rbegin(); rit!= vct6.rend(); ++rit)
		*rit = ++i;

	std::cout << "vct6 contains:";
	ft_print( vct6 );

	// ===== MAX_SIZE =====

	std::cout << "vct6 max_size: " << vct6.max_size() << std::endl;

	// ===== RESIZE =====

	ft::vector<int> vct7 = vct4;

	vct7.resize(5);
	vct7.resize(8,100);
	vct7.resize(12);

	std::cout << "vct7 contains:";
	ft_print( vct7 );

	//=====RESERVE=====

	ft::vector<int>::size_type sz;

	ft::vector<int> vct8;
	sz = vct8.capacity();
	std::cout << "making vct8 grow:\n";
	for (int j=0; j<100; ++j) {
		vct8.push_back(j);
		if (sz!=vct8.capacity()) {
			sz = vct8.capacity();
			std::cout << "capacity changed: " << sz << '\n';
		}
	}

	ft::vector<int> vct9;
	sz = vct9.capacity();
	vct9.reserve(100); 
	std::cout << "making vct9 grow:\n";
	for (int j=0; j<100; ++j) {
		vct9.push_back(j);
		if (sz!=vct9.capacity()) {
			sz = vct9.capacity();
			std::cout << "capacity changed: " << sz << '\n';
		}
	}

	try {
		vct8.resize(vct8.max_size()+1);
	}
	catch (const std::length_error& le) {
		std::cerr << "Length error: " << le.what() << '\n';
	}

	//===== AT =====

	std::cout << "vct1.at( 0 ): " << vct1.at( 0 ) << std::endl;
	std::cout << "vct1.at( 2 ): " << vct1.at( 2 ) << std::endl;
	try {
		vct8.at(20)=100;   
	}
	catch (const std::out_of_range& oor) {
		std::cerr << "Out of Range error: " << oor.what() << '\n';
	}

	//=====ASSIGN=====

	ft::vector<int> vct10;
	ft::vector<int> vct11;
	ft::vector<int> vct12;
	vct10.assign ((size_t )7, 100);             

	ft::vector<int>::iterator it10;
	it10 = vct10.begin() + 1;

	vct11.assign ( it10, vct10.end() - 1); 

	int int12[] = { 42, 21, 5 };
	vct12.assign (int12, int12 + 3);   

	std::cout << "Size of vct10: " << int (vct10.size()) << std::endl;
	std::cout << "Size of vct11: " << int (vct11.size()) << std::endl;
	std::cout << "Size of vct12: " << int (vct12.size()) << std::endl;
	std::cout << "vct12: ";
	ft_print( vct12 );

	//=====POP_BACK=====

	vct12.pop_back();
	std::cout << "vct12: ";
	ft_print( vct12 );

	//=====INSERT======

	ft::vector<int> vct13 ((size_t)3,100);
	ft::vector<int>::iterator it1;

	it1 = vct13.begin();
	it1 = vct13.insert ( it1 , 200 );

	vct13.insert (it1,(size_t)2,300);

	it1 = vct13.begin();

	ft::vector<int> vct14 ((size_t) 2,400);
	vct13.insert (it1+2,vct14.begin(),vct14.end());

	int arr13 [] = { 601,602,603 };
	vct13.insert (vct13.begin(), arr13, arr13+3);

	std::cout << "vct13 contains:";
	ft_print( vct13 );


	//=====ERASE=====

	ft::vector<int> vct15;

	for (int i=1; i<=10; i++) vct15.push_back(i);

	std::cout << "vct15 contains:";
	ft_print( vct15 );

	vct15.erase (vct15.begin()+5);

	std::cout << "vct15 contains:";
	ft_print( vct15 );

	ft::vector<int>::iterator ret = vct15.erase (vct15.begin(),vct15.begin()+3);

	std::cout << "vct15 contains:";
	ft_print( vct15 );
	std::cout << "erase returned iterator to: " << *ret << std::endl;

	//=====SWAP=====

	ft::vector<int> vct16(  3,100 );   

	ft::vector<int> vct17( 5,200 );   

	ft::vector<int>::iterator it16 = vct16.begin();

	vct16.swap(vct17);

	std::cout << "vct16 contains:";
	ft_print( vct16 );

	std::cout << "vct17 contains:";
	ft_print( vct17 );

	std::cout << "vct16 begin after swap with vct17: ";
	std::cout << *it16 << std::endl;


	//=====CLEAR======

	ft::vector<int> vct18;
	vct18.push_back (100);
	vct18.push_back (200);
	vct18.push_back (300);

	std::cout << "vct18 contains:";
	ft_print( vct18 );

	vct18.clear();
	vct18.push_back (1101);
	vct18.push_back (2202);

	std::cout << "vct18 contains:";
	ft_print( vct18 );

	//=====GET_ALLOCATOR=====

	ft::vector<int> vct19;

	int * p;

	p = vct19.get_allocator().allocate(5);

	for (i=0; i<5; i++) vct19.get_allocator().construct(&p[i],i);

	std::cout << "The allocated array contains:";
	for (i=0; i<5; i++) std::cout << ' ' << p[i];
	std::cout << '\n';

	for (i=0; i<5; i++) vct19.get_allocator().destroy(&p[i]);
	vct19.get_allocator().deallocate(p,5);

	//=====RELATIONAL OPERATORS=====

	ft::vector<int> vct20 ((size_t)3,100);   
	ft::vector<int> vct21 ((size_t)2,200);   

	if (vct20==vct21) std::cout << "vct20 and vct21 are equal\n";
	if (vct20!=vct21) std::cout << "vct20 and vct21 are not equal\n";
	if (vct20< vct21) std::cout << "vct20 is less than vct21\n";
	if (vct20> vct21) std::cout << "vct20 is greater than vct21\n";
	if (vct20<=vct21) std::cout << "vct20 is less than or equal to vct21\n";
	if (vct20>=vct21) std::cout << "vct20 is greater than or equal to vct21\n";

	//=====SWAP=====

	ft::vector<int>::iterator swapit1 = vct16.begin(); 
	ft::vector<int>::iterator swapit2 = vct17.begin(); 
	vct17.swap( vct16 );
	std::cout << "vct16: ";
	ft_print( vct16 );
	std::cout << "vct17: ";
	ft_print( vct17 );
	std::cout << "vct16.begin: " << *swapit2 << std::endl;
	std::cout << "vct17.begin: " << *swapit1 << std::endl;

	//++++++++++++STACK++++++++++++++

	//=====CONSTRUCTOR=====

	ft::vector<int> vct23 ((size_t)2,200);       
	ft::stack<int,ft::vector<int> > stc1;        
	ft::stack<int,ft::vector<int> > stc2 ( vct23 );

	//check compatibility
	
	ft::stack<int,std::vector<int> > stc11;        
	ft::stack<int,std::list<int> > stc12;        
	ft::stack<int,std::deque<int> > stc13;        

	//=====EMPTY=====

	std::cout << "stc1 is empty: " << stc1.empty() << std::endl;
	std::cout << "stc2 is empty: " << stc2.empty() << std::endl;


	//=====SIZE======

	std::cout << "size of stc1: " << stc1.size() << std::endl;
	std::cout << "size of stc2: " << stc2.size() << std::endl;

	//=====TOP======
		
	stc2.push( 300 );
	std::cout << "top of stc2: " << stc2.top() << std::endl;

	//=====PUSH=====

	ft::stack<int> stc3;

	for (int j = 0; j < 5; ++j)
		stc3.push( j );

	//=====POP=====

	std::cout << "Pop elements";
	while ( !stc3.empty() ) {

		std::cout << ' ' << stc3.top();
		stc3.pop();
	}
	std::cout << '\n';

	//=====RELATIONAL OPERATORS=====

	if (stc2==stc1) std::cout << "stc2 and stc1 are equal\n";
	if (stc2!=stc1) std::cout << "stc2 and stc1 are not equal\n";
	if (stc2< stc1) std::cout << "stc2 is less than stc1\n";
	if (stc2> stc1) std::cout << "stc2 is greater than stc1\n";
	if (stc2<=stc1) std::cout << "stc2 is less than or equal to stc1\n";
	if (stc2>=stc1) std::cout << "stc2 is greater than or equal to stc1\n";

	//++++++++++++++++++MAP+++++++++++++++++++

	//===== CONSTRUCTORS =====

	ft::map<char,int> map1;
	map1['a']=10;
	map1['b']=30;
	map1['c']=50;
	map1['d']=70;

	std::cout << map1['a'] << std::endl;
	std::cout << map1['b'] << std::endl;
	std::cout << map1['c'] << std::endl;
	std::cout << map1['d'] << std::endl;

	std::cout << "size of map1: " << map1.size() << std::endl;
	std::cout << "map1: " << std::endl;
	for( ft::map<char, int>::iterator it = map1.begin(); it != map1.end(); ++it )
		std::cout << (*it).first << " " << (*it).second << std::endl; 

	ft::map<char,int> map2 (map1.begin(),map1.end());

	std::cout << "map2: " << std::endl;
	for( ft::map<char, int>::reverse_iterator it = map2.rbegin(); it != map2.rend(); ++it )
		std::cout << (*it).first << " " << (*it).second << std::endl; 

	ft::map<char,int> map3 (map2);

	std::cout << "map3: " << std::endl;
	for( ft::map<char, int>::reverse_iterator it = map3.rbegin(); it != map3.rend(); ++it )
		std::cout << (*it).first << " " << (*it).second << std::endl; 

	//===== OPERATOR= ======

	map3['e'] = 100;
	map2 = map3;

	std::cout << "map2: " << std::endl;
	for( ft::map<char, int>::iterator it = map2.begin(); it != map2.end(); ++it )
		std::cout << (*it).first << " " << (*it).second << std::endl; 

	//===== BEGIN =====

	ft::map<char, int>::iterator itm; 
	itm = map2.begin();
	std::cout << "map2 begin: ";
	std::cout << itm->first << " " << itm->second << std::endl;


	//===== END =====

	itm = map2.end();
	itm--;
	std::cout << "map2 previous to end: ";
	std::cout << itm->first << " " << itm->second << std::endl;

	//===== RBEGIN =====

	ft::map<char, int>::reverse_iterator ritm; 
	ritm = map2.rbegin();
	std::cout << "map2 rbegin: ";
	std::cout << ritm->first << " " << ritm->second << std::endl;


	//===== REND =====

	ritm = map2.rend();
	ritm--;
	std::cout << "map2 previous to rend: ";
	std::cout << ritm->first << " " << ritm->second << std::endl;

	//===== EMPTY =====

	ft::map<char,int> map4;

	std::cout << "map1 is empty: " << map1.empty() << std::endl;
	std::cout << "map4 is empty: " << map4.empty() << std::endl;

	//===== SIZE =====

	std::cout << "map1 size: " << map1.size() << std::endl;
	std::cout << "map2 size: " << map2.size() << std::endl;
	std::cout << "map3 size: " << map3.size() << std::endl;
	std::cout << "map4 size: " << map4.size() << std::endl;

	//===== MAX_SIZE =====

	std::cout << "map1 max_size: " << map1.max_size() << std::endl;
	std::cout << "map2 max_size: " << map2.max_size() << std::endl;

	//===== OPERATOR[] =====

	map4['w'] = 1;
	map4['z'] = 4;

	//===== INSERT =====

	map4.insert( map4.begin(), ft::make_pair( 'x', 2 ) );

	ft::map<char, int>::iterator itmap4 = map4.begin();
	std::cout << "itmap4 before inserting: " << itmap4->first << " " << itmap4->second << std::endl; 
	map4.insert( map4.begin(), ft::make_pair( 'y', 3 ) );
	std::cout << "itmap4 after inserting: " << itmap4->first << " " << itmap4->second << std::endl; 

	std::cout << "map4: " << std::endl;
	for( ft::map<char, int>::iterator it = map4.begin(); it != map4.end(); ++it )
		std::cout << (*it).first << " " << (*it).second << std::endl; 

	//===== ERASE =====

	map4.erase( map4.begin() );

	itmap4 = map4.begin();
	std::cout << "itmap4 before erasing: " << itmap4->first << " " << itmap4->second << std::endl; 
	map4.erase( 'z' );
	std::cout << "itmap4 after erasing: " << itmap4->first << " " << itmap4->second << std::endl; 


	std::cout << "map4: " << std::endl;
	for( ft::map<char, int>::iterator it = map4.begin(); it != map4.end(); ++it )
		std::cout << (*it).first << " " << (*it).second << std::endl; 

	std::cout << "map4 size: " << map4.size() << std::endl; 

	//===== VALUE_COMP ======

	std::cout << "map4 contains:\n";

	ft::pair<char,int> highest = *map4.rbegin();          
	ft::map<char,int>::iterator mit = map4.begin();
	do {
		std::cout << mit->first << " => " << mit->second << '\n';
	} while ( map4.value_comp()(*mit++, highest) );

	//===== FIND ======

	std::cout << "map4 find x: " << map4.find( 'x' )->second << std::endl; 

	//===== SWAP ======

	ft::map<char, int>::iterator itb1 = map2.begin();
	ft::map<char, int>::iterator itb2 = map4.begin();
	map4.swap( map2 );

	std::cout << "itb1: " << itb1->first << std::endl;
	std::cout << "itb2: " << itb2->first << std::endl;


	std::cout << "map4 swap map2: " << std::endl;

	std::cout << "map2: " << std::endl;
	for( ft::map<char, int>::iterator it = map2.begin(); it != map2.end(); ++it )
		std::cout << (*it).first << " " << (*it).second << std::endl; 

	std::cout << "map4: " << std::endl;
	for( ft::map<char, int>::iterator it = map4.begin(); it != map4.end(); ++it )
		std::cout << (*it).first << " " << (*it).second << std::endl; 

	//===== COUNT =====

	std::cout << "map3 count a: " << map3.count( 'a' ) << std::endl; 
	std::cout << "map3 count z: " << map3.count( 'z' ) << std::endl; 


	//===== LOWER_BOUND =====

	std::cout << "map3 lower_bound b: ";
	if ( map3.lower_bound( 'b' ) != map3.end() )
		std::cout << map3.lower_bound( 'b' )->first;
	std::cout << std::endl;

	std::cout << "map3 lower_bound x: ";
	if ( map3.lower_bound( 'x' ) != map3.end() )
		std::cout << map3.lower_bound( 'x' )->first;
	std::cout << std::endl;


	//===== UPPER_BOUND =====

	std::cout << "map3 upper_bound b: ";
	if ( map3.upper_bound( 'b' ) != map3.end() )
		std::cout << map3.upper_bound( 'b' )->first;
	std::cout << std::endl;

	std::cout << "map3 upper_bound x: ";
	if ( map3.upper_bound( 'x' ) != map3.end() )
		std::cout << map3.upper_bound( 'x' )->first;
	std::cout << std::endl;


	//===== EQUAL_RANGE =====

	std::cout << "lower bound points to: ";
	std::cout << map3.equal_range( 'b' ).first->first << std::endl; 

	std::cout << "upper bound points to: ";
	std::cout << map3.equal_range( 'b' ).second->first << std::endl; 

	
//	// ===== AVL-TREE( FOR FT::MAP ONLY ) =====
//
//	std::cout << std::endl;
//	ft::map<int, int>mp;
//
//	for (int i = 0, j = 0; i < 12; ++i, ++j)
//		mp.insert(ft::make_pair(i, j));
//
//	ft::map<int, int>::iterator itavl = mp.begin();
//
//	for (; itavl != mp.end(); itavl = mp.begin()) {
//
//		for( ft::map<int,int>::iterator it = mp.begin(); it != mp.end(); ++it ) {
//
//			std::cout << it->first << " " << it.node->bf << " ";
//
//			if ( it.node->left )
//				std::cout << "L: " << it.node->left->content->first << " ";
//
//			if ( it.node->right )
//				std::cout << "R: " << it.node->right->content->first << " ";
//
//			if ( it.node->parent )
//				std::cout << "parent: " << it.node->parent->content->first << " ";
//
//			std::cout << std::endl;
//		}
//
//		mp.erase( itavl );
//		std::cout << std::endl;
//	}

}

