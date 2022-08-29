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
	for (int i = 0; i < entityVec.size(); i++)
	{
		entityVec.at(i)->process();
	}
}

void EnttHandler::draw()
{
	for (int i = 0; i < entityVec.size(); i++)
	{
		entityVec.at(i)->draw();
	}
}

void EnttHandler::endGame()
{
	for (int i = 0; i < entityVec.size(); i++)
	{
		entityVec.at(i)->endGame();
	}
}

void EnttHandler::addEntt(EntityMaster* entity)
{
	entity->id = entityVec.size();
	entityVec.push_back(entity);
}
void EnttHandler::deleteEntt(int enttId)
{
	if (entityVec.size() == 0)
		return;
	
	delete entityVec.at(enttId);
	entityVec.erase(entityVec.begin() + enttId);
	for (int i = enttId; i < entityVec.size(); i++)
		entityVec.at(i)->id = i;
	
	
	
}