#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <map>


template <typename itemType>
class ResourceManager {

public:

	std::map<std::string, itemType> resources;

public:

	ResourceManager() { }

	void loadResource(const std::string& name, const itemType res) {

		this->resources[name] = res;
		return;

	}
	itemType& getRef(const std::string& resource) {

		return (this->resources.at(resource));

	}

};