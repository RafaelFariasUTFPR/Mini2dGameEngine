#pragma once
#include <SFML/Graphics.hpp>

class Global
{
public:
	Global();


	int initialWidth;
	int initialHeight;
	std::string windowName;
	sf::Clock deltaClock;
	sf::RenderWindow window;
	sf::Event events;

};

