#pragma once
#include "EntityMaster.h"
#include "Global.h"

#include "C_RenderSprite.h"
#include "C_Physics2d.h"
class Cube :
    public EntityMaster
{
public:
    Cube(Global* globalVariables, std::string myName) : EntityMaster(globalVariables, myName)
    {
        // Adicionando os componentes
        componentHandler.addComponent(renderComponent);
        componentHandler.addComponent(physicsComponent);

    }

    //Quando fizer override da função parent deve chamar a função no Base
    void beginPlay() override;

    // Criando os componenetesz
    C_RenderSprite* renderComponent = new C_RenderSprite(global, "./resources/cube.png", sf::Vector2f(1,1));
    C_Physics2d* physicsComponent = new C_Physics2d(global, transform, sf::Vector2f(30, 20), 0);

};

