#include "CircleCollider.h"

const sf::Vector2f& CircleCollider::getPos() const
{
	return p;
}

void CircleCollider::setPos(const sf::Vector2f& pos)
{
	p = pos;
}

float CircleCollider::getR() const
{
	return r;
}

void CircleCollider::setR(float _r)
{
	r = _r;
}

CircleCollider::CircleCollider(const sf::Vector2f& pos, float rad) 
	: p(pos), r(rad)
{
}

bool CircleCollider::collides(const CircleCollider& other)
{
	return utils::length(p - other.getPos()) >= (r + other.getR());
}

bool CircleCollider::collides(const Collidable& other)
{
	std::cerr << "UNIMPLEMENTED\n";
	return false;
}

std::optional<Collision> CircleCollider::collision(const Collidable& other)
{
	std::cerr << "Not implemented\n";
	return {};
}

std::optional<Collision> CircleCollider::collision(const CircleCollider& other)
{

	sf::Vector2f n = other.getPos() - p;
	float dist = utils::length(n);
	float depth = dist - (r + other.getR());
	if (depth > 0) return { Collision{depth, n / utils::length(n)} };
	else return {};
}

void handleCollision(std::vector<CircleCollider>& circles, size_t i, size_t j, const Collision& c) {
	// Algo así:
	//circles[i].move(c.n * c.dist);
	//circles[j].move(-c.n * c.dist);
}

void collideCircles(std::vector<CircleCollider>& circles) {
	for (size_t i = 0; i < circles.size(); i++)
		for (size_t j = i + 1; j < circles.size(); j++) {
			auto c = circles[i].collision(circles[j]);
			if (c) handleCollision(circles, i, j, *c);
		}
}


void destroyCollisions(std::vector<CircleCollider>& circles) {
	std::vector<size_t> idxs;
	for (size_t i = 0; i < circles.size(); i++)
		for (size_t j = i + 1; j < circles.size(); j++) {
			if (circles[i].collides(circles[j])) {
				idxs.push_back(i); idxs.push_back(j);
				break;
			}
		}
	for (size_t i = idxs.size() - 1; i >= 0; i++)
		circles.erase(circles.begin()+idxs[i]);
}

CollidableCircle::CollidableCircle(const sf::Vector2f& _pos, float _r)
	: CircleCollider(_pos, _r), CircleShape(_r)
{
	setPosition(_pos);
}

void CollidableCircle::setPos(const sf::Vector2f& pos)
{
	CircleCollider::setPos(pos);
	CircleShape::setPosition(pos);
}

void CollidableCircle::setR(float _r)
{
	CircleCollider::setR(_r);
	CircleShape::setRadius(_r);
}
