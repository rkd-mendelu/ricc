#include <iostream>
#include <cassert>

#include "util/variant.hpp"

using namespace nonstd;

int main()
{
    std::string hello = "hello, world"; 

    variant< char, int, long, std::string > var;
    
    var =  'v' ; assert( get<  0 >( var ) == 'v' );
                 assert( get<char>( var ) == 'v' );
    var =   7  ; assert( get<int >( var ) ==  7  );
    var =  42L ; assert( get<long>( var ) == 42L );    
    var = hello; assert( get<std::string>( var ) == hello );
	return 0;
}