#include "Cube.h"

/*/Inicializando a classe derivada junto com a classe base
Cube::Cube(Global* globalVariables, std::string myName) : EntityMaster(globalVariables, myName)
{

	myComponents
}
*/

void Cube::beginPlay()
{
	// Chamando o metodo na classe base
	EntityMaster::beginPlay();
}