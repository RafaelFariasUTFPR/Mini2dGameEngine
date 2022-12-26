#include "S_Collision2d.h"

std::vector<Collision> Coll2d::threadedCollisionSystem(int id, uint32_t startIndex, uint32_t endIndex, std::vector<std::shared_ptr<C_Collider2d>> colliderCompVec)
{
	std::vector<Collision> collisionsVector;

	for (int i = startIndex; i < endIndex; i++)
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

	
	std::vector<Collision> collisionsVector;
	uint16_t numberOfColliderPerThread = 5;

	uint16_t remainig = colliderCompVec.size() % numberOfColliderPerThread;

	uint16_t numberOfThreadsNecessary = (colliderCompVec.size() - remainig) / numberOfColliderPerThread;
	if (remainig)
		numberOfThreadsNecessary++;

	std::vector<std::vector<Collision>> vectorOfCollisionsVector(numberOfThreadsNecessary);

	uint32_t currentIteration = 0;
	
	/*
	for (uint32_t i = 0; i < colliderCompVec.size() - remainig; i += numberOfColliderPerThread)
	{
		threadPool->push(threadedCollisionSystem, i, i + numberOfColliderPerThread, colliderCompVec, &vectorOfCollisionsVector.at(currentIteration));
		currentIteration++;
	}

	threadPool->push(threadedCollisionSystem, colliderCompVec.size() - remainig, colliderCompVec.size(), colliderCompVec, &vectorOfCollisionsVector.at(currentIteration));
	*/
	std::vector<Collision> colVect;
	auto f1 = threadPool->push(threadedCollisionSystem, 0, colliderCompVec.size(), colliderCompVec);
	//threadPool->push(threadedCollisionSystem, 0, colliderCompVec.size(), colliderCompVec, &vectorOfCollisionsVector.at(currentIteration));

	colVect = f1.get();

	// Fazendo isso para que o compilador não otimize esse while
	volatile int numberOfOccupiedThreads = threadPool->n_occupied();
	while (numberOfOccupiedThreads)
	{
		numberOfOccupiedThreads = threadPool->n_occupied();
		
	}

	collisionsVector = colVect;

	//collisionsVector = colVec;
	/*
	for (uint16_t i = 0; i < 1; i++)
	{
		for(int j = 0; j < vectorOfCollisionsVector.at(i).size(); j++)
			collisionsVector.push_back(vectorOfCollisionsVector.at(i).at(j));
	}
	//ollisionsVector.push_back(colVec);
	*/

	if (locked)
		operateEnttMutex->unlock();

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



