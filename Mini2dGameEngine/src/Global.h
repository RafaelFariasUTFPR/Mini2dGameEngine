#pragma once
#include <SFML/Graphics.hpp>

#include <mutex>


namespace render {
	typedef struct RenderArray {
		sf::VertexArray vArray;
		uint16_t textureNumber;
		sf::RenderStates renderState;
		

	} RederArray;



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
	
	render::RenderArray sceneArray;
	render::RenderArray sceneBuffer;
	//unsigned int tileSize = 256;

	std::vector <sf::VertexArray> debugVertexArray;
	std::vector <sf::VertexArray> physicsThreadDebugVertexArray;

	std::mutex m;



};
