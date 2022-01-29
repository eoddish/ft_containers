/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tempmain.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 00:32:11 by eoddish           #+#    #+#             */
/*   Updated: 2022/01/29 01:11:03 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.hpp"
#include "map.hpp"
#include <vector>
#include <unistd.h>
#include <map>

class B {
public:
    char *l;
    int i;
    B():l(nullptr), i(1) {};
    B(const int &ex) {
        this->i = ex;
        this->l = new char('a');
    };
    virtual ~B() {
        delete this->l;
        this->l = nullptr;
    };
};

class A : public B {
public:
    A():B(){};
    A(const B* ex){
        this->l = new char(*(ex->l));
        this->i = ex->i;
        if (ex->i == -1) throw "n";
    }
    ~A() {
        delete this->l;
        this->l = nullptr;
    };

};

template <typename T>
std::vector<int> assign_std_test(ft::vector<T> vector) {
    std::vector<int> v;
    std::vector<int> tmp;
    vector.assign(3, 3);
    tmp.assign(40000000, 1);
    vector.assign(tmp.begin(), tmp.end());
    for (size_t i = 0; i < tmp.size(); ++i)
        v.push_back(vector[i]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    return v;
}

template <typename T>
std::vector<int> resize_test(ft::vector<T> vector1) {
    std::vector<int> v;
	ft::vector<T> vector;
    //vector.assign(99000, 1);
    vector.resize(50000);
    vector1[1] = 0;
 	//vector.reserve(50000000);
	vector.resize(70000);
/*
write(1, "*\n", 2);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    vector.resize(153000000, T());
write(1, "*\n", 2);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    v.push_back(vector[65]);
*/
    return v;
}

template <typename T>
std::vector<int> iterator_test(ft::vector<T> vector) {
    typename ft::vector<T>::iterator it;
    std::vector<int> v;
    for (int i = 0; i < 10; ++i)
        vector.push_back(i);
    it = vector.begin();
    v.push_back(*(++it));
    v.push_back(*(--it));
    v.push_back(*(it + 1));
    it += 1;
    v.push_back(*(it - 1));
    it -= 1;
    v.push_back(*it);
    return v;
}

template <typename T>
std::vector<int> constructor_std_test(ft::vector<T> vecto) {
    (void)vecto;
    std::vector<int> v;
    ft::vector<T> vector(3, 3);
    std::vector<int> tmp(10000000, 4);
    ft::vector<int> tmp2(tmp.begin(), tmp.end());
    v.push_back(tmp2.size());
    v.push_back(tmp2.capacity());
    for (size_t i = 0; i < tmp.size(); ++i)
        v.push_back(tmp2[i]);
    return v;
}

template <typename T>
std::vector<int> rend_test(ft::vector<T> vector) {
    std::vector<int> v;
    vector.assign(1000, 1);
    v.push_back(*(vector.rend() - 1));
    v.push_back(*(vector.rend() - 2));
    return v;
}

	template <typename T>
	std::vector<int> empty_test(ft::vector<T> vector) {
			std::vector<int> v;
			vector.assign(1000, 1);
			v.push_back(vector.empty());
			return v;
		}

