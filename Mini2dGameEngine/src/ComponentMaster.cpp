#include "ComponentMaster.h"

ComponentMaster::ComponentMaster()
{

}

void ComponentMaster::setPointers(Global* globalVariables, myMath::Transform* enttTransform, uint32_t* _myId)
{
	global = globalVariables;
	transform = enttTransform;
	myId = _myId;
}
