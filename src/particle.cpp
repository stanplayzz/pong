#include "particle.hpp"

#include <numbers>

ParticleSystem::ParticleSystem()
{
	m_vertices.setPrimitiveType(sf::PrimitiveType::Triangles);

	m_particles.resize(m_maxParticles);
	m_vertices.resize(m_maxParticles * 6);

	for (size_t i = 0; i < m_maxParticles; i++)
	{
		size_t vertexIndex = i * 6;

		sf::Vector2f center(0.f, 0.f);

		float halfX = m_particleSize.x / 2.f;
		float halfY = m_particleSize.y / 2.f;

		m_vertices[vertexIndex].position = center + sf::Vector2f(-halfX, -halfY);
		m_vertices[vertexIndex + 1].position = center + sf::Vector2f(halfX, -halfY);
		m_vertices[vertexIndex + 2].position = center + sf::Vector2f(halfX, halfY);

		m_vertices[vertexIndex + 3].position = center + sf::Vector2f(-halfX, -halfY);
		m_vertices[vertexIndex + 4].position = center + sf::Vector2f(halfX, halfY);
		m_vertices[vertexIndex + 5].position = center + sf::Vector2f(-halfX, halfY);

		for (int j = 0; j < 6; j++)
			m_vertices[vertexIndex + j].color = sf::Color(0, 0, 0, 0);
	}
}

void ParticleSystem::emit(sf::Vector2f position, sf::Time lifeTime)
{
	for (size_t i = 0; i < m_maxParticles; i++)
	{
		Particle& p = m_particles[i];
		if (p.alive == false)
		{
			size_t vertexIndex = i * 6;

			float angle = (rand() % 360) * std::numbers::pi / 180.f;

			p.position = position;
			p.lifeTime = lifeTime;
			p.velocity = sf::Vector2f(cos(angle) * m_particleSpeed, sin(angle) * m_particleSpeed);
			p.color = sf::Color::White;
			for (int j = 0; j < 6; j++)
				m_vertices[vertexIndex + j].color = p.color;
			p.alive = true;
		}
	}
}

void ParticleSystem::update(sf::Time deltaTime)
{
	for (size_t i = 0; i < m_maxParticles; i++)
	{
		Particle& p = m_particles[i];
		if (p.alive == true)
		{
			size_t vertexIndex = i * 6;

			p.position += p.velocity * deltaTime.asSeconds();

			float halfX = m_particleSize.x / 2.f;
			float halfY = m_particleSize.y / 2.f;

			m_vertices[vertexIndex].position = p.position + sf::Vector2f(-halfX, -halfY);
			m_vertices[vertexIndex + 1].position = p.position + sf::Vector2f(halfX, -halfY);
			m_vertices[vertexIndex + 2].position = p.position + sf::Vector2f(halfX, halfY);

			m_vertices[vertexIndex + 3].position = p.position + sf::Vector2f(-halfX, -halfY);
			m_vertices[vertexIndex + 4].position = p.position + sf::Vector2f(halfX, halfY);
			m_vertices[vertexIndex + 5].position = p.position + sf::Vector2f(-halfX, halfY);

			p.lifeTime -= deltaTime;
			if (p.lifeTime.asSeconds() <= 0)
				p.alive = false;
		}
	}
}

void ParticleSystem::draw(sf::RenderWindow& window)
{
	window.draw(m_vertices);
}