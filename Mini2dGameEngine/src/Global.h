#pragma once
#include <SFML/Graphics.hpp>

#define PI 3.14159265

namespace math
{
struct Transform
{
	sf::Vector2f position = sf::Vector2f(0, 0);
	sf::Vector2f scale = sf::Vector2f(1,1);
	double rotation = 0;
};

}

class Global
{
public:
	Global();


	int initialWidth;
	int initialHeight;
	double deltaTime;
	std::string windowName;
	sf::Clock deltaClock;
	sf::RenderWindow window;
	sf::Event events;

};

