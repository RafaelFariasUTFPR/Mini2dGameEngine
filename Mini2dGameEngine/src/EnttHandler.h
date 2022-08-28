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



private:
	Global* global;
	std::vector<EntityMaster*>entityVec;

};

