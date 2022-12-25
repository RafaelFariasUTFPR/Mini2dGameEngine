#include "C_Collider2d.h"

C_Collider2d::C_Collider2d(sf::VertexArray _collisionVertexArray) : ComponentMaster()
{
	setCollisionPoligon(_collisionVertexArray);

}

C_Collider2d::C_Collider2d()
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

	ComponentMaster::process();
}

void C_Collider2d::fixedProcess(double deltaTime)
{
	updatePosition();

	ComponentMaster::fixedProcess(deltaTime);
}

void C_Collider2d::updatePosition()
{
	collisionPoligon = collisionVertexArray;

	for (int i = 0; i < collisionPoligon.getVertexCount(); i++)
	{
		collisionPoligon[i].position += transform->position;
		collisionPoligon[i].position = myMath::rotatePointArrounPoint(collisionPoligon[i].position, transform->position, transform->rotation);
	}

	if (drawDebug)
	{
		collisionDebugVertexArray = collisionPoligon;
		collisionDebugVertexArray.append(collisionPoligon[0]);

	}

}

void C_Collider2d::draw()
{
	if (drawDebug && collisionPoligon.getVertexCount())
	{
		global->window.draw(collisionDebugVertexArray);
	}

	ComponentMaster::draw();
}