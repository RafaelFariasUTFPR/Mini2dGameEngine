#pragma once

#include <SFML/Graphics.hpp>


#include "ComponentMaster.h"

class C_RenderSprite :
    public ComponentMaster
{
public:
    C_RenderSprite(Global* globalVariables, std::string texturePath, sf::Vector2f scale);

    void process() override;
    void draw() override;

    sf::Texture texture;
    sf::Sprite sprite;
private:
    sf::VertexArray vertexArr;


};

