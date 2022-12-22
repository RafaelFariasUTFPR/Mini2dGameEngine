#include "EnttHandler.h"



EnttHandler::EnttHandler(Global& globalVariables)
{
	global = &globalVariables;

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
	Coll2d::runCollisionSystem(entityVec, global);


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
	if (entityVec.size() == 0)
		return;
	
	entityVec.erase(entityVec.begin() + enttId);
	for (int i = enttId; i < entityVec.size(); i++)
		entityVec.at(i)->id = i;
	
	
}