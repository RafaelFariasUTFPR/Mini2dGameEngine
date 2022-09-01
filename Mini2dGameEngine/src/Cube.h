#pragma once
#include "EntityMaster.h"
#include "Global.h"

#include "C_RenderSprite.h"
#include "C_Physics2d.h"
#include "C_Collider2d.h"
class Cube :
    public EntityMaster
{
public:
    Cube(Global* globalVariables, std::string myName) : EntityMaster(globalVariables, myName)
    {
        isDynamic = true;
        // Adicionando os componentes
        componentHandler.addComponent(renderComponent);
        componentHandler.addComponent(physicsComponent);
        componentHandler.addComponent(colliderComponent);


    }

    //Quando fizer override da função parent deve chamar a função no Base
    void beginPlay() override;

    // Criando os componenetes
    C_RenderSprite* renderComponent = new C_RenderSprite(global, "./resources/cube.png", sf::Vector2f(5,1));
    C_Physics2d* physicsComponent = new C_Physics2d(global, transform, sf::Vector2f(30, 20), 0);
    C_Collider2d* colliderComponent = new C_Collider2d(global);
};

