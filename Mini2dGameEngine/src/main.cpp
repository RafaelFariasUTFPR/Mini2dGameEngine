#include <iostream>
#include <SFML/Graphics.hpp>

#include "../imgui/imgui.h"
#include "../imgui/imgui-SFML.h"

#include "Global.h"
#include "Game.h"

int main()
{
    Global global;
    Game game(global);

    ImGui::SFML::Init(global.window);
    game.beginPlay();
    //Main executable loop
    while (global.window.isOpen())
    {
        global.deltaTime = global.deltaClock.getElapsedTime().asSeconds();
        
        while (global.window.pollEvent(global.events))
        {
            ImGui::SFML::ProcessEvent(global.events);
            if (global.events.type == sf::Event::Closed)
                global.window.close();
        }
        
        //LOOP VAI AQUI

        double fps = 1 / global.deltaTime;
        std::cout << fps << "\n";


        //Update e resetando o deltaClock
        ImGui::SFML::Update(global.window, global.deltaClock.restart());

        /*
        for (int i = 0; i < 10000000; i++)
        {
            double a = i;
            a /= 500;
        }
        
        */
        //DRAW VAI AQUI
        
        ImGui::Begin("TITULO");
        ImGui::Text("TEXTO");
        ImGui::End();
        
        global.window.clear(sf::Color::Black);

        //After every drawing
        ImGui::SFML::Render(global.window);

        global.window.display();

        



    }
    ImGui::SFML::Shutdown();
    std::cout << "Hello World!\n";
}
