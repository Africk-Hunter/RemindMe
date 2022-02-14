#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <map>

class TextureManager {

public:

	std::map<std::string, sf::Texture> textures;

public:

	void loadTexture(const std::string& name, const std::string& fileName);
	sf::Texture& getRef(const std::string& texture);

	TextureManager();



	class texture_manager
	{
	};
};