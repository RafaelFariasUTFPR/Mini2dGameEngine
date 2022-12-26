#include "EnttHandler.h"



EnttHandler::EnttHandler(Global& globalVariables) : threadPool(std::thread::hardware_concurrency())
{
	global = &globalVariables;
	substepDt = stepDt / global->physicsSubSteps;

}

void EnttHandler::beforePlay()
{
	for (int i = 0; i < entityVec.size(); i++)
	{
		entityVec.at(i)->beforePlay();
	}
}

void EnttHandler::beginPlay()
{
	for (int i = 0; i < entityVec.size(); i++)
	{
		entityVec.at(i)->beginPlay();
	}
}

void EnttHandler::process()
{
	for (int i = 0; i < entityVec.size(); i++)
	{
		if (entityVec.at(i) == nullptr)
			continue;
		entityVec.at(i)->process();

	}
}

void EnttHandler::physicsProcess()
{

	physicsClock.restart();
	colliderCompVec.clear();
	std::vector<std::shared_ptr<C_Physics2d>> physicsCompVec;

	operateEnttMutex.lock();

	for (int i = 0; i < entityVec.size(); i++)
	{
		if (entityVec.at(i) == nullptr)
			continue;
		for (int j = 0; j < entityVec[i]->componentHandler.componentVec.size(); j++)
		{
			//Pegando os componentes C_Collider2d e colocando em um vetor
			if (std::dynamic_pointer_cast<C_Collider2d> (entityVec[i]->componentHandler.componentVec[j]))
				colliderCompVec.push_back(std::dynamic_pointer_cast<C_Collider2d> (entityVec[i]->componentHandler.componentVec[j]));


			if (std::dynamic_pointer_cast<C_Physics2d> (entityVec[i]->componentHandler.componentVec[j]))
				physicsCompVec.push_back(std::dynamic_pointer_cast<C_Physics2d> (entityVec[i]->componentHandler.componentVec[j]));
		
		}

	}
	operateEnttMutex.unlock();


	
	double currentTime = 0;
	
	for (uint8_t i = 0; i < global->physicsSubSteps; i++)
	{
		
		
		collisionsQueue = Coll2d::runCollisionSystem(colliderCompVec, &threadPool, &operateEnttMutex);


		operateEnttMutex.lock();

		Coll2d::solvePhysicsCollisions(physicsCompVec, collisionsQueue, stepDt);



		// Chamando o physics process em todos os componentes
		
		for (unsigned int j = 0; j < entityVec.size(); j++)
		{
			if (entityVec.at(j) == nullptr)
				continue;
			entityVec.at(j)->fixedProcess(stepDt);
		}
		operateEnttMutex.unlock();

		
		// Travando o update
		currentTime = physicsClock.getElapsedTime().asSeconds();
		double finishedCalcTime = currentTime + substepDt;
		while (currentTime < finishedCalcTime)
			currentTime = physicsClock.getElapsedTime().asSeconds();


	}



	/*
	currentTime = physicsClock.getElapsedTime().asSeconds();
	while (currentTime < stepDt)
	{
		currentTime = physicsClock.getElapsedTime().asSeconds();

	}
	*/

	global->actualPhysicsUpdateTime = currentTime;
	//printf("Number of steps %u\n", numberOfSubSteps);
}

void EnttHandler::draw()
{
	for (int i = 0; i < entityVec.size(); i++)
	{
		if (entityVec.at(i) == nullptr)
			continue;
		entityVec.at(i)->draw();
	}
}

void EnttHandler::endGame()
{
	for (int i = 0; i < entityVec.size(); i++)
	{
		if (entityVec.at(i) == nullptr)
			continue;
		entityVec.at(i)->endGame();
	}
}

void EnttHandler::addEntt(std::shared_ptr<EntityMaster> entity)
{

	entity->id = entityVec.size();
	entityVec.push_back(entity);

}


void EnttHandler::deleteEntt(int enttId)
{
	operateEnttMutex.lock();


	if (entityVec.size() == 0)
	{
		operateEnttMutex.unlock();
		return;
	}
	entityVec.erase(entityVec.begin() + enttId);
	operateEnttMutex.unlock();
}