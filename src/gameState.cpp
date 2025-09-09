#include "gameState.hpp"
#include "game.hpp"

#include <SFML/Graphics.hpp>

#include <print>

GameStateType MainMenuState::update(sf::Time deltaTime)
{
    return p_type;
}

void MainMenuState::draw(sf::RenderWindow& window)
{
    window.clear(sf::Color::Black);


    
    window.display();
}

GameplayState::GameplayState() : m_ball(0, -720 / 2), m_paddle(1280 / 2 - 100, 0)
{
	p_type = GameStateType::gameplay;
}

GameStateType GameplayState::update(sf::Time deltaTime)
{
    m_ball.update(deltaTime);
    m_paddle.update(deltaTime);
    
    handleBall();

    return p_type;
}

void GameplayState::draw(sf::RenderWindow& window)
{
    window.clear(sf::Color::Black);

    window.draw(m_ball.getShape());
    window.draw(m_paddle.getShape());

    window.display();
}

void GameplayState::handleBall()
{
	Game game;
	sf::View view = game.getView();

	// view border collisions
	if (m_ball.getPosition().position.x < -view.getSize().x / 2)
		m_ball.bounceX();
	if (m_ball.getPosition().position.x + m_ball.getPosition().size.x > view.getSize().x / 2)
		std::println("you lost but ehh who cares?");
	if (m_ball.getPosition().position.y < -view.getSize().y / 2 || m_ball.getPosition().position.y + m_ball.getPosition().size.y > view.getSize().y / 2)
		m_ball.bounceY();

	// paddle collisions
	if (m_ball.getPosition().position.x + m_ball.getPosition().size.x > m_paddle.getPosition().position.x &&
		m_ball.getPosition().position.y + m_ball.getPosition().size.y < m_paddle.getPosition().position.y + m_paddle.getPosition().size.y &&
		m_ball.getPosition().position.y + m_ball.getPosition().size.y > m_paddle.getPosition().position.y
		)
	{
		m_ball.bounceX();
	}
}