#include "game.hpp"
#include "ball.hpp"

#include <print>

std::map<sf::Keyboard::Key, bool> Game::m_keyMap;

Game::Game() : m_ball(0, -720/2), m_paddle(1280 /2 - 100, 0)
{
}

Game::~Game()
{
}

void Game::createWindow()
{
	m_window.create(sf::VideoMode({ 1280, 720 }), "This is totally not a recreation of the famous game named 'pong' originally created by Allan Alcorn", sf::Style::Titlebar | sf::Style::Close);

	m_view = sf::View(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(m_window.getSize()));
	m_window.setView(m_view);
}

void Game::run()
{
	sf::Clock clock;

	sf::Time deltaTime;

	while (m_window.isOpen())
	{
		deltaTime = clock.restart();

		processInput();

		handleBall();

		m_window.clear(sf::Color::Black);

		m_ball.update(deltaTime);
		m_paddle.update(deltaTime);
		m_window.draw(m_ball.getShape());


		m_window.draw(m_paddle.getShape());

		m_window.display();
	}
}

void Game::processInput()
{
	while (auto event = m_window.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
			m_window.close();

		if (auto key = event->getIf<sf::Event::KeyPressed>())
			Game::m_keyMap[key->code] = true;

		if (auto key = event->getIf<sf::Event::KeyReleased>())
			Game::m_keyMap[key->code] = false;

	}
}

void Game::handleBall()
{
	// view border collisions
	if (m_ball.getPosition().position.x < -m_view.getSize().x / 2)
		m_ball.bounceX();
	if (m_ball.getPosition().position.x + m_ball.getPosition().size.x > m_view.getSize().x / 2)
		m_window.close();
	if (m_ball.getPosition().position.y < -m_view.getSize().y / 2 || m_ball.getPosition().position.y + m_ball.getPosition().size.y > m_view.getSize().y / 2)
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