#pragma once


#include <iostream>


#include "Global.h"
#include "MyMath.h"

class ComponentMaster
{
public:
	ComponentMaster();

	virtual void beforePlay() {}
	virtual void beginPlay() {}
	virtual void process() {}
	virtual void processDeltaTime(double deltaTime) {}
	virtual void endGame() {}
	virtual void draw() {}

	void setPointers(Global* globalVariables, myMath::Transform* enttTransform);

	virtual myMath::Transform getTransform() { return *transform; }
	void setTransform(myMath::Transform _transform) { *transform = _transform; }

	bool controlsTransform = false;
	myMath::Transform* transform;

protected:
	Global* global;
};