bool fncomp (char lhs, char rhs) {return lhs<rhs;}

	struct classcomp {
  	bool operator() (const char& lhs, const char& rhs) const
  {return lhs<rhs;}
};

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

	std::cout << "vct1 front: " << vct1.front() << " ";
	std::cout << "vct1 back: " << vct1.back() << std::endl;

	vct1.push_back( 3 );
	std::cout << "vct1 front: " << vct1.front() << " ";
	std::cout << "vct1.back: " << vct1.back() << std::endl;

	vct1.push_back( 5 );
	std::cout << "vct1 begin: " << *vct1.begin() << " ";
	std::cout << "vct1 end: " << *vct1.end() << std::endl;
	
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

	//===== IS_INTEGRAL ===== 	

	std::cout << "float: " << ft::is_integral<float>::value << std::endl;
	std::cout << "intptr_t: " << ft::is_integral<intptr_t>::value << std::endl;
 	std::cout << "i is odd: " << is_odd(i) << std::endl;

  if ( ft::is_integral<int>() )
    std::cout << "int is an integral type" << std::endl;

  // same result as:
  if ( ft::is_integral<int>::value )
    std::cout << "int is an integral type" << std::endl;


	//===== EQUAL ===== 	

	std::cout << ft::equal(vct2.begin(), vct2.end(), vct4.begin() ) << std::endl;

	std::cout << ft::equal(vct2.begin(), vct2.end(), vct3.begin() ) << std::endl;

	
	//===== LEXICOGRAPHICAL_COMPARE ===== 	

	char foo[]="Apple";
	char bar[]="apartment";

	std::cout << "Using default comparison (operator<): ";
	std::cout << ft::lexicographical_compare(foo,foo+5,bar,bar+9);
	std::cout << '\n';
	
	std::cout << "Using mycomp as comparison object: ";
	std::cout << ft::lexicographical_compare(foo,foo+5,bar,bar+9,mycomp);
	std::cout << '\n';

	//===== PAIR =====

	ft::pair <std::string,double> product1;                     // default constructor
	ft::pair <std::string,double> product2 ("tomatoes",2.30);   // value init
	ft::pair <std::string,double> product3 (product2);          // copy constructor

	//===== MAKE_PAIR =====
	
	product1 = ft::make_pair(std::string("lightbulbs"),0.99);   // using make_pair (move)
	
	product2.first = "shoes";                  // the type of first is string
	product2.second = 39.90;                   // the type of second is double
	
	std::cout << "The price of " << product1.first << " is $" << product1.second << '\n';
	std::cout << "The price of " << product2.first << " is $" << product2.second << '\n';
	std::cout << "The price of " << product3.first << " is $" << product3.second << '\n';

	ft::pair <int,int> foo1;
	ft::pair <int,int> bar1;
	
	foo1 = ft::make_pair (10,20);
	bar1 = ft::make_pair (26, 39); // ok: implicit conversion from pair<double,char>
	
	std::cout << "foo1: " << foo1.first << ", " << foo1.second << '\n';
	std::cout << "bar1: " << bar1.first << ", " << bar1.second << '\n';

	//===== REVERSE_ITERATOR =====

	ft::vector<int> vct6 (5);  // 5 default-constructed ints

	ft::vector<int>::reverse_iterator rit = vct6.rbegin();

	i=0;
  for (rit = vct6.rbegin(); rit!= vct6.rend(); ++rit)
    *rit = ++i;

	std::cout << "vct6 contains:";
	for (ft::vector<int>::iterator it = vct6.begin(); it != vct6.end(); ++it)
	std::cout << ' ' << *it;
	std::cout << '\n';

	// ===== MAX_SIZE =====

	std::cout << "vct6 max_size: " << vct6.max_size() << std::endl;

	// ===== RESIZE =====

	ft::vector<int> vct7;
	
	// set some initial content:
	for (i=1;i<10;i++) vct7.push_back(i);
	
	vct7.resize(5);
	vct7.resize(8,100);
	vct7.resize(12);
	
	std::cout << "myvector contains:";
	for (size_t j=0;j<vct7.size();j++)
	  std::cout << ' ' << vct7[j];
	std::cout << '\n';

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
	vct9.reserve(100);   // this is the only difference with foo above
	std::cout << "making vct9 grow:\n";
	for (int j=0; j<100; ++j) {
		vct9.push_back(j);
		if (sz!=vct9.capacity()) {
			sz = vct9.capacity();
			std::cout << "capacity changed: " << sz << '\n';
	  }
  }
 
	try {
	    // vector throws a length_error if resized above max_size
	    vct8.resize(vct8.max_size()+1);
	  }
	  catch (const std::length_error& le) {
		  std::cerr << "Length error: " << le.what() << '\n';
	  }

