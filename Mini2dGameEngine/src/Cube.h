#pragma once
#include "EntityMaster.h"
#include "Global.h"

#include "C_Render.h"
class Cube :
    public EntityMaster
{
public:
    Cube(Global* globalVariables, std::string myName);

    //Quando fizer override da fun��o parent deve chamar a fun��o no
    //Base
    void beginPlay() override;

    


};

