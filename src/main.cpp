#include <time.h>
#include <cstdlib>

#include "tournament.hpp"

int main () {

	srand(time(NULL));
	
	Tournament t;
	t.startRandomBattles(12,18);
	
	return 0;

}
