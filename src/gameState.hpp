#pragma once

#include "ball.hpp"
#include "paddle.hpp"
#include "assetManager.hpp"
#include "particle.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdint>

enum class GameStateType : std::uint8_t { main_menu, gameplay };

class GameState
{
public:
	virtual ~GameState() = default;
	virtual GameStateType update(sf::Time deltaTime, sf::RenderWindow& window) { return p_type; }
	virtual void draw(sf::RenderWindow& window) = 0;
	virtual void onEvent(std::optional<sf::Event> event) {}

	[[nodiscard]] auto get_type() const -> GameStateType { return p_type; }
	
protected:
	GameStateType p_type{};
	GameStateType m_target_type{};
};

class MainMenuState final : public GameState
{
public:
	MainMenuState();
	GameStateType update(sf::Time deltaTime, sf::RenderWindow& window) override;
	void draw(sf::RenderWindow& window) override;
	void onEvent(std::optional<sf::Event> event) override;
private:
	std::optional<sf::Text> m_startText;
	sf::Font m_font;
	ParticleSystem m_particleSystem;
};

class GameplayState final : public GameState
{
public:
	GameplayState();
	GameStateType update(sf::Time deltaTime, sf::RenderWindow& window) override;
	void draw(sf::RenderWindow& window) override;
	void onEvent(std::optional<sf::Event> event) override {}

private:
	void handleBall(sf::RenderWindow& window);

	Ball m_ball;
	Paddle m_paddle;

	sf::SoundBuffer m_plopBuffer;
	sf::SoundBuffer m_gameOverBuffer;
	sf::Sound m_plop;
	sf::Sound m_gameOver;
};