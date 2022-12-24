#include "ComponentMaster.h"

ComponentMaster::ComponentMaster()
{

}

void ComponentMaster::setPointers(Global* globalVariables, myMath::Transform* enttTransform)
{
	global = globalVariables;
	transform = enttTransform;
}
