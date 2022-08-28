#include "Cube.h"

/*/Inicializando a classe derivada junto com a classe base
Cube::Cube(Global* globalVariables, std::string myName) : EntityMaster(globalVariables, myName)
{

	myComponents
}
*/

void Cube::beginPlay()
{
	std::cout << "Begin\n";

	// Chamando o metodo na classe base
	EntityMaster::beginPlay();
}