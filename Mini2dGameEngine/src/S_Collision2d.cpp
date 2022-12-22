#include "S_Collision2d.h"


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

		for (int i2 = 0; i2 < physicsCompVec.size(); i2++)
		{
			if (i2 == i)
				continue;

			//Otimização
			double influenceDist = physicsCompVec.at(i)->collider->influenceRadius + physicsCompVec.at(i2)->collider->influenceRadius;
			if (myMath::distBetweenPoints(physicsCompVec.at(i)->transform.position, physicsCompVec.at(i2)->transform.position) > influenceDist)
				continue;

			SAT::ColResult result = SAT::SATCollision(*physicsCompVec.at(i)->collider, *physicsCompVec.at(i2)->collider);

			if (result.result)
				physicsCompVec.at(i)->transform.position += result.displacement;
			std::cout << result.result << std::endl;

		}




	}

}

