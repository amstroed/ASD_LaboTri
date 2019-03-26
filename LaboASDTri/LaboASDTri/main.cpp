
#include <cstdlib>
#include <iostream>
#include "sortings.h"


using namespace std;

int main() {
	vector<string> test{ "pierre", "gilles", "lisa", "frank", "eric", "alex" , "albert" };
	quickSort(test, test.begin(), test.end() - 1);
	return EXIT_SUCCESS;
}

