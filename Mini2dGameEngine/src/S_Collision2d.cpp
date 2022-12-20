#include "S_Collision2d.h"

// Talvez tenha algum bug
Coll2d::CollisionResult Coll2d::calculatePointCollision(sf::Vector2f startPos, sf::VertexArray startCollider, sf::Vector2f endPos, sf::VertexArray collider)
{
	CollisionResult collisionResult;
	sf::VertexArray collisionDebugLines;
	collisionDebugLines.setPrimitiveType(sf::Lines);
	bool isInside = false;
	bool intersectedLines = false;

	for (int i = 0; i < startCollider.getVertexCount() - 1; i++)
	{
		collisionDebugLines.append(sf::Vertex(startPos, debugLineColor));
		collisionDebugLines.append(sf::Vertex(endPos, debugLineColor));

		for (int j = 1; j < collider.getVertexCount(); j++)
		{
			sf::Vector2f initialLinePoint(collider[j].position);
			sf::Vector2f endLinePoint(collider[j - 1].position);

			if (myMath::doLinesIntersect(startPos, endPos, initialLinePoint, endLinePoint))
			{
				//collisionDebugLines.append(sf::Vertex(initialLinePoint, sf::Color::Blue));
				//collisionDebugLines.append(sf::Vertex(endLinePoint, sf::Color::Blue));
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
			double displacementForce = 1000 / myMath::distBetweenPoints(startPos, endPos);

			collisionResult.displacement.x = displacementForce;

			collisionResult.displacement.y = displacementForce;

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

	bool isInside = false;
	collisionResult.result = false;


	for (int i = 0; i < startCollider.getVertexCount() - 1; i++)
	{
		sf::Vector2f endPos = startCollider[i].position;

		collisionDebugLines.append(sf::Vertex(startPos, debugLineColor));
		collisionDebugLines.append(sf::Vertex(endPos, debugLineColor));

		bool intersectedLines = false;
		for (int j = 1; j < collider.getVertexCount(); j++)
		{
			sf::Vector2f initialLinePoint(collider[j].position);
			sf::Vector2f endLinePoint(collider[j - 1].position);


			if (myMath::doLinesIntersect(startPos, endPos, initialLinePoint, endLinePoint))
			{
				collisionDebugLines.append(sf::Vertex(initialLinePoint, sf::Color::Blue));
				collisionDebugLines.append(sf::Vertex(endLinePoint, sf::Color::Blue));

				collisionResult.result = true;
				collisionResult.collisionDebugLinesArr.push_back(collisionDebugLines);

				collisionResult.displacement += myMath::calcDisplacement(startPos, endPos, initialLinePoint, endLinePoint);
				//collisionResult.calculatedDeltaSpeed = myMath::calcElasticColl()
				//return collisionResult;
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



	for (int i = 0; i < physicsCompVec.size(); i++)
	{
		//Skipping if theres no vertex in the poligon
		if (!physicsCompVec.at(i)->collider->getCollisionPoligon().getVertexCount())
			continue;
		physicsCompVec.at(i)->setFutureSpeed(physicsCompVec.at(i)->getSpeed());



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

			if (colResult.result)
			{
				//std::cout << colResult.result;
				//continue;
				// Se eles forem solidos
				float collisionMultiplier = 1;
				if (physicsCompVec.at(i)->isSolid && physicsCompVec.at(i2)->isSolid)
				{
					myMath::ElasticColRes resolveResult = myMath::calcElasticColl(physicsCompVec.at(i)->velocity, physicsCompVec.at(i)->mass, physicsCompVec.at(i2)->velocity, physicsCompVec.at(i2)->mass);
					
					resolveResult.velocity1.x *= collisionMultiplier;
					resolveResult.velocity1.y *= collisionMultiplier;

					resolveResult.velocity2.x *= collisionMultiplier;
					resolveResult.velocity2.y *= collisionMultiplier;

					//std::cout << physicsCompVec.at(i)->velocity.x << std::endl;
					physicsCompVec.at(i)->setFutureSpeed(physicsCompVec.at(i)-> getSpeed() + resolveResult.velocity1);
					physicsCompVec.at(i2)->setFutureSpeed(physicsCompVec.at(i)->getSpeed() + resolveResult.velocity2);

					if (physicsCompVec.at(i)->getIsDynamic())
					{
						physicsCompVec.at(i)->setPosition(physicsCompVec.at(i)->transform.position - colResult.displacement);
					}
					// Se o objeto não for dinamico mova o que fez a colisão
					else if (physicsCompVec.at(i2)->getIsDynamic())
					{
						physicsCompVec.at(i2)->setPosition(physicsCompVec.at(i2)->transform.position + colResult.displacement);

					}

					



				}
				// Se for apenas um trigger
				else
				{

				}

			}



		}




	}
	for (int i = 0; i < physicsCompVec.size(); i++)
		physicsCompVec.at(i)->setSpeed(physicsCompVec.at(i)->getFutureSpeed());


}

void Coll2d::runThreadCollisionSystem(std::vector<std::shared_ptr<EntityMaster>> _entityVec, Global* global, int min, int max)
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



	for (int i = min; i <= max; i++)
	{
		if (i > physicsCompVec.size() - 1)
			break;
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
					global->physicsThreadDebugVertexArray.push_back(colResult.collisionDebugLinesArr.at(j));
			
			// Checando se o objeto está dentro do outro
			if (!colResult.result)
			{
				colResult = calculatePointCollision(physicsCompVec.at(i)->collider->getTransform().position, physicsCompVec.at(i)->collider->getCollisionPoligon(), physicsCompVec.at(i2)->collider->getTransform().position, physicsCompVec.at(i2)->collider->getCollisionPoligon());
				if (physicsCompVec.at(i)->collider->drawDebug)
					for (int j = 0; j < colResult.collisionDebugLinesArr.size(); j++)
						global->physicsThreadDebugVertexArray.push_back(colResult.collisionDebugLinesArr.at(j));
			}


			//	#######################################################
			//
			//			PRECISA MELHORAR ESSE DISPLACEMENT!
			//
			//	#######################################################
			//std::cout << colResult.result;

			if (colResult.result)
			{

				//continue;
				// Se eles forem solidos
				if (physicsCompVec.at(i)->isSolid && physicsCompVec.at(i2)->isSolid)
				{
					/*Tentando remover um pouco da ocilação
					const int disAmount = 50;
					const int maxDisplacement = 10;
					if (colResult.displacement.x > maxDisplacement)
						colResult.displacement.x = maxDisplacement;
					if (colResult.displacement.x < -maxDisplacement)
						colResult.displacement.x = -maxDisplacement;

					if (colResult.displacement.y > maxDisplacement)
						colResult.displacement.y = maxDisplacement;
					if (colResult.displacement.y < -maxDisplacement)
						colResult.displacement.y = -maxDisplacement;
					colResult.displacement = sf::Vector2f(colResult.displacement.x * disAmount * global->deltaTime, colResult.displacement.y * disAmount * global->deltaTime);


					*/
					const int maxDisplacement = 30;


					if (physicsCompVec.at(i)->getIsDynamic())
					{
						physicsCompVec.at(i)->setPosition(physicsCompVec.at(i)->transform.position - colResult.displacement);
					}
					// Se o objeto não for dinamico mova o que fez a colisão
					else if (physicsCompVec.at(i2)->getIsDynamic())
					{
						physicsCompVec.at(i2)->setPosition(physicsCompVec.at(i2)->transform.position + colResult.displacement);

					}



				}
				// Se for apenas um trigger
				else
				{

				}

			}

			//physicsCompVec.at(i)->wasCollidingLastFrame = colResult.result;



		}




	}

	
}
