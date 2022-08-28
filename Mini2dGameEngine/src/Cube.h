#pragma once
#include "EntityMaster.h"
#include "Global.h"

#include "C_Render.h"
class Cube :
    public EntityMaster
{
public:
    Cube(Global* globalVariables, std::string myName) : EntityMaster(globalVariables, myName)
    {
        // Adicionando os componentes
        C_Render* renderComponent = new C_Render(global);
        componentHandler.addComponent(renderComponent);
    }

    //Quando fizer override da fun��o parent deve chamar a fun��o no
    //Base
    void beginPlay() override;

    


};

