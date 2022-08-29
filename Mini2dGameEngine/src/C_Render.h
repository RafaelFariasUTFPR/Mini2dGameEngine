#pragma once

#include <SFML/Graphics.hpp>


#include "ComponentMaster.h"

class C_Render :
    public ComponentMaster
{
public:
    C_Render(Global* globalVariables, std::string texturePath);

    void draw() override;
    sf::Texture texture;
    sf::Sprite sprite;
private:
    sf::VertexArray vertexArr;


};

