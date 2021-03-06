#include "RNG.h"
#include "utils.h"
namespace rng {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(0.0, 1.0);


	float rand01() { 
		return dis(gen);
	}

	float rand(float min, float max) { // random float between min and max, included
		return rand01() * (max - min) + min;
	}

	int rand(int min, int max) { // random int between min and max, included
		//std::uniform_int_distribution<int> dis(min, max);
		//return dis(gen);
		return std::min(int(rand01() * (1 + max - min) + min), max);
	}

	int randWithIntDis(int min, int max) { // random int between min and max, included
		std::uniform_int_distribution<int> dis(min, max);
		return dis(gen);
	}

	int randMax(int max) { // random int up to max, included
		return rand(0, max);
	}

	sf::Vector2f rand2f()
	{
		float th = rand(0.0f, 2.0f * utils::PI);
		return sf::Vector2f(cos(th),sin(th));
	}
	sf::Color randColor()
	{
		return sf::Color(rand(0,255), rand(0, 255), rand(0, 255));
	}
}