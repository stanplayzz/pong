#pragma once

#include "ball.hpp"
#include "paddle.hpp"
#include "gameState.hpp"

#include <SFML/Graphics.hpp>

#include <map>

class Game
{
public:
	Game();

	void run();
	void processInput();
	void handleBall();

	sf::View getView() const;

private:
	void createWindow();

	std::unique_ptr<GameState> m_current_state = std::make_unique<GameplayState>();

	sf::RenderWindow m_window;
	sf::View m_view;
};

