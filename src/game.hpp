#pragma once

#include "ball.hpp"
#include "paddle.hpp"

#include <SFML/Graphics.hpp>

#include <map>

class Game
{
public:
	Game();

	void run();
	void processInput();
	void handleBall();

private:
	void createWindow();

	sf::RenderWindow m_window;
	sf::View m_view;

	Ball m_ball;
	Paddle m_paddle;
};

