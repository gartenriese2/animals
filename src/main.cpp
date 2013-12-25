#include <time.h>
#include <cstdlib>

#include "tournament.hpp"

int main () {

	srand(time(NULL));
	
	Tournament t;
	t.startWithFirestarter();
	
	return 0;

}
