#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <string>

#include "texture_manager.hpp"

void TextureManager::loadTexture(const std::string& name, const std::string& filename)
{
    /* Load the texture */
    sf::Texture tex;
    if (!tex.loadFromFile(filename)) {
        std::cout << "Error Loading File " << filename << std::endl;
    }

    /* Add it to the list of textures */
    this->textures[name] = tex;

    return;
}

sf::Texture& TextureManager::getRef(const std::string& texture)
{
    return this->textures.at(texture);
}

TextureManager::TextureManager() { }