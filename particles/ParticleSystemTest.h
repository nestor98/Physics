#pragma once
#include "../camera/Camera.h"
#include "ParticleSystem.h"

namespace ps {

class ParticleSystemTest
{

	ps::Settings pSettings;
	ps::ParticleSystem pSystem;
	sf::RenderWindow& window;
	sf::Time dT = sf::seconds(0);

	Camera cam;

	int currentPreset = -1;

	// UI vars:
	float ttl = 1.5f;// , sizeI = 50, sizeE = 2.0f * sizeI;
	float colIni[4] { 1.0f,1.0f,1.0f,1.0f },
		  colEnd[4] { 1.0f,1.0f,1.0f,0.0f };
	float vel[6] = { 0,0, // vel 
					 0,0, // velNeg x,y
					 0,0  // velPos x,y
	};


	void captureEvents();
	void update();
	void draw() const;


	void loadNextPSettings();
	void updateSettings();
	void updateVars();


public:
	ParticleSystemTest(sf::RenderWindow& _window, const sf::Texture& t);
	ParticleSystemTest(sf::RenderWindow& _window, const sf::Texture& t, const sf::IntRect& r);
	
	void loop();


};

} // namespace ps