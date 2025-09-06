#pragma once

#include <SFML/Graphics.hpp>

class Ball
{
public:
	Ball(float startX, float startY);

	void bounceX();
	void bounceY();
	sf::CircleShape getShape();
	sf::FloatRect getPosition();
	void update(sf::Time deltaTime);

private:
	sf::CircleShape m_ballShape;
	sf::Vector2f m_position;
	float m_ballDirectionX = 1.0f;
	float m_ballDirectionY = 1.0f;
	float speed = 500.0f;
};