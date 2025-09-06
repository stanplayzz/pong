#pragma once

#include <SFML/Graphics.hpp>

class Paddle
{
public:
	Paddle(float startX, float startY);

	sf::RectangleShape getShape();
	sf::FloatRect getPosition();
	void update(sf::Time deltaTime);

private:
	sf::RectangleShape m_paddle;
	sf::Vector2f m_position;
	float speed = 400.f;
};