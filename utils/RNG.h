#pragma once

#include <random>

namespace rng {

	float rand01();// random real between 0 and 1

	float rand(float min, float max);// random real between min and max, included

	int rand(int min, int max);
	int randWithIntDis(int min, int max);
	// random int between min and max, included

	int randMax(int max);// random int up to max, included

}
