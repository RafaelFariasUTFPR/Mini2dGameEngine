#pragma once

#include <vector>
#include <iostream>
#include <memory>

#include "ComponentMaster.h"
#include "Global.h"

class ComponentHandler
{
public:
	ComponentHandler(Global* globalVariables);
	~ComponentHandler();

	void beforePlay();
	void beginPlay();
	void process();
	void draw();
	void endGame();

	void addComponent(std::shared_ptr<ComponentMaster> component);


	//Standard Variables
	myMath::Transform transform;

	std::vector<std::shared_ptr<ComponentMaster>> componentVec;

private:
	Global* global;

};

