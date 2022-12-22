#pragma once

#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>

#include "C_Collider2d.h"
#include "MyMath.h"

namespace SAT
{
	struct ColResult
	{
		sf::Vector2f displacement = sf::Vector2f(0, 0);
		bool result;
	};


	const float INF = std::numeric_limits<float>::infinity();

	ColResult SATCollision(C_Collider2d body, C_Collider2d other);

	//bool SATCollision(const CircleCollider& body, const Collider& other, sf::Vector2f& MTV);
	//bool SATCollision(const C_Collider2d& body, const CircleCollider& other, sf::Vector2f& MTV);
	//bool SATCollision(const CircleCollider& body, const CircleCollider& other, sf::Vector2f& MTV);

	sf::Vector2f CircleAxis(sf::VertexArray vertices, uint32_t count, sf::Vector2f center);

	sf::Vector2f PerpendicularAxis(sf::VertexArray vertices, uint32_t index, uint32_t count);

	sf::Vector2f ProjectOnto(sf::VertexArray vertices, uint32_t count, sf::Vector2f axis);
	sf::Vector2f ProjectCircle(sf::Vector2f circleCenter, float radius, sf::Vector2f axis);

	sf::Vector2f GetCenter(C_Collider2d body);

	float Overlap(sf::Vector2f v0, sf::Vector2f v1);
}

