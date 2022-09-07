#include "S_Collision2d.h"


Coll2d::CollisionResult Coll2d::calculateCollision(sf::VertexArray startCollider, sf::Vector2f endPos, sf::VertexArray collider)
{
	CollisionResult collisionResult;
	sf::VertexArray collisionDebugLines;
	collisionDebugLines.setPrimitiveType(sf::Lines);

	int targetArrVertexCount = collider.getVertexCount();
	bool isInside = false;


	for (int i = 0; i < startCollider.getVertexCount() - 1; i++)
	{
		sf::Vector2f startPos = startCollider[i].position;
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


		
	}
	collisionResult.result = false;
	return collisionResult;
	
}



void Coll2d::runCollisionSystem(std::vector<std::shared_ptr<EntityMaster>> _entityVec, Global* global)
{
	std::vector<std::shared_ptr<C_Physics2d>> physicsCompVec;
	for (int i = 0; i < _entityVec.size(); i++)
	{
		if (_entityVec.at(i) == nullptr)
			continue;
		for (int j = 0; j < _entityVec[i]->componentHandler.componentVec.size(); j++)
		{
			if (std::dynamic_pointer_cast<C_Physics2d> (_entityVec[i]->componentHandler.componentVec[j]))
			{
				physicsCompVec.push_back(std::dynamic_pointer_cast<C_Physics2d> (_entityVec[i]->componentHandler.componentVec[j]));

			}
		}
	}

	// Essa colisão está muito lenta
	// Precisa mudar o tipo de colisão ja que não conta se não tiver vertices se sobrepondo

	for (int i = 0; i < physicsCompVec.size(); i++)
	{
		//Skipping if theres no vertex in the poligon
		if (!physicsCompVec.at(i)->collider->collisionPoligon.getVertexCount())
			continue;


		for (int i2 = 0; i2 < physicsCompVec.size(); i2++)
		{
			if (i2 == i)
				continue;
			CollisionResult colResult = calculateCollision(physicsCompVec.at(i)->collider->collisionPoligon, physicsCompVec.at(i2)->transform.position, physicsCompVec.at(i2)->collider->collisionPoligon);
			if (physicsCompVec.at(i)->collider->drawDebug)
			{
				for (int j = 0; j < colResult.collisionDebugLinesArr.size(); j++)
				{
					global->debugVertexArray.push_back(colResult.collisionDebugLinesArr.at(j));
				}

			}

		}




	}

	
}
