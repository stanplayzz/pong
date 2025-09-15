#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <vector>

struct Particle
{
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Time lifeTime;
	sf::Color color;
	bool alive;
};

class ParticleSystem
{
public:
	ParticleSystem();

	void emit(sf::Vector2f position, sf::Time lifeTime);
	void update(sf::Time deltaTime);
	void draw(sf::RenderWindow& window);

private:
	std::size_t m_maxParticles = 100;
	sf::Vector2f m_particleSize{ 25.f, 25.f };
	float m_particleSpeed = 100.f;
	
	std::vector<Particle> m_particles;
	sf::VertexArray m_vertices;
};