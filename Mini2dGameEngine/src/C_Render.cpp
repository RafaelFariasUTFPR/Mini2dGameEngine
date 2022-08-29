#include "C_Render.h"

C_Render::C_Render(Global* globalVariables, std::string texturePath) : ComponentMaster(globalVariables)
{

    texture.loadFromFile(texturePath);
    sprite.setTexture(texture);
    sprite.setScale(sf::Vector2f(10, 10));
    sprite.setPosition(sf::Vector2f(400, 400));


    /*
    vertexArr.setPrimitiveType(sf::LinesStrip);

    //Gerando o formato da nave
    vertexArr.append(sf::Vertex(sf::Vector2f(-5, 5), sf::Color::White));
    vertexArr.append(sf::Vertex(sf::Vector2f(0, -10), sf::Color::White));
    vertexArr.append(sf::Vertex(sf::Vector2f(5, 5), sf::Color::White));
    vertexArr.append(sf::Vertex(sf::Vector2f(-5, 5), sf::Color::White));
    
    */
}

void C_Render::draw()
{
    global->window.draw(sprite);
}