//=====AT=====

	std::cout << "vct1.at( 0 ): " << vct1.at( 0 ) << std::endl;
	std::cout << "vct1.at( 2 ): " << vct1.at( 2 ) << std::endl;
  	try {
  	  vct8.at(20)=100;      // vector::at throws an out-of-range
  	}
  	catch (const std::out_of_range& oor) {
  	  std::cerr << "Out of Range error: " << oor.what() << '\n';
  }

//=====ASSIGN=====

	ft::vector<int> vct10;
	ft::vector<int> vct11;
	ft::vector<int> vct12;
	vct10.assign ((size_t )7,100);             // 7 ints with a value of 100
	
	ft::vector<int>::iterator it;
	it=vct10.begin()+1;
	
	vct11.assign (it,vct10.end()-1); // the 5 central values of first
	
	int myints[] = {1776,7,4};
	vct12.assign (myints,myints+3);   // assigning from array.
	
	std::cout << "Size of vct10: " << int (vct10.size()) << '\n';
	std::cout << "Size of vct11: " << int (vct11.size()) << '\n';
	std::cout << "Size of vct12: " << int (vct12.size()) << '\n';
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
	
	// "it1" no longer valid, get a new one:
	it1 = vct13.begin();
	
	ft::vector<int> vct14 ((size_t) 2,400);
	vct13.insert (it1+2,vct14.begin(),vct14.end());
	
	int myarray [] = { 501,502,503 };
	vct13.insert (vct13.begin(), myarray, myarray+3);
	
	std::cout << "vct13 contains:";
	ft_print( vct13 );


//=====ERASE=====

	ft::vector<int> vct15;
	
	// set some values (from 1 to 10)
	for (int i=1; i<=10; i++) vct15.push_back(i);

	std::cout << "vct15 contains:";
	ft_print( vct15 );
	
	// erase the 6th element
	vct15.erase (vct15.begin()+5);

	std::cout << "vct15 contains:";
	ft_print( vct15 );
	
	// erase the first 3 elements:
	vct15.erase (vct15.begin(),vct15.begin()+3);
	
	std::cout << "vct15 contains:";
	ft_print( vct15 );
	
//=====SWAP=====

	ft::vector<int> vct16(  3,100 );   // three ints with a value of 100
	
	ft::vector<int> vct17( 5,200 );   // five ints with a value of 200
	
	vct16.swap(vct17);
	
	std::cout << "vct16 contains:";
	ft_print( vct16 );
	
	std::cout << "vct17 contains:";
	ft_print( vct17 );


//=====CLEAR======

	ft::vector<int> vct18;
	vct18.push_back (100);
	vct18.push_back (200);
	vct18.push_back (300);
	
	std::cout << "vct18 contains:";
	for (unsigned i=0; i<vct18.size(); i++)
	  std::cout << ' ' << vct18[i];
	std::cout << '\n';
	
	vct18.clear();
	vct18.push_back (1101);
	vct18.push_back (2202);
	
	std::cout << "vct18 contains:";
	for (unsigned i=0; i<vct18.size(); i++)
	  std::cout << ' ' << vct18[i];
	std::cout << '\n';

//=====GET_ALLOCATOR=====

	ft::vector<int> vct19;
	
	int * p;
	
	// allocate an array with space for 5 elements using vector's allocator:
	p = vct19.get_allocator().allocate(5);
	
	// construct values in-place on the array:
	for (i=0; i<5; i++) vct19.get_allocator().construct(&p[i],i);
	
	std::cout << "The allocated array contains:";
	for (i=0; i<5; i++) std::cout << ' ' << p[i];
	std::cout << '\n';
	
	// destroy and deallocate:
	for (i=0; i<5; i++) vct19.get_allocator().destroy(&p[i]);
	vct19.get_allocator().deallocate(p,5);

//=====RELATIONAL OPERATORS=====

	ft::vector<int> vct20 ((size_t)3,100);   // three ints with a value of 100
	ft::vector<int> vct21 ((size_t)2,200);   // two ints with a value of 200
	
	if (vct20==vct21) std::cout << "vct20 and vct21 are equal\n";
	if (vct20!=vct21) std::cout << "vct20 and vct21 are not equal\n";
