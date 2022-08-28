#include "Global.h"

Global::Global() :initialWidth{ 1280 }, initialHeight{ 720 }, windowName {"GameEngine"}, window(sf::VideoMode(initialWidth, initialHeight), windowName)
{

}