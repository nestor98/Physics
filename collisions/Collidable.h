#pragma once
#include <optional>
#include "../utils/utils.h"
//#include "SFML/Graphics.hpp"

struct Collision {
	float dist;
	sf::Vector2f n;
};

class Collidable {
protected:
	sf::Vector2f pos;
public:
	virtual bool collides(const Collidable& other) = 0;
	virtual std::optional<Collision> collision(const Collidable& other) = 0;
};