/*	if (vct20< vct21) std::cout << "vct20 is less than vct21\n";
	if (vct20> vct21) std::cout << "vct20 is greater than vct21\n";
	if (vct20<=vct21) std::cout << "vct20 is less than or equal to vct21\n";
	if (vct20>=vct21) std::cout << "vct20 is greater than or equal to vct21\n";
*/
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

	ft::vector<int> vct23 ((size_t)2,200);        // vector with 2 elements
	ft::stack<int> stc1;                    // empty stack
	ft::stack<int,ft::vector<int> > stc2 ( vct23 );

//=====EMPTY=====

	std::cout << "stc1 is empty: " << stc1.empty() << '\n';
	std::cout << "stc2 is empty: " << stc2.empty() << '\n';


//=====SIZE======

	std::cout << "size of stc1: " << stc1.size() << '\n';
	std::cout << "size of stc2: " << stc2.size() << '\n';

//=====TOP======
	//std::cout << "top of stc1: " << stc1.top() << '\n';

	stc2.push( 300 );
	std::cout << "top of stc2: " << stc2.top() << '\n';

//=====PUSH=====

	ft::stack<int> stc3;
	
	for (int j=0; j<5; ++j) stc3.push(j);

//=====POP=====
	
	std::cout << "Popping out elements...";
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

	std::cout << "**" << std::endl;
	map4.insert( map4.begin(), ft::make_pair( 'y', 3 ) );

	std::cout << "map4: " << std::endl;
	for( ft::map<char, int>::iterator it = map4.begin(); it != map4.end(); ++it )
		std::cout << (*it).first << " " << (*it).second << std::endl; 

	//===== ERASE =====

	map4.erase( map4.begin() );
	map4.erase( 'z' );

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

