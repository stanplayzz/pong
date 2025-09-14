#include "assetManager.hpp"

#include <filesystem>

namespace fs = std::filesystem;

static sf::Font& AssetManager::getFont(const std::string& name)
{
	auto& instance = getInstance();

	auto it = instance.fonts.find(name);
	if (it != instance.fonts.end())
	{
		return it->second;
	}
	sf::Font font;
	std::string path = fs::path("assets/fonts") / name;

	if (!font.loadFromFile(path))
	{
		throw std::runtime_error("Failed to open font at: " + path);
	}

	instance.fonts[name] = std::move(font);
	return instance.fonts[name];
}