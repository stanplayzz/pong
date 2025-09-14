#include "gameState.hpp"
#include "game.hpp"
#include "assetManager.hpp"

#include <SFML/Graphics.hpp>

#include <print>
#include <algorithm>
#include <stdexcept>

MainMenuState::MainMenuState()
{
	m_font = AssetManager::getFont("Coolvetica.otf");

	m_startText.emplace(m_font);
	m_startText->setString("Press Any Key To Play!");
	m_startText->setFillColor(sf::Color::White);
	m_startText->setCharacterSize(50);
	m_startText->setOrigin(sf::Vector2f(m_startText->getLocalBounds().size.x / 2, m_startText->getLocalBounds().size.y / 2));

	p_type = GameStateType::main_menu;
}

GameStateType MainMenuState::update(sf::Time deltaTime, sf::RenderWindow& window)
{
    return m_target_type;
}

void MainMenuState::onEvent(std::optional<sf::Event> event)
{
	if (event->is<sf::Event::KeyReleased>())
	{
		m_target_type = GameStateType::gameplay;
	}
}

void MainMenuState::draw(sf::RenderWindow& window)
{
    window.clear(sf::Color(0, 20, 40));

	window.draw(*m_startText);
    
    window.display();
}

GameplayState::GameplayState() : m_ball(0, -720 / 2), m_paddle(1280 / 2 - 100, 0)
{
	p_type = GameStateType::gameplay;
}

GameStateType GameplayState::update(sf::Time deltaTime, sf::RenderWindow& window)
{
    m_ball.update(deltaTime);
    m_paddle.update(deltaTime);
    
    handleBall(window);

    return m_target_type;
}

void GameplayState::draw(sf::RenderWindow& window)
{
    window.clear(sf::Color::Black);

    window.draw(m_ball.getShape());
    window.draw(m_paddle.getShape());

    window.display();

	m_target_type = GameStateType::gameplay;
}

void GameplayState::handleBall(sf::RenderWindow& window)
{
	sf::View view = window.getView();

	// view border collisions
	if (m_ball.getPosition().position.x < -view.getSize().x / 2)
		m_ball.bounceX();
	if (m_ball.getPosition().position.x + m_ball.getPosition().size.x > view.getSize().x / 2)
		m_target_type = GameStateType::main_menu;
	if (m_ball.getPosition().position.y < -view.getSize().y / 2 || m_ball.getPosition().position.y + m_ball.getPosition().size.y > view.getSize().y / 2)
		m_ball.bounceY();

	// paddle collisions
	float closestX = std::clamp(m_ball.getCenter().x, m_paddle.getPosition().position.x, m_paddle.getPosition().position.x + m_paddle.getPosition().size.x);
	float closestY = std::clamp(m_ball.getCenter().y, m_paddle.getPosition().position.y, m_paddle.getPosition().position.y + m_paddle.getPosition().size.y);

	float distX = m_ball.getCenter().x - closestX;
	float distY = m_ball.getCenter().y - closestY;
	float dist = std::sqrt(distX * distX + distY * distY);

	if (dist <= m_ball.getRadius())
	{
		m_ball.bounceX();
	}


	/*if (m_ball.getPosition().position.x + m_ball.getPosition().size.x > m_paddle.getPosition().position.x &&
		m_ball.getPosition().position.x + m_ball.getPosition().size.x < m_paddle.getPosition().position.x + 5 &&
		m_ball.getPosition().position.y < m_paddle.getPosition().position.y + m_paddle.getPosition().size.y &&
		m_ball.getPosition().position.y + m_ball.getPosition().size.y > m_paddle.getPosition().position.y)
	{
		m_ball.bounceX();
	}*/
}