/*
	empty_test( ft::vector<int>() );
	rend_test( vct1 );
	std::cout << "vct15 contains: ";
	ft_print( vct15 );
	std::cout << *(vct15.rend() - 1) << std::endl;
	std::cout << *(vct15.rend() - 2) << std::endl;
	std::cout << *(vct15.begin() += 1 ) << std::endl;
	std::cout << *(vct15.begin() += 2 ) << std::endl;
	constructor_std_test(vct15);


	 iterator_test(vct15);
	resize_test(vct15); 
	assign_std_test( vct15);


	vector<int>::const_iterator it = vct15.begin();
	ft::vector<int> vct30;
	std::cout << "vct30 contains: ";
	ft_print( vct30 );
	vct30.insert( vct30.end(), vct15.begin(),vct15.end() ); 
	std::cout << "vct30 contains: ";
	ft_print( vct30 );
	vct30.insert( vct30.end(), vct15.rbegin(),vct15.rend() ); 
	std::cout << "vct30 contains: ";
	ft_print( vct30 );
	ft::vector<int>::reverse_iterator itt(vct30.rbegin());
	ft::vector<int>::const_reverse_iterator itte(vct30.rend());
	ft::vector<int>::const_iterator itti(vct30.begin());
	std::cout << (itt != itte) << std::endl;
	itte--;
	std::cout << itti[0] << std::endl;
	ft::vector<int>::const_iterator ittk;
	ittk = itti;
	std::cout << ittk[0] << std::endl;
	std::cout << ittk[0] << std::endl;
	*/
	std::map<int,std::string> map10;
	ft::map<int,std::string> map11;
	std::cout << map10.max_size() << std::endl;
	std::cout << map11.max_size() << std::endl;
	
	std::map<int,char> map12;
	 ft::map<int, char> map13;
	std::cout << map12.max_size() << std::endl;
	std::cout << map13.max_size() << std::endl;
	map13.insert(map13.begin(), ft::make_pair( 1, 'a' ));
	map13.insert(map13.end(), ft::make_pair( 2, 'a' ));
	for( ft::map<int,char>::iterator it = map13.begin(); it != map13.end(); ++it ) {

		std::cout << it->first << std::endl;
	}

	 ft::map<int, char> const map16( map13.begin(), map13.end() );
	ft::map<int,char>::const_iterator ittt = map13.begin();
	//ittt->second = 'c';
	std::cout << ittt->second << std::endl;
	
	std::map<int,float> map14;
	ft::map<int, float> map15;
	std::cout << map14.max_size() << std::endl;
	std::cout << map15.max_size() << std::endl;

	std::cout << std::endl;

    std::cout << (typeid(std::vector<int>::const_iterator::iterator_category).name()) << std::endl;
    std::cout << (typeid(std::vector<int>::const_iterator::value_type).name()) << std::endl;
    std::cout << (typeid(std::vector<int>::const_iterator::difference_type).name()) << std::endl;
    std::cout << (typeid(std::vector<int>::const_iterator::iterator_type).name()) << std::endl;
    std::cout << (typeid(std::vector<int>::const_iterator::pointer).name()) << std::endl;
    std::cout << (typeid(std::vector<int>::const_iterator::reference).name()) << std::endl;
    std::cout << (typeid(std::vector<int>::const_reverse_iterator::iterator_category).name()) << std::endl;
    std::cout << (typeid(std::vector<int>::const_reverse_iterator::value_type).name()) << std::endl;
    std::cout << (typeid(std::vector<int>::const_reverse_iterator::difference_type).name()) << std::endl;
    std::cout << (typeid(std::vector<int>::const_reverse_iterator::pointer).name()) << std::endl;
    std::cout << (typeid(std::vector<int>::const_reverse_iterator::reference).name()) << std::endl;

	std::cout << std::endl;

    std::cout << (typeid(ft::vector<int>::const_iterator::iterator_category).name()) << std::endl;
    std::cout << (typeid(ft::vector<int>::const_iterator::value_type).name()) << std::endl;
    std::cout << (typeid(ft::vector<int>::const_iterator::difference_type).name()) << std::endl;
    std::cout << (typeid(ft::vector<int>::const_iterator::iterator_type).name()) << std::endl;
    std::cout << (typeid(ft::vector<int>::const_iterator::pointer).name()) << std::endl;
    std::cout << (typeid(ft::vector<int>::const_iterator::reference).name()) << std::endl;
    std::cout << (typeid(ft::vector<int>::const_reverse_iterator::iterator_category).name()) << std::endl;
    std::cout << (typeid(ft::vector<int>::const_reverse_iterator::value_type).name()) << std::endl;
    std::cout << (typeid(ft::vector<int>::const_reverse_iterator::difference_type).name()) << std::endl;
    std::cout << (typeid(ft::vector<int>::const_reverse_iterator::pointer).name()) << std::endl;
    std::cout << (typeid(ft::vector<int>::const_reverse_iterator::reference).name()) << std::endl;


	ft::map<int, int> mp;
	 std::vector<int> v;
    v.push_back(mp.erase(3));

    for (int i = 0, j = 0; i < 30; ++i, ++j)
        mp.insert(ft::make_pair(i, j));
/*    ft::map<int, int>::iterator it25 = mp.begin();
    v.push_back(it25->first);
    v.push_back(mp.erase(-5));
    v.push_back(mp.size());
    v.push_back(mp.erase(0));
    v.push_back(mp.size());

    it25 = mp.begin();
    v.push_back(it25->first);
*/
    ft::map<int, int>::iterator it4 = mp.begin();

	
		std::cout << std::endl;

    for (; it4 != mp.end(); it4 = mp.begin()) {

	for( ft::map<int,int>::iterator it = mp.begin(); it != mp.end(); ++it ) {


		std::cout << it->first << " " << it.node->bf << " ";

		if ( it.node->left )
		std::cout << "L: " << it.node->left->content->first << " ";

		if ( it.node->right )
		std::cout << "R: " << it.node->right->content->first << " ";

		if ( it.node->parent )
		std::cout << "parent: " << it.node->parent->content->first << " ";


		std::cout << std::endl;


	}

        mp.erase(it4->first);
		std::cout << std::endl;
		}

     ft::map<int, int>::iterator it2 = mp.end();

    it2--;


    v.push_back(mp.erase(30  - 1));
    v.push_back(mp.size());
    ft::map<int, int> mp2;
    for (int i = 0, j = 0; i < 10 ; ++i, ++j)
        mp2.insert(ft::make_pair(i, j));
    mp2.erase(2);
    mp2.erase(7);
     ft::map<int, int>::iterator it3 = mp2.begin();
    for (; it3 != mp2.end(); ++it3) {
        v.push_back(it3->first);
        v.push_back(it3->second);
    }

	int _ratio = 1;
