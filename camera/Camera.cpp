#include "Camera.h"
#include "../utils/utils.h"
Camera::Camera(const sf::View& v) : sf::View(v)
{
}
void Camera::moveByMouse(const sf::Vector2i& pos)
{
	if (!dragging) {
		dragging = true;
	}
	else {
		sf::Vector2f dif = utils::toVector2f(lastMousePos - pos);
		move(dif * m_zoom);
	}
	lastMousePos = pos;
}

void Camera::resetDrag()
{
	dragging = false;
}

void Camera::zoom(const float& factor)
{
	sf::View::zoom(factor);
	m_zoom *= factor;
}
