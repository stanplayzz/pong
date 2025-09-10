#include "ball.hpp"

#include <print>

Ball::Ball(float startX, float startY) : m_position(startX, startY)
{
	m_ballShape.setRadius(25.f);
	m_ballShape.setFillColor(sf::Color::Magenta);
	m_ballShape.setPosition(m_position);
}

void Ball::bounceX()
{
	m_ballDirectionX = -m_ballDirectionX;
}

void Ball::bounceY()
{
	m_ballDirectionY = -m_ballDirectionY;
}

const sf::CircleShape& Ball::getShape() const
{
	return m_ballShape;
}

sf::FloatRect Ball::getPosition() const
{
	return m_ballShape.getGlobalBounds();
}

sf::Vector2f Ball::getCenter() const
{
	return m_ballShape.getGeometricCenter();
}

float Ball::getRadius() const
{
	return m_ballShape.getRadius();
}

void Ball::update(sf::Time deltaTime)
{
	m_position.x += m_ballDirectionX * speed * deltaTime.asSeconds();
	m_position.y += m_ballDirectionY * speed * deltaTime.asSeconds();

	m_ballShape.setPosition(m_position);
}