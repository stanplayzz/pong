#pragma once

#include "ball.hpp"
#include "paddle.hpp"

#include <SFML/Graphics.hpp>
#include <cstdint>

enum class GameStateType : std::uint8_t { main_menu, gameplay };

class GameState
{
public:
	virtual ~GameState() = default;
	virtual GameStateType update(sf::Time deltaTime) { return p_type; }
	virtual void draw(sf::RenderWindow& window) =0;

	[[nodiscard]] auto get_type() const -> GameStateType { return p_type; }
	
protected:
	GameStateType p_type{};
};

class MainMenuState final : public GameState
{
public:
	MainMenuState() { p_type = GameStateType::main_menu; }
	GameStateType update(sf::Time deltaTime) override;
	void draw(sf::RenderWindow& window) override;
};

class GameplayState final : public GameState
{
public:
	GameplayState();
	GameStateType update(sf::Time deltaTime) override;
	void draw(sf::RenderWindow& window) override;
private:
	void handleBall();

	Ball m_ball;
	Paddle m_paddle;
};