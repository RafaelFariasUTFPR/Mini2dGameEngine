#include "S_Collision2d.h"

// Talvez tenha algum bug
Coll2d::CollisionResult Coll2d::calculatePointCollision(sf::Vector2f startPos, sf::VertexArray startCollider, sf::Vector2f endPos, sf::VertexArray collider)
{
	CollisionResult collisionResult;
	sf::VertexArray collisionDebugLines;
	collisionDebugLines.setPrimitiveType(sf::Lines);

	int targetArrVertexCount = collider.getVertexCount();
	bool isInside = false;

	for (int i = 0; i < startCollider.getVertexCount() - 1; i++)
	{
		collisionDebugLines.append(sf::Vertex(startPos, sf::Color::Red));
		collisionDebugLines.append(sf::Vertex(endPos, sf::Color::Red));

		bool intersectedLines = false;
		for (int j = 1; j < targetArrVertexCount; j++)
		{
			sf::Vector2f initialLinePoint(collider[j - 1].position);
			sf::Vector2f endLinePoint(collider[j].position);

			if (myMath::doLinesIntersect(startPos, endPos, initialLinePoint, endLinePoint))
			{
				collisionResult.collisionDebugLinesArr.push_back(collisionDebugLines);

				intersectedLines = true;
				collisionResult.result = false;

				return collisionResult;

			}

		}

		if (!intersectedLines)
		{
			collisionResult.collisionDebugLinesArr.push_back(collisionDebugLines);

			collisionResult.result = true;
			return collisionResult;
		}

	}
	
	collisionResult.collisionDebugLinesArr.push_back(collisionDebugLines);

	collisionResult.result = false;
	return collisionResult;
}


// Colisão pelo metodo das diagonais
Coll2d::CollisionResult Coll2d::calculateCollision(sf::Vector2f startPos, sf::VertexArray startCollider, sf::VertexArray collider)
{
	CollisionResult collisionResult;
	sf::VertexArray collisionDebugLines;
	collisionDebugLines.setPrimitiveType(sf::Lines);

	int targetArrVertexCount = collider.getVertexCount();
	bool isInside = false;
	collisionResult.result = false;


	for (int i = 0; i < startCollider.getVertexCount() - 1; i++)
	{
		sf::Vector2f endPos = startCollider[i].position;

		collisionDebugLines.append(sf::Vertex(startPos, sf::Color::Red));
		collisionDebugLines.append(sf::Vertex(endPos, sf::Color::Red));

		bool intersectedLines = false;
		for (int j = 0; j < targetArrVertexCount-1; j++)
		{
			sf::Vector2f initialLinePoint(collider[j].position);
			sf::Vector2f endLinePoint(collider[j + 1].position);


			if (myMath::doLinesIntersect(startPos, endPos, initialLinePoint, endLinePoint))
			{
				collisionDebugLines.append(sf::Vertex(initialLinePoint, sf::Color::Blue));
				collisionDebugLines.append(sf::Vertex(endLinePoint, sf::Color::Blue));

				collisionResult.result = true;
				collisionResult.collisionDebugLinesArr.push_back(collisionDebugLines);

				return collisionResult;
			}

		}
		collisionResult.collisionDebugLinesArr.push_back(collisionDebugLines);

	}


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

	//Implementar colisão AABB

	for (int i = 0; i < physicsCompVec.size(); i++)
	{
		//Skipping if theres no vertex in the poligon
		if (!physicsCompVec.at(i)->collider->getCollisionPoligon().getVertexCount())
			continue;


		for (int i2 = 0; i2 < physicsCompVec.size(); i2++)
		{
			if (i2 == i)
				continue;

			//Otimização
			double influenceDist = physicsCompVec.at(i)->collider->influenceRadius + physicsCompVec.at(i2)->collider->influenceRadius;
			if (myMath::distBetweenPoints(physicsCompVec.at(i)->transform.position, physicsCompVec.at(i2)->transform.position) > influenceDist)
				continue;

			CollisionResult colResult = calculateCollision(physicsCompVec.at(i)->transform.position, physicsCompVec.at(i)->collider->getCollisionPoligon(), physicsCompVec.at(i2)->collider->getCollisionPoligon());


			if (physicsCompVec.at(i)->collider->drawDebug)
				for (int j = 0; j < colResult.collisionDebugLinesArr.size(); j++)
					global->debugVertexArray.push_back(colResult.collisionDebugLinesArr.at(j));

			
			// Checando se o objeto está dentro do outro
			if (!colResult.result)
			{
				colResult = calculatePointCollision(physicsCompVec.at(i)->transform.position, physicsCompVec.at(i)->collider->getCollisionPoligon(), physicsCompVec.at(i2)->transform.position, physicsCompVec.at(i2)->collider->getCollisionPoligon());
				
				if (physicsCompVec.at(i)->collider->drawDebug)
					for (int j = 0; j < colResult.collisionDebugLinesArr.size(); j++)
						global->debugVertexArray.push_back(colResult.collisionDebugLinesArr.at(j));

			}





		}




	}

	
}
