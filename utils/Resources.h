#pragma once
#include "resource.h"
//#include "../particles/ParticleSystem.h"

class ps::ParticleSystem;

class Resources
{
private:
	Resources();

	std::vector<sf::Texture> textures;
	std::vector<std::vector<sf::IntRect>> textRects;


	std::vector<ps::Settings> particlePresets;
	std::vector<ps::ParticleSystem> particleSystems;

	const std::string PATH_TO_ASSETS = "../assets/";
	const std::string RESOURCES_CSV = "resources.csv";

public:
	enum class TextureIdx {
		smoke
	};
	Resources(Resources &other) = delete;
	void operator=(const Resources&) = delete;
	static Resources& getInstance();

	const sf::Texture& getTexture(TextureIdx type);
	const std::vector<sf::IntRect>& getIntRects(TextureIdx type);


	ps::ParticleSystem& getParticleSystem(int idx);

	std::vector<ps::ParticleSystem>& getParticleSystems();

	bool savePSettings(const ps::Settings& pSettings) const;

	const std::vector<ps::Settings>& getPSystemPresets() const;
};

