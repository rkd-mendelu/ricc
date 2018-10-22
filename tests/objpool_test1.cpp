#include <iostream>

#include "util/ObjectPool.hpp"
#include "lex/Token.hpp"

using namespace std;

int main()
{
	TPJparser::ObjectPool<TPJparser::Token> my_pool;

	if (my_pool.getSize() != 0) {
		cerr << "getSize != 0" << endl;
		return 1;
	}

	my_pool.show();
	TPJparser::Token& token1 = my_pool.getItem();
	my_pool.show();
	TPJparser::Token& token2 = my_pool.getItem();
	my_pool.show();
	TPJparser::Token& token3 = my_pool.getItem();
	my_pool.show();
	TPJparser::Token& token4 = my_pool.getItem();
	my_pool.show();
	TPJparser::Token& token5 = my_pool.getItem();
	my_pool.show();

	if (token1.getID() != 0) {
		cerr << "token1 has wrong ID" << endl;
	}

	if (my_pool.getSize() != 5) {
		cerr << "getSize != 5 but " << my_pool.getSize() << " after 5x getItem()" << endl;
		return 1;
	}

	/************************************************************/

	if (token1.getID() != 0) {
		cerr << "token1 has wrong ID" << endl;
		return 1;
	}

	if (token2.getID() != 1) {
		cerr << "token2 has wrong ID" << endl;
		return 1;
	}

	if (token3.getID() != 2) {
		cerr << "token3 has wrong ID" << endl;
		return 1;
	}

	if (token4.getID() != 3) {
		cerr << "token4 has wrong ID" << endl;
		return 1;
	}

	if (token5.getID() != 4) {
		cerr << "token5 has wrong ID" << endl;
		return 1;
	}

	/************************************************************/



	return 0;
}