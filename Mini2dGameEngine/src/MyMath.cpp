#include "MyMath.h"

using namespace myMath;


bool onSegment(sf::Vector2f p, sf::Vector2f q, sf::Vector2f r)
{
	if (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
		q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y))
		return true;

	return false;
}

int orientation(sf::Vector2f p, sf::Vector2f q, sf::Vector2f r)
{
	// See https://www.geeksforgeeks.org/orientation-3-ordered-points/
	// for details of below formula.
	int val = (q.y - p.y) * (r.x - q.x) -
		(q.x - p.x) * (r.y - q.y);

	if (val == 0) return 0;  // collinear

	return (val > 0) ? 1 : 2; // clock or counterclock wise
}
sf::Vector2f myMath::rotatePointArrounPoint(sf::Vector2f myPoint, sf::Vector2f centerPoint, float rotationAngle)
{
	// Convertendo de graus para radianos e invertendo o sentido de rotação
	rotationAngle = (-rotationAngle) * (PI / 180);

	float s = sin(rotationAngle);
	float c = cos(rotationAngle);

	// Retornando o ponto para 0,0
	myPoint.x -= centerPoint.x;
	myPoint.y -= centerPoint.y;

	// Rotacionando
	float xnew = myPoint.x * c - myPoint.y * s;
	float ynew = myPoint.x * s + myPoint.y * c;

	// Levando o ponto de volta para a posição original
	myPoint.x = xnew + centerPoint.x;
	myPoint.y = ynew + centerPoint.y;

	return myPoint;
}

bool myMath::doLinesIntersect(sf::Vector2f p1, sf::Vector2f q1, sf::Vector2f p2, sf::Vector2f q2)
{

	// Find the four orientations needed for general and
	// special cases
	int o1 = orientation(p1, q1, p2);
	int o2 = orientation(p1, q1, q2);
	int o3 = orientation(p2, q2, p1);
	int o4 = orientation(p2, q2, q1);

	// General case
	if (o1 != o2 && o3 != o4)
		return true;

	// Special Cases
	// p1, q1 and p2 are collinear and p2 lies on segment p1q1
	if (o1 == 0 && onSegment(p1, p2, q1)) return true;

	// p1, q1 and q2 are collinear and q2 lies on segment p1q1
	if (o2 == 0 && onSegment(p1, q2, q1)) return true;

	// p2, q2 and p1 are collinear and p1 lies on segment p2q2
	if (o3 == 0 && onSegment(p2, p1, q2)) return true;

	// p2, q2 and q1 are collinear and q1 lies on segment p2q2
	if (o4 == 0 && onSegment(p2, q1, q2)) return true;

	return false; // Doesn't fall in any of the above cases
}
double myMath::deg2rad(double angle)
{
	return angle * (PI / 180);
}


