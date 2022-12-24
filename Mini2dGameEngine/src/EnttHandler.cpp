#include "EnttHandler.h"



EnttHandler::EnttHandler(Global& globalVariables)
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
	//Coll2d::runCollisionSystem(entityVec,global);
	for (int i = 0; i < entityVec.size(); i++)
	{
		if (entityVec.at(i) == nullptr)
			continue;
		entityVec.at(i)->process();

	}
}

void EnttHandler::physicsProcess()
{
	while (operateEnttMutex.try_lock())
	{

	}
	

	physicsClock.restart();

	std::vector<std::shared_ptr<C_Physics2d>> physicsCompVec;
	for (int i = 0; i < entityVec.size(); i++)
	{
		if (entityVec.at(i) == nullptr)
			continue;
		for (int j = 0; j < entityVec[i]->componentHandler.componentVec.size(); j++)
		{
			if (std::dynamic_pointer_cast<C_Physics2d> (entityVec[i]->componentHandler.componentVec[j]))
			{
				physicsCompVec.push_back(std::dynamic_pointer_cast<C_Physics2d> (entityVec[i]->componentHandler.componentVec[j]));
			}
		}
	}

	//double dtSubstep = 0.015;
	double startingTime = physicsClock.getElapsedTime().asSeconds() ;
	

	double currentTime = 0;
	
	for (uint8_t i = 0; i < global->physicsSubSteps; i++)
	{
		Coll2d::runCollisionSystem(physicsCompVec, substepDt, global);
		currentTime = physicsClock.getElapsedTime().asSeconds();
		double finishedCalcTime = physicsClock.getElapsedTime().asSeconds();
		while (currentTime < finishedCalcTime + substepDt)
		{
			currentTime = physicsClock.getElapsedTime().asSeconds();

		}

	}
	/*
	currentTime = physicsClock.getElapsedTime().asSeconds();
	while (currentTime < stepDt)
	{
		currentTime = physicsClock.getElapsedTime().asSeconds();

	}
	*/
	operateEnttMutex.unlock();

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
	for (int i = enttId; i < entityVec.size(); i++)
		entityVec.at(i)->id = i;

		
	operateEnttMutex.unlock();

}