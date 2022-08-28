#include "EnttHandler.h"


EnttHandler::EnttHandler(Global& globalVariables)
{
	global = &globalVariables;

	//Lembra que precisa deletar posteriormente
	Cube* myCube = new Cube(global, std::string("ALPHA"));
	entityVec.push_back(myCube);

	


}

void EnttHandler::beginPlay()
{
	for (int i = 0; i < entityVec.size(); i++)
	{
		entityVec.at(i)->beginPlay();
	}
}
