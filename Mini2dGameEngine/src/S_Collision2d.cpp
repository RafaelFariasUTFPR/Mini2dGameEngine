#include "S_Collision2d.h"

std::queue<Collision> Coll2d::threadedCollisionSystem(int id, uint32_t startIndex, uint8_t n_ofThreadsUsed, std::vector<std::shared_ptr<C_Collider2d>> colliderCompVec)
{
	std::queue<Collision> collisionsQueue;

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


			//Otimização
			double influenceDist = colliderCompVec.at(i)->influenceRadius + colliderCompVec.at(i2)->influenceRadius;
			if (myMath::distBetweenPoints(colliderCompVec.at(i)->getTransform().position, colliderCompVec.at(i2)->getTransform().position) > influenceDist)
				continue;

			// Calculando a colisão
			SAT::ColResult result = SAT::SATCollision(*colliderCompVec.at(i), *colliderCompVec.at(i2));


			// Se estiver colidindo
			if (result.result)
			{
				Collision coll;
				coll.myId = i;
				coll.otherId = i2;
				coll.collisionNormal = myMath::Normalize(result.displacement);
				coll.displacement = result.displacement;
				coll.collisionPoints = result.collisionPoints;


				collisionsQueue.push(coll);

			}

		}

	}

	return collisionsQueue;
}

std::queue<Collision> Coll2d::runCollisionSystem(std::vector<std::shared_ptr<C_Collider2d>> colliderCompVec, ctpl::thread_pool* threadPool, std::mutex* operateEnttMutex)
{
	operateEnttMutex->lock();

	
	std::queue<Collision> collisionsResult;



	// Colocando as tarefas na threadpool
	auto result1 = threadPool->push(threadedCollisionSystem, 0, COLL_NUMBER_OF_THREADS_USED, colliderCompVec);
	auto result2 = threadPool->push(threadedCollisionSystem, 1, COLL_NUMBER_OF_THREADS_USED, colliderCompVec);
	auto result3 = threadPool->push(threadedCollisionSystem, 2, COLL_NUMBER_OF_THREADS_USED, colliderCompVec);
	auto result4 = threadPool->push(threadedCollisionSystem, 3, COLL_NUMBER_OF_THREADS_USED, colliderCompVec);
	auto result5 = threadPool->push(threadedCollisionSystem, 4, COLL_NUMBER_OF_THREADS_USED, colliderCompVec);
	auto result6 = threadPool->push(threadedCollisionSystem, 5, COLL_NUMBER_OF_THREADS_USED, colliderCompVec);
	auto result7 = threadPool->push(threadedCollisionSystem, 6, COLL_NUMBER_OF_THREADS_USED, colliderCompVec);
	auto result8 = threadPool->push(threadedCollisionSystem, 7, COLL_NUMBER_OF_THREADS_USED, colliderCompVec);
	

	// Aguardar até que todos os threads terminem o seu trabalho
	// Fazendo isso para que o compilador não otimize esse while
	volatile int numberOfOccupiedThreads = threadPool->n_occupied();
	while (numberOfOccupiedThreads)
		numberOfOccupiedThreads = threadPool->n_occupied();




	operateEnttMutex->unlock();

	// Pegando os resultados dos auto e colocando em uma array
	std::queue<Collision> resultArr[] = {
		result1.get(),
		result2.get(),
		result3.get(),
		result4.get(),
		result5.get(),
		result6.get(),
		result7.get(),
		result8.get()
	};

	// Pegando todos os elementos dos resultados e colocando em uma fila
	for (uint8_t i = 0; i < COLL_NUMBER_OF_THREADS_USED; i++)
	{
		while (!resultArr[i].empty())
		{
			collisionsResult.push(resultArr[i].front());
			resultArr[i].pop();
		}
	}



	return collisionsResult;

}


void Coll2d::solvePhysicsCollisions(std::vector<std::shared_ptr<C_Physics2d>> physicsCompVec, std::queue<Collision>collisionsQueue, double dt)
{

	while (collisionsQueue.size())
	{
		Collision frontCollider = collisionsQueue.front();
		//if (physicsCompVec.at(collisionsVector.at(i).myId) == nullptr || physicsCompVec.at(collisionsVector.at(i).otherId) == nullptr)
		//	continue;

		
		std::shared_ptr<C_Physics2d> bodyPhysicsComp;
		std::shared_ptr<C_Physics2d> otherBodyPhysicsComp;


		// Pegando o componente C_Physics2d do boddy
		for (unsigned int j = 0; j < physicsCompVec.size(); j++)
		{
			if (physicsCompVec.at(j)->getMyId() == frontCollider.myId)
				bodyPhysicsComp = physicsCompVec.at(j);
			else if (physicsCompVec.at(j)->getMyId() == frontCollider.otherId)
				otherBodyPhysicsComp = physicsCompVec.at(j);
		}


		myMath::CollResult solveResult = myMath::calculateInelasticCollision(bodyPhysicsComp->getSpeed(), bodyPhysicsComp->mass, otherBodyPhysicsComp->getSpeed(), otherBodyPhysicsComp->mass, .8);


		
		if (bodyPhysicsComp->getIsDynamic())
		{
			// ###### TODO ######
			// refazer essa parte, pode criar uma função no physics componente
			// chamada applyImpuseAt, e esse fica responsavel por gerar torque e 
			// tudo mais

			float momentum = (pow(myMath::Length(bodyPhysicsComp->getSpeed()),2) * bodyPhysicsComp->mass) + (bodyPhysicsComp->mass * myMath::Length(bodyPhysicsComp->gravity));
			float momentumPerContactPoint = momentum / frontCollider.collisionPoints.size();
			for (int i = 0; i < frontCollider.collisionPoints.size(); i++)
			{
				float contactPointRadius = myMath::distBetweenPoints(frontCollider.collisionPoints.at(i), bodyPhysicsComp->getTransform().position);
				if((frontCollider.collisionPoints.at(i) - bodyPhysicsComp->getTransform().position).x > 0)
					bodyPhysicsComp->applyTorque(contactPointRadius, momentum * 20, -90);
				else
					bodyPhysicsComp->applyTorque(contactPointRadius, momentum * 20, 90);

			}
			
			// ###### #### ######
			
			bodyPhysicsComp->setPosition(bodyPhysicsComp->transform->position + frontCollider.displacement);

			if (otherBodyPhysicsComp->hasInfiniteMass())
			{
				bodyPhysicsComp->setSpeed(myMath::GetReflection(bodyPhysicsComp->getSpeed() * bodyPhysicsComp->elasticity, frontCollider.collisionNormal));

			}
			else
			{
				bodyPhysicsComp->setSpeed(myMath::GetReflection(solveResult.velocity1, frontCollider.collisionNormal));

			}

		}
		if (otherBodyPhysicsComp->getIsDynamic())
		{

			//otherBodyPhysicsComp->setSpeed(otherBodyPhysicsComp->getSpeed() + (solveResult.velocity2 - otherBodyPhysicsComp->getSpeed()));
		
			if (bodyPhysicsComp->hasInfiniteMass())
			{

			}
			else
			{
				//otherBodyPhysicsComp->setSpeed(myMath::GetReflection(solveResult.velocity1, frontCollider.collisionNormal));

			}
		}



		collisionsQueue.pop();
	}

}



