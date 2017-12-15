#include "lib/leftist.h"
#include "lib/skew.h"
#include "lib/stl.h"
#include "lib/binomial.h"
#include "lib/test.h"

int main(int argc, char **argv) {
	srand(time(NULL));
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}