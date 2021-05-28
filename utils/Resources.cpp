#include "Resources.h"
#include <fstream>
#include <iostream>
#include <exception>
#include <sstream>
#include "utils.h"

Resources::Resources()
{
	std::ifstream file(PATH_TO_ASSETS + RESOURCES_CSV);

	if (!file.is_open()) {
		throw std::runtime_error("Resources file cannot be read. Make sure the file " + RESOURCES_CSV + " is not corrupt.");
	}

	std::string buffer, type, token[4];
	std::getline(file, buffer, '\n');

	//int i;

	while (!file.eof()) {
		std::istringstream iss(buffer);
		std::getline(iss, type, ',');

		if (type == "T") {
			char sep = ',';
			std::string line;
			std::getline(iss, line); // until \n
			std::istringstream liness(line);
			// number of sprites in grid
			sf::Vector2i nSprites;
			nSprites.x = utils::parseInt(liness, sep);
			nSprites.y = utils::parseInt(liness, sep);
			// Texture
			std::string path;
			std::getline(liness, path);
			auto& tex = textures.emplace_back();
			path = PATH_TO_ASSETS + path;
			if (!tex.loadFromFile(path)) 
				throw std::runtime_error("Error loading texture <" + PATH_TO_ASSETS + path + ">\n");
			// IntRects
			auto& rects = textRects.emplace_back(); // vector
			sf::Vector2i size(tex.getSize().x / nSprites.x, tex.getSize().y / nSprites.y); // size of each frame
			for (int col = 0; col < nSprites.y; col++)
				for (int row = 0; row < nSprites.x; row++)
					rects.emplace_back(row * size.x, col * size.y, size.x, size.y); // each rect
		}
		else if (type == "PS") { // Particle Systems
			char sep = ',';
			std::string line;
			std::getline(iss, line); // until \n
			ps::Settings pSettings(line);
			auto& ps = particlePresets.emplace_back(pSettings);
		}
		/*else if (type == "PS") { // Particle Systems
			char sep = ',';
			std::string line;
			std::getline(iss, line); // until \n
			std::istringstream liness(line);
			int texIdx = utils::parseInt(liness, sep);
			std::vector<float> coords;
			for (int i = 0; i < 4; i++) coords.push_back(utils::parseFloat(liness, sep));
			sf::FloatRect texRect(coords[0], coords[1],coords[2],coords[3]);
			std::getline(liness, line); // rest of the line until \n
			ps::Settings pSettings(line);
			auto& ps = particleSystems.emplace_back(pSettings);
			//std::cout <<"texRect: " << texRect.left << " "<<texRect.top << " "<<texRect.width << " "<<texRect.height << " \n";
			ps.setTexture(getTexture(TextureIdx(texIdx)), texRect);
		}*/
	std::getline(file, buffer, '\n');
	}
}

Resources& Resources::getInstance() {
	static Resources src_;
	return src_;
}


const sf::Texture& Resources::getTexture(TextureIdx type) {
	return textures[int(type)];
}

const std::vector<sf::IntRect>& Resources::getIntRects(TextureIdx type)
{
	return textRects[int(type)];
}

ps::PSystem& Resources::getParticleSystem(int idx)
{
	return particleSystems[idx];
}

std::vector<ps::PSystem>& Resources::getParticleSystems()
{
	return particleSystems;
}

bool Resources::savePSettings(const ps::Settings& pSettings) const
{
	std::ofstream f(PATH_TO_ASSETS + RESOURCES_CSV, std::ios_base::app);

	if (!(f << "\n# Saved ParticleSettings:\n")) return false;
	f << "PS," << pSettings.to_string();
	return true;
}

const std::vector<ps::Settings>& Resources::getPSystemPresets() const
{
	return particlePresets;
}

