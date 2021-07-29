#include <unordered_set>

#include "Orbit.h"
#include "../utils/resource.h"

const float G = 1000.0f;

Body::Body(const sf::Vector2f& _pos, const sf::Vector2f& _vel, float _r) :
	CollidableCircle(_pos, _r), vel(_vel), acc(0, 0), mass(_r * _r)
{
}

void Body::update(sf::Time dT)
{
	float dTs = dT.asSeconds();
	vel += acc * dTs;
	move(vel * dTs);
	//std::cout << vel << "\n";

}

sf::Vector2f Body::getGravityPull(const sf::Vector2f& p) const
{
	sf::Vector2f d = pos-p; // vector between the bodies
	float rSq = utils::dot(d, d); // squared
	d = d / utils::length(d); // direction
	return d * std::min(G * mass / rSq, utils::MAX_ACC); // vector
}

void Body::setAcc(const sf::Vector2f& a)
{
	acc = a;
#ifdef SHOW_ACC
	line.setColor(sf::Color::Red);
	line.setPoints(pos, pos+50.0f*acc);
#endif
}

float Body::getMass() const
{
	return mass;
}

#ifdef SHOW_ACC

const selbaward::Line& Body::getLine() const
{
	return line;
}
#endif // SHOW_ACC




Orbit::Orbit(sf::RenderWindow& _window, size_t nCircles, float radius, float cSize) :
	Visualizer(_window), circleTool(currentR)
{
	for (size_t i = 0; i < nCircles; i++)
	{
		sf::Vector2f pos =rng::rand2f();
		//std::cout << "P: " << pos << "\n";
		float r = rng::rand(cSize/10.0f, cSize);
		sf::Vector2f v = rng::rand2f() * 0.0f + 1.5f*utils::perpendicular(pos);
		v = v / utils::length(v);
		bodies.emplace_back(rng::rand(radius / 10.0f, radius) * pos, 300.0f * v, r);
		//bodies.emplace_back(rng::rand(radius / 10.0f, radius) * pos, 500.0f * v / utils::dot(v, pos), r);
		bodies.back().setFillColor(rng::randColor());
	}
	// Circle tool
	circleTool.setFillColor(sf::Color::Green);
	circleTool.setOrigin(circleTool.getRadius(), circleTool.getRadius());
}


void Orbit::loop() {
	ImGui::SFML::Init(window);
	sf::Clock deltaClock;
	while (window.isOpen()) {

		captureEvents();
		dT = deltaClock.restart();
		// Speed hack:
		dT *= speed;

		update();
		sf::Time e1 = deltaClock.getElapsedTime();
		draw();
		sf::Time e2 = deltaClock.getElapsedTime() - e1;
		if (rng::rand01() > 0.98f) std::cout << "update time: " << e1.asSeconds() << " s. Draw: " << e2.asSeconds() << " s.\n";
	}
	ImGui::SFML::Shutdown();
}




void Orbit::captureEvents()
{
	sf::Event event;
	while (window.pollEvent(event)) {
		ImGui::SFML::ProcessEvent(event);
		Visualizer::captureEvent(event);
		if (!ImGui::IsAnyItemHovered() && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
			if (!addingCircle) {
				addingCircle = true;
				circleTool.setRadius(currentR);
			}
			else {
				addingCircle = false;
				bodies.emplace_back(utils::mousePosition2f(window), sf::Vector2f(0,0), currentR);
			}
		}
		else if (addingCircle && !sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && event.type == sf::Event::MouseWheelScrolled)
		{
			if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) { // Zoom
				float factor = (event.mouseWheelScroll.delta > 0) ? 0.9f : 1.1f;
				currentR *= factor;
				circleTool.setRadius(currentR);
			}
		}

	}
}

void Orbit::update()
{
	ImGui::SFML::Update(window, dT);
	ImGui::Begin("Simulation Speed");
	ImGui::DragFloat("Speed", &speed, 0.1f, -2.0f, 2.0f);
	if (ImGui::Button(gravity ? "Gravity ON" : "Gravity OFF")) gravity = !gravity;
	if (ImGui::Button(eraseCollisions ? "Collisions ON" : "Collisions OFF")) eraseCollisions = !eraseCollisions;
	ImGui::End();

	std::vector<size_t> toRemove;
	for (size_t i = 0; i < bodies.size(); i++) {
		sf::Vector2f a(0,0);
		sf::Vector2f p = bodies[i].getPos();
		if (gravity || eraseCollisions)
			for (size_t j = 0; j < bodies.size(); j++) {
				if (i == j) continue;
				if (eraseCollisions && bodies[i].collides(bodies[j]) && rng::rand01()>0.8f) {
					if (bodies[i].getMass() < bodies[j].getMass()) toRemove.emplace_back(i);
					else toRemove.emplace_back(j);
				}
				if (gravity) a += bodies[j].getGravityPull(p);
			}
		a += -p;
		bodies[i].update(dT);
		bodies[i].setAcc(a);// / bodies[i].getMass());
	}
	//std::sort(toRemove.begin(), toRemove.end(), std::greater<>());

	std::unordered_set<int> s;
	for (int i : toRemove)
		s.insert(i);
	toRemove.assign(s.begin(), s.end());
	std::sort(toRemove.begin(), toRemove.end(), std::greater<>());

	//for (auto e : toRemove) std::cout << e << " ";
	for (auto e : toRemove)
		if (e < bodies.size() && eraseCollisions) 
			bodies.erase(bodies.begin() + e);
}

void Orbit::draw() const
{
	window.clear();
	for (const auto& b : bodies) {
		window.draw(b);
	}

#ifdef SHOW_ACC
	for (const auto& b : bodies) {
		window.draw(b.getLine());
	}
#endif
	if (addingCircle) {
		circleTool.setOrigin(circleTool.getRadius(), circleTool.getRadius());
		circleTool.setPosition(utils::mousePosition2f(window));
		window.draw(circleTool);
	}


	ImGui::SFML::Render(window);
	window.display();
}
