#pragma once

#include <iostream>

#include <list>

#include "SFML/Graphics.hpp"

namespace utils {
	constexpr float PI = 3.14159265f;

	float distanceToLine(sf::Vector2f l0, sf::Vector2f lf, sf::Vector2f p);
	float parseFloat(std::istringstream& is, const char sep);
	int parseInt(std::istringstream& is, const char sep);
	sf::Color parseColor(std::istringstream& is, const char sep);
	float stopDistance(const float& speed, const float& deceleration);

	template <class T>
	bool contains(std::list<T> l, T v);

	sf::Vector2f mousePosition2f(const sf::RenderWindow& window);
	sf::Vector2i clampMouseCoord(const sf::Vector2f& pos, const sf::RenderTarget& window);

	sf::Vector2i clampMouseCoord(const sf::RenderWindow& window);

	float dot(const sf::Vector2f a, const sf::Vector2f b);

	int positiveMod(int i, int n);

	int clamp(int val, int min, int max);

	float clampf(float val, float min, float max);

	float degrees(float radians);

	sf::Vector2f polarToCarthesian(float radius, float angle);

	// Clamp + valor absoluto
	float clampAbs(const float& val, const float& limit);

	bool inRange(float value, float min, float max);

	sf::Vector2f clampAbs(const sf::Vector2f& val, const float& limit);

	float lerp(float x, float y, float z); // z must be between 0 and 1. Returns x if 0, z if 1, linearly interpolated if in between
	sf::Color lerp(sf::Color x, sf::Color y, float z); // Same for colors (rgb interpolation)

	sf::Vector2f toVector2f(const sf::Vector2i& v);

	sf::IntRect floatToIntRect(const sf::FloatRect& fr);

	// Distance between the points p1 and p2
	float distance(const sf::Vector2f& p1, const sf::Vector2f& p2);

	// Length (modulo) of vector v
	float length(const sf::Vector2f& v);

	sf::Vector2i spritesForFloatRect(const sf::FloatRect& rect); // returns the number of sprites horizontally and vertically for a texture with floatRect

	// Scale sprite to full window size
	void scaleToFullScreen(sf::Sprite& s, const float& windowHeight);

	// Scale sprite to full window size
	void scaleToFullScreen(sf::Sprite& s, const sf::RenderWindow& window);

	sf::IntRect texRectInGrid(const sf::Texture& tex, int nX, int nY, int idxX, int idxY); // Returns the texRect of index idxX, idxY for tex assuming its in a grid of nX by nY
	sf::IntRect texRectInGrid(const sf::Texture& tex, const sf::Vector2i& nSprites, const sf::Vector2i& idx); // same with vectors

	// Post: sprite.width = width in world
	void setWidth(sf::Sprite& s, const float& width);

	void setHeight(sf::Sprite& s, const float& h);

	void scaleToFullScreenRatio(sf::Sprite& s, const sf::RenderWindow& window, const float& verticalRatio);

	sf::Vector2f globalToRelative(const sf::Vector2f& global, const sf::RenderWindow& window);


	sf::Vector2f relativeToGlobal(sf::Vector2f relative, const sf::RenderWindow& window);


	sf::IntRect relativeToGlobalTextureRect(const sf::FloatRect& relative, const sf::Texture& tex);

	void scaleSpriteToTextRect(sf::Sprite& sprite);

	// Sets the origin to the center of the sprite
	void centerOrigin(sf::Sprite& s);

	template <typename I, typename O>
	O to(I in) {
		return static_cast<O>(in);
	}

	template <typename T>
	sf::Vector2i toVector2i(const sf::Vector2<T>& v);

	template <typename T>
	sf::Vector2f toVector2f(const sf::Vector2<T>& v);

	template <typename T1, typename T2>
	sf::Vector2<T1> toVector2(sf::Vector2<T2> v) {
		return sf::Vector2<T1>(v.x, v.y);
	}



	template<typename T>
	inline sf::Vector2f toVector2f(const sf::Vector2<T>& v)
	{
		return sf::Vector2f(v.x, v.y);
	}

	template <typename T>
	sf::Vector2u toVector2u(const sf::Vector2<T>& v);
}


/*template <typename T>
std::string to_string(const sf::Vector2<T>& v);
template <typename T>
std::ostream& operator<<(std::ostream& os, const sf::Vector2<T>& v);
*/

template<typename T>
inline std::string to_string(const sf::Vector2<T>& v)
{
	return std::to_string(v.x) + " " + std::to_string(v.y);
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const sf::Vector2<T>& v)
{
	return os << to_string(v);
}



inline std::string to_string(const sf::Color& c)
{
	return std::to_string(c.r) + " " + std::to_string(c.g) + " " + std::to_string(c.b);
}


inline std::ostream& operator<<(std::ostream& os, const sf::Color& c)
{
	return os << to_string(c);
}