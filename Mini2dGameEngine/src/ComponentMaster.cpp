#include "ComponentMaster.h"

ComponentMaster::ComponentMaster()
{

}

void ComponentMaster::setPointers(Global* globalVariables, myMath::Transform* enttTransform, uint32_t* _myId, bool* _isDynamic)
{
	global = globalVariables;
	transform = enttTransform;
	myId = _myId;
	isDynamic = _isDynamic;
}
