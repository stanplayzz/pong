#include "assetManager.hpp"

#include <filesystem>

sf::Font& AssetManager::getFont(const std::string& name)
{
	auto& instance = getInstance();

	auto it = instance.fonts.find(name);
	if (it != instance.fonts.end())
	{
		return it->second;
	}
	sf::Font font;
	std::string path = (std::filesystem::path("assets/fonts") / name).string();

	if (!font.openFromFile(path))
	{
		throw std::runtime_error("Failed to open font at: " + path);
	}

	instance.fonts[name] = std::move(font);
	return instance.fonts[name];
}

sf::SoundBuffer& AssetManager::getSoundBuffer(const std::string& name)
{
	auto& instance = getInstance();

	auto it = instance.sounds.find(name);
	if (it != instance.sounds.end())
	{
		return it->second;
	}
	sf::SoundBuffer SoundBuffer;
	std::string path = (std::filesystem::path("assets/sfx") / name).string();

	if (!SoundBuffer.loadFromFile(path))
	{
		throw std::runtime_error("Failed to open sound at: " + path);
	}

	instance.sounds[name] = std::move(SoundBuffer);
	return instance.sounds[name];
}
