#include "MyMath.h"

namespace myMath
{
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
	sf::Vector2f rotatePointArrounPoint(sf::Vector2f myPoint, sf::Vector2f centerPoint, float rotationAngle)
	{
		// Convertendo de graus para radianos e invertendo o sentido de rotação
		rotationAngle = (rotationAngle) * (PI / 180);

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

	bool doLinesIntersect(sf::Vector2f p1, sf::Vector2f q1, sf::Vector2f p2, sf::Vector2f q2)
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

	sf::Vector2f calcDisplacement(sf::Vector2f p1, sf::Vector2f q1, sf::Vector2f p2, sf::Vector2f q2)
	{
	
		float h = (q2.x - p2.x) * (p1.y - q1.y) - (p1.x - q1.x) * (q2.y - p2.y);
		float t1 = ((p2.y - q2.y) * (p1.x - p2.x) + (q2.x - p2.x) * (p1.y - p2.y)) / h;
		float t2 = ((p1.y - q1.y) * (p1.x - p2.x) + (q1.x - p1.x) * (p1.y - p2.y)) / h;

		if (t1 >= 0.0f && t1 < 1.0f && t2 >= 0.0f && t2 < 1.0f)
		{
			float displacementX =  (1.0f - t1) * (q1.x - p1.x);
			float displacementY = (1.0f - t1) * (q1.y - p1.y);

			return sf::Vector2f(displacementX, displacementY);
		}
		return sf::Vector2f(0,0);
	}
	double deg2rad(double angle)
	{
		return angle * (PI / 180);
	}

	double distBetweenPoints(sf::Vector2f p1, sf::Vector2f p2)
	{
		float dx = p2.x - p1.x;
		float dy = p2.y - p1.y;
		double dist = sqrt(pow(dx, 2) + pow(dy, 2));
		return dist;
	}



	float DotProduct(sf::Vector2f v0, sf::Vector2f v1) {
		return v0.x * v1.x + v0.y * v1.y;
	}

	// Z coords of crossed vectors
	float CrossProduct(sf::Vector2f v0, sf::Vector2f v1) {
		return v0.x * v1.y - v0.y * v1.x;
	}

	float Distance(sf::Vector2f v0, sf::Vector2f v1) {
		return sqrtf((v0 - v1).x * (v0 - v1).x + (v0 - v1).y * (v0 - v1).y);
	}

	float Length(sf::Vector2f v) {
		return sqrtf(v.x * v.x + v.y * v.y);
	}

	sf::Vector2f Normalize(sf::Vector2f v) {
		float length = Length(v);

		return length ? v / length : sf::Vector2f();
	}

	sf::Vector2f GetCenter(sf::VertexArray body) {
		sf::Vector2f center;

		uint32_t count = body.getVertexCount();

		float A = 0.0f;

		float area = 0.0f;

		for (uint32_t i = 0; i < count; i++) {
			auto& v0 = body[i].position;
			auto& v1 = body[i + 1 != count ? i + 1 : 0].position;
			float b = myMath::CrossProduct(v0, v1);

			A += b;

			center += (v0 + v1) * b;
		}

		center *= 1.0f / (3.0f * A);

		return center;
	}

	/*
	sf::Vector2f VecAbs(sf::Vector2f v) {
		return sf::Vector2f
		{
			v.x < T(0) ? -v.x : v.x,
				v.y < T(0) ? -v.y : v.y
		};
	}
	*/

	sf::Vector2f GetReflection(sf::Vector2f v, sf::Vector2f normal)
	{
		sf::Vector2f reflection;
		v.x *= -1;
		v.y *= -1;
		reflection.x = (2 * (normal.x * v.x) * normal.x) - v.x;
		reflection.y = (2 * (normal.y * v.y) * normal.y) - v.y;

		return reflection;

	
	}



	CollResult calculateInelasticCollision(sf::Vector2f velocity1, float mass1, sf::Vector2f velocity2, float mass2, float elasticity)
	{
		CollResult result;
		
		//result.velocity1 = (((mass1 - mass2) / (mass1 + mass2)) * velocity1) + (((2*mass2)/(mass1 + mass2)) * velocity2);
		result.velocity1 = (mass1 * velocity1) + (mass2 * velocity2);
		result.velocity1 = result.velocity1 / (mass1 + mass2);


		
		//result.velocity2 = (((2 * mass1) / (mass1 + mass2)) * velocity1) + (((mass2 - mass1) / (mass1 + mass2)) * velocity2);

		return result;
	}

}