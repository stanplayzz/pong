#pragma once

#include <SFML/Graphics.hpp>

class Paddle
{
public:
	Paddle(float startX, float startY);

	[[nodiscard]] const sf::RectangleShape& getShape() const;
	[[nodiscard]] sf::FloatRect getPosition() const;
	void update(sf::Time deltaTime);

private:
	sf::RectangleShape m_paddle;
	sf::Vector2f m_position;
	float speed = 400.f;
};