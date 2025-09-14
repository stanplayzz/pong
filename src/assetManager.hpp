#pragma once

#include <SFML/Graphics.hpp>

#include <map>
#include <string>

class AssetManager
{
public:
	static sf::Font& getFont(const std::string& name);

private:
	AssetManager() {}
	static AssetManager& getInstance()
	{
		static AssetManager instance;
		return instance;
	}

	std::map<std::string, sf::Font> fonts;
};