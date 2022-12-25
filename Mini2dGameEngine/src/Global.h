#pragma once
#include <SFML/Graphics.hpp>



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

	// Numero de subPassos para cada tick da simulação fisica
	uint16_t physicsSubSteps = 2;
	float actualPhysicsUpdateTime;
	
	render::RenderArray sceneArray;
	render::RenderArray sceneBuffer;

	std::vector <sf::VertexArray> debugVertexArray;
	std::vector <sf::VertexArray> physicsThreadDebugVertexArray;




};
