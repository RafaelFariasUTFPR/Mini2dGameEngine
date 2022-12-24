#include "S_Collision2d.h"


void Coll2d::runCollisionSystem(std::vector<std::shared_ptr<C_Physics2d>> physicsCompVec, double dt, Global* global)
{
	for (int i = 0; i < physicsCompVec.size(); i++)
	{
		physicsCompVec.at(i)->processDeltaTime(dt);

		//Skipping if theres no vertex in the poligon
		if (!physicsCompVec.at(i)->collider->getCollisionPoligon().getVertexCount())
			continue;
		for (int i2 = 0; i2 < physicsCompVec.size(); i2++)
		{
			if (i2 == i)
				continue;

			
			//Otimização
			double influenceDist = physicsCompVec.at(i)->collider->influenceRadius + physicsCompVec.at(i2)->collider->influenceRadius;
			if (myMath::distBetweenPoints(physicsCompVec.at(i)->getTransform().position, physicsCompVec.at(i2)->getTransform().position) > influenceDist)
				continue;

			SAT::ColResult result = SAT::SATCollision(*physicsCompVec.at(i)->collider, *physicsCompVec.at(i2)->collider);

			// Talvez tirar isso
			//if (!physicsCompVec.at(i)->getIsDynamic())
			//	continue;

			if (result.result)
			{
				myMath::CollResult solveResult = myMath::calculateInelasticCollision(physicsCompVec.at(i)->getSpeed(), physicsCompVec.at(i)->mass, physicsCompVec.at(i2)->getSpeed(), physicsCompVec.at(i2)->mass, 1);
				if (physicsCompVec.at(i)->getIsDynamic())
				{
					physicsCompVec.at(i)->transform->position += result.displacement;
					physicsCompVec.at(i)->setSpeed(physicsCompVec.at(i)->getSpeed() + (solveResult.velocity1 - physicsCompVec.at(i)->getSpeed()));

				}
				if (physicsCompVec.at(i2)->getIsDynamic())
					physicsCompVec.at(i2)->setSpeed(physicsCompVec.at(i2)->getSpeed() + (solveResult.velocity2 - physicsCompVec.at(i2)->getSpeed()));


			}

		}




	}

}

