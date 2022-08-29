#include "C_RenderSprite.h"

C_RenderSprite::C_RenderSprite(Global* globalVariables, std::string texturePath, sf::Vector2f scale) : ComponentMaster(globalVariables)
{

    texture.loadFromFile(texturePath);
    sprite.setTexture(texture);
    sprite.setScale(scale);
    //sprite.setPosition(sf::Vector2f(400, 400));


    /*
    vertexArr.setPrimitiveType(sf::LinesStrip);

    //Gerando o formato da nave
    vertexArr.append(sf::Vertex(sf::Vector2f(-5, 5), sf::Color::White));
    vertexArr.append(sf::Vertex(sf::Vector2f(0, -10), sf::Color::White));
    vertexArr.append(sf::Vertex(sf::Vector2f(5, 5), sf::Color::White));
    vertexArr.append(sf::Vertex(sf::Vector2f(-5, 5), sf::Color::White));
    
    */
}

void C_RenderSprite::draw()
{
    global->window.draw(sprite);
    ComponentMaster::draw();
}

void C_RenderSprite::process()
{

    sprite.setScale(transform.scale);
    sprite.setPosition(transform.position);
    sprite.setRotation(transform.rotation);
    ComponentMaster::process();
}