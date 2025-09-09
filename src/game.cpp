#include "game.hpp"
#include "ball.hpp"

#include <print>

Game::Game()
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
		m_current_state->draw(m_window);

		auto to_state = m_current_state->update(deltaTime, m_window);

		if (to_state != m_current_state->get_type())
		{
			switch (to_state)
			{
			case GameStateType::main_menu:
				m_current_state = std::make_unique<MainMenuState>();
				break;
			case GameStateType::gameplay:
				m_current_state = std::make_unique<GameplayState>();
				break;
			}
		}

		
	}
}

void Game::processInput()
{
	while (auto event = m_window.pollEvent())
	{
		m_current_state->onEvent(event);
		if (event->is<sf::Event::Closed>())
			m_window.close();
	}
}

sf::View Game::getView() const
{
	return m_window.getView();
}