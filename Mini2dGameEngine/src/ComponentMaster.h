#pragma once


#include <iostream>

#include "Global.h"

class ComponentMaster
{
public:
	ComponentMaster(Global* globalVariables);

	virtual void beforePlay() {}
	virtual void beginPlay() {}
	virtual void process() {}
	virtual void endGame() {}
	virtual void draw() {}

	virtual math::Transform getTransform() { return transform; }
	void setTransform(math::Transform _transform) { transform = _transform; }

	bool controlsTransform = false;

protected:
	math::Transform transform;
	Global* global;

	//Standard Variables

};

