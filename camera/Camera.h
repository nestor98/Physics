#pragma once
#include "SFML/Graphics.hpp"
class Camera : public sf::View
{
	bool dragging = false;
	sf::Vector2i lastMousePos;

	float m_zoom = 1.0f;
public:
	Camera(const sf::View& v);
	void moveByMouse(const sf::Vector2i& pos);
	void resetDrag();

	void zoom(const float& factor);
};

