#include "S_Collision2d.h"


std::vector<Collision> Coll2d::runCollisionSystem(std::vector<std::shared_ptr<C_Collider2d>> colliderCompVec)
{
	std::vector<Collision> collisionsVector;
	for (int i = 0; i < colliderCompVec.size(); i++)
	{
		colliderCompVec.at(i)->clearCollisions();
		//Skipping if theres no vertex in the poligon
		if (!colliderCompVec.at(i)->getCollisionPoligon().getVertexCount())
			continue;
		for (int i2 = 0; i2 < colliderCompVec.size(); i2++)
		{
			if (i2 == i)
				continue;
			if (!colliderCompVec.at(i)->getIsDynamic() && !colliderCompVec.at(i2)->getIsDynamic())
				continue;

			//printf("%i && %i\n", i, i2);

			//Otimização
			double influenceDist = colliderCompVec.at(i)->influenceRadius + colliderCompVec.at(i2)->influenceRadius;
			if (myMath::distBetweenPoints(colliderCompVec.at(i)->getTransform().position, colliderCompVec.at(i2)->getTransform().position) > influenceDist)
				continue;

			// Calculando a colisão
			SAT::ColResult result = SAT::SATCollision(*colliderCompVec.at(i), *colliderCompVec.at(i2));


			// Se estiver colidindo
			if (result.result)
			{
				//myMath::CollResult solveResult = myMath::calculateInelasticCollision(physicsCompVec.at(i)->getSpeed(), physicsCompVec.at(i)->mass, physicsCompVec.at(i2)->getSpeed(), physicsCompVec.at(i2)->mass, 1);
				
				Collision coll;
				coll.myId = i;
				coll.otherId = i2;
				coll.collisionNormal = myMath::Normalize(result.displacement);
				coll.displacement = result.displacement;

				// Adicionando a lista de colisões do componente
				colliderCompVec.at(i)->addCollisions(coll);

				collisionsVector.push_back(coll);
			}

		}

	}

	return collisionsVector;

}


void Coll2d::solvePhysicsCollisions(std::vector<std::shared_ptr<C_Physics2d>> physicsCompVec, std::vector<Collision>collisionsVector, double dt)
{
	for (unsigned int i = 0; i < collisionsVector.size(); i++)
	{
		//if (physicsCompVec.at(collisionsVector.at(i).myId) == nullptr || physicsCompVec.at(collisionsVector.at(i).otherId) == nullptr)
		//	continue;

		
		std::shared_ptr<C_Physics2d> bodyPhysicsComp;
		std::shared_ptr<C_Physics2d> otherBodyPhysicsComp;


		// Pegando o componente C_Physics2d do boddy
		for (unsigned int j = 0; j < physicsCompVec.size(); j++)
		{
			if (physicsCompVec.at(j)->getMyId() == collisionsVector.at(i).myId)
				bodyPhysicsComp = physicsCompVec.at(j);
			else if (physicsCompVec.at(j)->getMyId() == collisionsVector.at(i).otherId)
				otherBodyPhysicsComp = physicsCompVec.at(j);
		}


		myMath::CollResult solveResult = myMath::calculateInelasticCollision(bodyPhysicsComp->getSpeed(), bodyPhysicsComp->mass, otherBodyPhysicsComp->getSpeed(), otherBodyPhysicsComp->mass, 1);


		
		if (bodyPhysicsComp->getIsDynamic())
		{
			bodyPhysicsComp->setPosition(bodyPhysicsComp->transform->position + collisionsVector.at(i).displacement);

			if (otherBodyPhysicsComp->hasInfiniteMass())
			{
				bodyPhysicsComp->setSpeed(myMath::GetReflection(bodyPhysicsComp->getSpeed(), collisionsVector.at(i).collisionNormal));

			}

		}
		if (otherBodyPhysicsComp->getIsDynamic())
		{

			//otherBodyPhysicsComp->setSpeed(otherBodyPhysicsComp->getSpeed() + (solveResult.velocity2 - otherBodyPhysicsComp->getSpeed()));
		
			if (bodyPhysicsComp->hasInfiniteMass())
			{

			}
		}




	}

}



