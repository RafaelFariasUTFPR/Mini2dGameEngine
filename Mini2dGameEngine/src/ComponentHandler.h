#pragma once

#include <vector>
#include <iostream>
#include <memory>

#include "ComponentMaster.h"
#include "Global.h"
#include "MyMath.h"
class ComponentHandler
{
public:
	ComponentHandler(Global* globalVariables, myMath::Transform* enttTransform);
	~ComponentHandler();

	void beforePlay();
	void beginPlay();
	void process();
	void draw();
	void endGame();

	void addComponent(std::shared_ptr<ComponentMaster> component);



	std::vector<std::shared_ptr<ComponentMaster>> componentVec;

private:
	Global* global;
	myMath::Transform* transform;

};

