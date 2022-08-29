#pragma once

#include <vector>
#include <iostream>

#include "EntityMaster.h"
#include "Cube.h"


class EnttHandler
{
public:
	EnttHandler(Global& globalVariables);


	void beforePlay();
	void beginPlay();
	void process();
	void draw();
	void endGame();


	void addEntt(EntityMaster* entity);
	void deleteEntt(int enttId);

	EntityMaster* getEntityAt(int index) 
	{
		return entityVec.at(index);
	}

	int getEntityVecSize() { return entityVec.size(); }


private:
	Global* global;
	
	std::vector<EntityMaster*>entityVec;

};

