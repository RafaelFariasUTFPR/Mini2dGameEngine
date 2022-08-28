#pragma once

#include <SFML/Graphics.hpp>


#include "ComponentMaster.h"

class C_Render :
    public ComponentMaster
{
public:
    C_Render(Global* globalVariables);

    void draw() override;
    
private:
    sf::VertexArray vertexArr;


};

