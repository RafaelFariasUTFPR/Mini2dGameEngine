#pragma once


#include <iostream>

#include "Global.h"
#include "MyMath.h"

class ComponentMaster
{
public:
	ComponentMaster(Global* globalVariables);

	virtual void beforePlay() {}
	virtual void beginPlay() {}
	virtual void process() {}
	virtual void endGame() {}
	virtual void draw() {}

	virtual myMath::Transform getTransform() { return transform; }
	void setTransform(myMath::Transform _transform) { transform = _transform; }

	bool controlsTransform = false;

protected:
	myMath::Transform transform;
	Global* global;

	//Standard Variables

};

