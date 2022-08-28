#pragma once

#include <vector>
#include <iostream>

#include "EntityMaster.h"
#include "Cube.h"


class EnttHandler
{
public:
	EnttHandler(Global& globalVariables);


	void beginPlay();



private:
	Global* global;
	std::vector<EntityMaster*>entityVec;

};

