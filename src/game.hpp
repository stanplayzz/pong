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

	sf::View getView() const;

private:

	std::unique_ptr<GameState> m_current_state = std::make_unique<MainMenuState>();

	sf::RenderWindow m_window;
	sf::View m_view;
};

