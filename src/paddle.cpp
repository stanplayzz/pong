#include "paddle.hpp"
#include "game.hpp"

Paddle::Paddle(float startX, float startY) : m_position(startX, startY)
{
	m_paddle.setSize(sf::Vector2f(50.f, 200.f));
	m_paddle.setFillColor(sf::Color::Blue);
	m_paddle.setPosition(m_position);
	m_paddle.setOrigin(m_paddle.getGeometricCenter());
}

const sf::RectangleShape& Paddle::getShape() const
{
	return m_paddle;
}

const sf::FloatRect& Paddle::getPosition() const
{
	return m_paddle.getGlobalBounds();
}

void Paddle::update(sf::Time deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		m_position.y -= speed * deltaTime.asSeconds();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		m_position.y += speed * deltaTime.asSeconds();

	m_paddle.setPosition(m_position);
}