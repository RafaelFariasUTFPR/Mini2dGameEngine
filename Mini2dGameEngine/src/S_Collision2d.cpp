#include "S_Collision2d.h"

using namespace Coll2d;



CollisionResult Coll2d::calculateCollision(sf::Vector2f startPos, sf::Vector2f endPos, sf::VertexArray collider)
{
	CollisionResult collisionResult;
	sf::VertexArray collisionDebugLines;
	collisionDebugLines.clear();

	int targetArrVertexCount = collider.getVertexCount();
	bool isInside = false;


	collisionDebugLines.append(sf::Vertex(startPos, sf::Color::Red));
	collisionDebugLines.append(sf::Vertex(endPos, sf::Color::Red));

	bool intersectedLines = false;
	for (int j = 1; j < targetArrVertexCount; j++)
	{

		sf::Vector2f initialLinePoint(collider[j - 1].position);
		sf::Vector2f endLinePoint(collider[j].position);



		if (myMath::doLinesIntersect(startPos, endPos, initialLinePoint, endLinePoint))
		{

			collisionDebugLines.append(sf::Vertex(initialLinePoint, sf::Color::Blue));
			collisionDebugLines.append(sf::Vertex(endLinePoint, sf::Color::Blue));

			collisionResult.collisionDebugLinesArr.push_back(collisionDebugLines);
				
			intersectedLines = true;

		}

	}

	if (!intersectedLines)
	{
		collisionResult.result = true;
		return collisionResult;
	}

		
	collisionResult.result = false;
	return collisionResult;
}




