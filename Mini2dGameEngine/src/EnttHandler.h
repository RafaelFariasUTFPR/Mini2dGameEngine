#pragma once

#include <vector>
#include <iostream>



#include "EntityMaster.h"
#include "entts/Cube.h"
#include "C_Collider2d.h"

#include "S_Collision2d.h"


class EnttHandler
{
public:
	EnttHandler(Global& globalVariables);


	void beforePlay();
	void beginPlay();
	void physicsProcess();
	void threadPhysicsProcess();

	void process();
	void draw();
	void endGame();


	void addEntt(std::shared_ptr<EntityMaster> entity);


	void deleteEntt(int enttId);

	std::shared_ptr<EntityMaster> getEntityAt(int index)
	{
		return entityVec.at(index);

	}

	int getEntityVecSize() { return entityVec.size(); }


private:
	Global* global;
	
	std::vector<std::shared_ptr<EntityMaster>> entityVec;

};

