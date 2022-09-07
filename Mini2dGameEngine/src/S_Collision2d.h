#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <thread>

#include "MyMath.h"
#include "C_Physics2d.h"
#include "C_Collider2d.h"

#include "EntityMaster.h"


namespace Coll2d
{
	struct CollisionResult
	{
		bool result = false;
		std::vector <sf::VertexArray> collisionDebugLinesArr;
	};

	CollisionResult calculatePointCollision(sf::Vector2f startPos, sf::Vector2f endPos, sf::VertexArray collider);
	
	// Colisão pelo metodo das diagonais
	CollisionResult calculateCollision(sf::Vector2f startPos, sf::VertexArray startCollider, sf::VertexArray collider);


	void runCollisionSystem(std::vector<std::shared_ptr<EntityMaster>> _entityVec, Global* global);


}

