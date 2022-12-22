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
			if (myMath::distBetweenPoints(physicsCompVec.at(i)->transform.position, physicsCompVec.at(i2)->transform.position) > influenceDist)
				continue;

			SAT::ColResult result = SAT::SATCollision(*physicsCompVec.at(i)->collider, *physicsCompVec.at(i2)->collider);

			// Talvez tirar isso
			if (!physicsCompVec.at(i)->getIsDynamic())
				continue;

			if (result.result)
				physicsCompVec.at(i)->transform.position += result.displacement;
			//std::cout << result.result << std::endl;

		}




	}

}

