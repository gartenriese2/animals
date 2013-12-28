#include <time.h>
#include <cstdlib>

#include "tournament.hpp"

int main () {

	srand(time(NULL));
	
	Tournament t;
	t.startRandomBattles();
	
	return 0;

}
