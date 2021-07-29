#pragma once
#include "SFML/Graphics.hpp"


namespace qtree {

template <typename T>
struct Point {
	sf::Vector2f p;
	T data;
};



constexpr size_t N_POINTS = 4;
constexpr int MAX_DEPTH = 8; // unused for now

template <typename T>
class QuadTree
{
	std::array<Point<T>, N_POINTS> pts;
	size_t idx = 0;
	sf::FloatRect area;

	int depth;
	
	std::array<std::unique_ptr<QuadTree>, 4> childs; // tL, tR, bL, bR;

	void constructChilds() {
		float w = area.width / 2.0f,
			  h = area.height / 2.0f;
		childs[0] = std::make_unique<QuadTree<T>>(area.left, area.top, w, h); // top left
		childs[1] = std::make_unique<QuadTree<T>>(area.left+w/2.0f, area.top, w, h); // top right
		childs[2] = std::make_unique<QuadTree<T>>(area.left, area.top + h / 2.0f, w, h); // bottom left
		childs[3] = std::make_unique<QuadTree<T>>(area.left + w / 2.0f, area.top + h / 2.0f, w, h); // bottom right
	}

public:
	QuadTree(const sf::FloatRect& _area, int _depth = 0) 
		: area(_area), depth(_depth) {}

	void insert(const Point<T>& p) {
		if (area.contains(p.p)) {
			if (idx < 4) pts[idx++] = p; // we have space
			else { // we dont, subdivide
				constructChilds(); 
				for (size_t i = 0; i < 4; i++) 
					childs[i]->insert(p); // insert p into the appropiate child
			}
		}

	}

	void query() const {

	}
	// TODO: query in circle area


	// Debug function:
#ifdef VISUALIZE_QTREE
	void draw(sf::RenderWindow& window) const;
#endif
};

}


