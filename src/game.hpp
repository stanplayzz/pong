#pragma once

#include "ball.hpp"
#include "paddle.hpp"

#include <SFML/Graphics.hpp>

#include <map>

class Game
{
public:
	Game();
	~Game();

	void createWindow();
	void run();
	void processInput();
	void handleBall();

	static std::map<sf::Keyboard::Key, bool> m_keyMap;

private:
	sf::RenderWindow m_window;
	sf::View m_view;

	

	Ball m_ball;
	Paddle m_paddle;
};

