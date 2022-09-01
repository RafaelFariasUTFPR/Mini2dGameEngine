#include "S_Collision2d.h"


Coll2d::CollisionResult Coll2d::calculateCollision(sf::Vector2f startPos, sf::Vector2f endPos, sf::VertexArray collider)
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

void Coll2d::runCollisionSystem(std::vector<EntityMaster*> _entityVec)
{
	std::vector<C_Physics2d*> physicsCompVec;
	for (int i = 0; i < _entityVec.size(); i++)
	{
		if (_entityVec.at(i) == nullptr)
			continue;
		for (int j = 0; j < _entityVec[i]->componentHandler.componentVec.size(); j++)
		{
			if (dynamic_cast<C_Physics2d*> (_entityVec[i]->componentHandler.componentVec[j]))
			{
				physicsCompVec.push_back(dynamic_cast<C_Physics2d*> (_entityVec[i]->componentHandler.componentVec[j]));

			}
		}
	}
}
