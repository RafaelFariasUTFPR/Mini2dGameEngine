#include "S_Collision2d.h"

std::vector<Collision> Coll2d::threadedCollisionSystem(int id, uint32_t startIndex, uint8_t n_ofThreadsUsed, std::vector<std::shared_ptr<C_Collider2d>> colliderCompVec)
{
	std::vector<Collision> collisionsVector;

	for (int i = startIndex; i < colliderCompVec.size(); i += n_ofThreadsUsed)
	{
		if (i >= colliderCompVec.size())
			break;
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
				//colliderCompVec.at(i)->addCollisions(coll);



				collisionsVector.push_back(coll);

			}

		}

	}
	/*
	std::cout << resultCollisionVector->size() << "Coll\n";
	while (colliderCompVec.size())
	{
		resultCollisionVector->push(collisionsVector.front());
		collisionsVector.pop();
	}
	*/
	return collisionsVector;
}

std::vector<Collision> Coll2d::runCollisionSystem(std::vector<std::shared_ptr<C_Collider2d>> colliderCompVec, ctpl::thread_pool* threadPool, std::mutex* operateEnttMutex)
{
	//bool locked = operateEnttMutex->try_lock();
	bool locked = true;
	operateEnttMutex->lock();

	
	std::vector<Collision> collisionsResult;


	uint8_t numberOfThreadsUseds = 8;




	auto result1 = threadPool->push(threadedCollisionSystem, 0, numberOfThreadsUseds, colliderCompVec);
	auto result2 = threadPool->push(threadedCollisionSystem, 1, numberOfThreadsUseds, colliderCompVec);
	auto result3 = threadPool->push(threadedCollisionSystem, 2, numberOfThreadsUseds, colliderCompVec);
	auto result4 = threadPool->push(threadedCollisionSystem, 3, numberOfThreadsUseds, colliderCompVec);
	auto result5 = threadPool->push(threadedCollisionSystem, 4, numberOfThreadsUseds, colliderCompVec);
	auto result6 = threadPool->push(threadedCollisionSystem, 5, numberOfThreadsUseds, colliderCompVec);
	auto result7 = threadPool->push(threadedCollisionSystem, 6, numberOfThreadsUseds, colliderCompVec);
	auto result8 = threadPool->push(threadedCollisionSystem, 7, numberOfThreadsUseds, colliderCompVec);


	
	//threadPool->push(threadedCollisionSystem, 0, colliderCompVec.size(), colliderCompVec, &vectorOfCollisionsVector.at(currentIteration));

	

	// Fazendo isso para que o compilador não otimize esse while
	volatile int numberOfOccupiedThreads = threadPool->n_occupied();
	while (numberOfOccupiedThreads)
	{
		numberOfOccupiedThreads = threadPool->n_occupied();
		
	}






	std::vector<Collision> vec1 = result1.get();
	std::vector<Collision> vec2 = result2.get();
	std::vector<Collision> vec3 = result3.get();
	std::vector<Collision> vec4 = result4.get();
	std::vector<Collision> vec5 = result5.get();
	std::vector<Collision> vec6 = result6.get();
	std::vector<Collision> vec7 = result7.get();
	std::vector<Collision> vec8 = result8.get();



	for (int i = 0; i < vec1.size(); i++)
		collisionsResult.push_back(vec1.at(i));
	for (int i = 0; i < vec2.size(); i++)
		collisionsResult.push_back(vec2.at(i));
	for (int i = 0; i < vec3.size(); i++)
		collisionsResult.push_back(vec3.at(i));
	for (int i = 0; i < vec4.size(); i++)
		collisionsResult.push_back(vec4.at(i));
	for (int i = 0; i < vec5.size(); i++)
		collisionsResult.push_back(vec5.at(i));
	for (int i = 0; i < vec6.size(); i++)
		collisionsResult.push_back(vec6.at(i));
	for (int i = 0; i < vec7.size(); i++)
		collisionsResult.push_back(vec7.at(i));
	for (int i = 0; i < vec8.size(); i++)
		collisionsResult.push_back(vec8.at(i));

	if (locked)
		operateEnttMutex->unlock();




	return collisionsResult;

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