/*
	ft::vector<int> vector1;

    vector1.assign(9900 * _ratio, 1);
    vector1.resize(5000 * _ratio);
    vector1.reserve(5000 * _ratio);
    std::cout << (vector1.size()) << std::endl;
    std::cout << (vector1.capacity()) << std::endl;
    vector1.resize(7000 * _ratio);

    std::cout << (vector1.size()) << std::endl;
    std::cout << (vector1.capacity()) << std::endl;
    vector1.resize(15300 * _ratio, int());

    std::cout << (vector1.size()) << std::endl;
    std::cout << (vector1.capacity()) << std::endl;

    std::cout << (vector1[65]) << std::endl;

	std::cout << std::endl;
   	std::vector<int> vector2;
 
    vector2.assign(9900 * _ratio, 1);
    vector2.resize(5000 * _ratio);
    vector2.reserve(5000 * _ratio);
    std::cout << (vector2.size()) << std::endl;
    std::cout << (vector2.capacity()) << std::endl;
    vector2.resize(7000 * _ratio);

    std::cout << (vector2.size()) << std::endl;
    std::cout << (vector2.capacity()) << std::endl;
    vector2.resize(15300 * _ratio, int());

    std::cout << (vector2.size()) << std::endl;
    std::cout << (vector2.capacity()) << std::endl;

    std::cout << (vector2[65]) << std::endl;

  */ 
 /*  	
	std::cout << std::endl;
   	ft::vector<int> vector1;

    vector1.assign(2600 * _ratio, 1);
    std::cout << (*(vector1.insert(vector1.end() - 800 * _ratio, 44))) << std::endl;
    std::cout << (vector1.size()) << std::endl; std::cout << (vector1.capacity()) << std::endl;
    std::unique_ptr<B> k2(new B(3));
    std::unique_ptr<B> k3(new B(4));
    std::unique_ptr<B> k4(new B(-1));
    ft::vector<A> vv;
    ft::vector<B*> v1;

    std::cout << (&(*k2)) << std::endl;
    std::cout << (&(*k3)) << std::endl;
    std::cout << (&(*k4)) << std::endl;
    vv.insert(vv.begin(), v1.begin(), v1.end()); 
        std::cout << vv.size() << std::endl;
        std::cout << (vv.capacity()) << std::endl;

	
	std::cout << std::endl;
   	std::vector<int> vector2;

    vector2.assign(2600 * _ratio, 1);
    std::cout << (*(vector2.insert(vector2.end() - 800 * _ratio, 44))) << std::endl;
    std::cout << (vector2.size()) << std::endl;
    std::cout << (vector2.capacity()) << std::endl;
    std::unique_ptr<B> k5(new B(3));
    std::unique_ptr<B> k6(new B(4));
    std::unique_ptr<B> k7(new B(-1));
    std::vector<A> vvn;
    std::vector<B*> v1n;

    std::cout << (&(*k5)) << std::endl;
    std::cout << (&(*k6)) << std::endl;
    std::cout << (&(*k7)) << std::endl;
    vvn.insert(vvn.begin(), v1n.begin(), v1n.end()); 
        std::cout << vvn.size() << std::endl;
        std::cout << (vvn.capacity()) << std::endl;
*/

