#include "C_Collider2d.h"

C_Collider2d::C_Collider2d(Global* globalVariables, sf::VertexArray _collisionVertexArray) : ComponentMaster(globalVariables)
{
	setCollisionPoligon(_collisionVertexArray);

}

C_Collider2d::C_Collider2d(Global* globalVariables) : ComponentMaster(globalVariables)
{

}

void C_Collider2d::setCollisionPoligon(sf::VertexArray _collisionVertexArray)
{
	collisionVertexArray = _collisionVertexArray;
	collisionVertexArray.setPrimitiveType(sf::LineStrip);

	for (int i = 0; i < collisionVertexArray.getVertexCount() - 1; i++)
	{
		double dist = myMath::distBetweenPoints(sf::Vector2f(0, 0), collisionVertexArray[i].position);
		if (dist > influenceRadius)
			influenceRadius = dist;
	}


}


void C_Collider2d::process()
{
	collisionPoligon = collisionVertexArray;


	for (int i = 0; i < collisionPoligon.getVertexCount(); i++)
	{
		collisionPoligon[i].position += transform.position;
		collisionPoligon[i].position = myMath::rotatePointArrounPoint(collisionPoligon[i].position, transform.position, transform.rotation);
	}


	ComponentMaster::process();
}


void C_Collider2d::draw()
{
	if (drawDebug && collisionPoligon.getVertexCount())
	{
		sf::VertexArray collisionDebugVertexArray = collisionPoligon;
		collisionDebugVertexArray.append(collisionPoligon[0]);

		global->window.draw(collisionDebugVertexArray);

	}

	ComponentMaster::draw();
}