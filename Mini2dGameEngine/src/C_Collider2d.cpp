#include "C_Collider2d.h"

C_Collider2d::C_Collider2d(Global* globalVariables, sf::VertexArray& _collisionVertexArray) : ComponentMaster(globalVariables)
{
	collisionVertexArray = &_collisionVertexArray;
	collisionVertexArray -> setPrimitiveType(sf::LinesStrip);
	

}

void C_Collider2d::process()
{
	collisionPoligon = *collisionVertexArray;

	for (int i = 0; i < collisionPoligon.getVertexCount(); i++)
		collisionPoligon[i].position += transform.position;


	ComponentMaster::process();
}


void C_Collider2d::draw()
{

	if (drawDebug)
		global->window.draw(collisionPoligon);

	ComponentMaster::draw();
}