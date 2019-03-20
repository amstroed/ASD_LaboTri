
#include <cstdlib>
#include <iostream>
#include "sortings.h"


using namespace std;

int main() {
	vector<string> test{ "alex", "frank", "lisa", "eric", "albert", "gilles", "pierre" };
	selectionSort(test);
	return EXIT_SUCCESS;
}

