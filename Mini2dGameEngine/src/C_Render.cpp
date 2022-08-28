#include "C_Render.h"

C_Render::C_Render(Global* globalVariables) : ComponentMaster(globalVariables)
{
    vertexArr.setPrimitiveType(sf::LinesStrip);

    //Gerando o formato da nave
    vertexArr.append(sf::Vertex(sf::Vector2f(-5, 5), sf::Color::White));
    vertexArr.append(sf::Vertex(sf::Vector2f(0, -10), sf::Color::White));
    vertexArr.append(sf::Vertex(sf::Vector2f(5, 5), sf::Color::White));
    vertexArr.append(sf::Vertex(sf::Vector2f(-5, 5), sf::Color::White));
}

void C_Render::draw()
{
    std::cout << "Draw cube\n";
    global->window.draw(vertexArr);
}