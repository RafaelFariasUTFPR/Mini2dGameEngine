#include "S_Collision2d.h"


std::vector<Collision> Coll2d::runCollisionSystem(std::vector<std::shared_ptr<C_Collider2d>> colliderCompVec)
{
	std::vector<Collision> collisionsVector;
	for (int i = 0; i < colliderCompVec.size(); i++)
	{
		//Skipping if theres no vertex in the poligon
		if (!colliderCompVec.at(i)->getCollisionPoligon().getVertexCount())
			continue;
		for (int i2 = 0; i2 < colliderCompVec.size(); i2++)
		{
			if (i2 == i)
				continue;

			//Otimização
			double influenceDist = colliderCompVec.at(i)->influenceRadius + colliderCompVec.at(i2)->influenceRadius;
			if (myMath::distBetweenPoints(colliderCompVec.at(i)->getTransform().position, colliderCompVec.at(i2)->getTransform().position) > influenceDist)
				continue;

			SAT::ColResult result = SAT::SATCollision(*colliderCompVec.at(i), *colliderCompVec.at(i2));

			// Talvez tirar isso
			//if (!physicsCompVec.at(i)->getIsDynamic())
			//	continue;

			if (result.result)
			{
				//myMath::CollResult solveResult = myMath::calculateInelasticCollision(physicsCompVec.at(i)->getSpeed(), physicsCompVec.at(i)->mass, physicsCompVec.at(i2)->getSpeed(), physicsCompVec.at(i2)->mass, 1);
				
				Collision coll;
				coll.myId = i;
				coll.otherId = i2;
				//coll.collisionNormal
				//coll.otherCollider = colliderCompVec.at(i2);
				coll.displacement = result.displacement;

				colliderCompVec.at(i)->addCollisions(coll);
				collisionsVector.push_back(coll);
			}

		}

	}

	return collisionsVector;

}


void Coll2d::solvePhysicsCollisions(std::vector<std::shared_ptr<EntityMaster>> entityVec, std::vector<Collision>collisionsVector, double dt)
{
	for (unsigned int i = 0; i < collisionsVector.size(); i++)
	{
		if (entityVec.at(collisionsVector.at(i).myId) == nullptr || entityVec.at(collisionsVector.at(i).otherId) == nullptr)
			continue;
		std::shared_ptr<EntityMaster> body = entityVec.at(collisionsVector.at(i).myId);
		std::shared_ptr<EntityMaster> otherBody = entityVec.at(collisionsVector.at(i).otherId);

		//printf("%u && %u\n", body->id, otherBody->id);
		
		std::shared_ptr<C_Physics2d> bodyPhysicsComp;
		std::shared_ptr<C_Physics2d> otherBodyPhysicsComp;


		// Pegando o componente C_Physics2d do boddy
		for (unsigned int j = 0; j < body->componentHandler.componentVec.size(); j++)
			if (std::dynamic_pointer_cast<C_Physics2d> (body->componentHandler.componentVec[j]))
				bodyPhysicsComp = std::dynamic_pointer_cast<C_Physics2d> (body->componentHandler.componentVec[j]);
		
		// Pegando o componente C_Physics2d do otherBody
		for (unsigned int j = 0; j < otherBody->componentHandler.componentVec.size(); j++)
			if (std::dynamic_pointer_cast<C_Physics2d> (otherBody->componentHandler.componentVec[j]))
				otherBodyPhysicsComp = std::dynamic_pointer_cast<C_Physics2d> (otherBody->componentHandler.componentVec[j]);


		myMath::CollResult solveResult = myMath::calculateInelasticCollision(bodyPhysicsComp->getSpeed(), bodyPhysicsComp->mass, otherBodyPhysicsComp->getSpeed(), otherBodyPhysicsComp->mass, 1);


		if (bodyPhysicsComp->getIsDynamic())
		{
			bodyPhysicsComp->setPosition(bodyPhysicsComp->transform->position + collisionsVector.at(i).displacement);
			bodyPhysicsComp->setSpeed(bodyPhysicsComp->getSpeed() + (solveResult.velocity1 - bodyPhysicsComp->getSpeed()));

		}
		if (otherBodyPhysicsComp->getIsDynamic())
		{

			otherBodyPhysicsComp->setSpeed(otherBodyPhysicsComp->getSpeed() + (solveResult.velocity2 - otherBodyPhysicsComp->getSpeed()));
		}




	}

}



