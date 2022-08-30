#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "MyMath.h"


namespace Coll2d
{
	struct CollisionResult
	{
		bool result = false;
		std::vector <sf::VertexArray> collisionDebugLinesArr;
	};

	CollisionResult calculateCollision(sf::Vector2f startPos, sf::Vector2f endPos, sf::VertexArray collider);


}