std::cout << std::endl;	
    ft::vector<int> vector5;
    ft::vector<int> tmp1;
    tmp1.assign(2600 * _ratio, 1);
    vector5.assign(4200 * _ratio, 1);
    vector5.insert(vector5.end() - 1000 * _ratio, tmp1.begin(), tmp1.end());
    std::cout << (vector5[3]) << std::endl;
    std::cout << (vector5.size()) << std::endl;
    std::cout << (vector5.capacity()) << std::endl;


	std::cout << std::endl;	
    std::vector<int> vector6;
    std::vector<int> tmp2;
    tmp2.assign(2600 * _ratio, 1);
    vector6.assign(4200 * _ratio, 1);
    vector6.insert(vector6.end() - 1000 * _ratio, tmp2.begin(), tmp2.end());
    std::cout << (vector6[3]) << std::endl;
    std::cout << (vector6.size()) << std::endl;
    std::cout << (vector6.capacity()) << std::endl;

	std::cout << std::endl;
    ft::vector<int> vector7;
    ft::vector<int> tmp3;
    tmp3.assign(2600 * _ratio, 1);
    vector7.assign(2200 * _ratio, 1);
    vector7.insert(vector7.end() - 1400 * _ratio, tmp3.begin(), tmp3.end());
    std::cout << (vector7[3]) << std::endl;
    std::cout << (vector7.size()) << std::endl;
    std::cout << (vector7.capacity()) << std::endl;


	std::cout << std::endl;
    std::vector<int> vector8;
    std::vector<int> tmp4;
    tmp4.assign(2600 * _ratio, 1);
    vector8.assign(2200 * _ratio, 1);
    vector8.insert(vector8.end() - 1400 * _ratio, tmp4.begin(), tmp4.end());
    std::cout << (vector8[3]) << std::endl;
    std::cout << (vector8.size()) << std::endl;
    std::cout << (vector8.capacity()) << std::endl;
	
	std::cout << std::endl;
	ft::vector<int> vector100;
    std::vector<int> v100;
    vector100.assign(2600 * _ratio, 1);
    v100.push_back(*(vector100.insert(vector100.end() - 800 * _ratio, 44)));
    v100.push_back(vector100.size());
    v100.push_back(vector100.capacity());
    std::unique_ptr<B> k12(new B(3));
    std::unique_ptr<B> k13(new B(4));
    std::unique_ptr<B> k14(new B(-1));
    ft::vector<A> vv100;
    ft::vector<B*> v1100;

    v1100.push_back(&(*k12));
    v1100.push_back(&(*k13));
    v1100.push_back(&(*k14));
    try { vv100.insert(vv100.begin(), v1100.begin(), v1100.end()); }
    catch (...) {
        v100.push_back(vv100.size());
        v100.push_back(vv100.capacity());
    }

	std::cout << std::endl;
    std::vector<int> vector200;
    std::vector<int> v200;
    vector200.assign(2600 * _ratio, 1);
    v200.push_back(*(vector200.insert(vector200.end() - 800 * _ratio, 44)));
    v200.push_back(vector200.size());
    v200.push_back(vector200.capacity());
    std::unique_ptr<B> k22(new B(3));
    std::unique_ptr<B> k23(new B(4));
    std::unique_ptr<B> k24(new B(-1));
    std::vector<A> vv200;
    std::vector<B*> v1200;

    v1200.push_back(&(*k22));
    v1200.push_back(&(*k23));
    v1200.push_back(&(*k24));
    try { vv200.insert(vv200.begin(), v1200.begin(), v1200.end());  }
    catch (...) {
        v200.push_back(vv200.size());
        v200.push_back(vv200.capacity());
    }

	for( std::vector<int>::iterator prit = v100.begin(); prit != v100.end(); ++prit )
	std::cout << *prit << std::endl;

	std::cout << std::endl;

	for( std::vector<int>::iterator prit = v200.begin(); prit != v200.end(); ++prit )
	std::cout << *prit << std::endl;
}
