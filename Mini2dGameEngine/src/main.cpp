#include <iostream>
#include <SFML/Graphics.hpp>

#include "../imgui/imgui.h"
#include "../imgui/imgui-SFML.h"

#include "Global.h"

int main()
{
    Global global;

    ImGui::SFML::Init(global.window);
    

    while (global.window.isOpen())
    {
        while (global.window.pollEvent(global.events))
        {
            ImGui::SFML::ProcessEvent(global.events);
            if (global.events.type == sf::Event::Closed)
                global.window.close();
        }
        ImGui::SFML::Update(global.window, global.deltaClock.restart());


        ImGui::Begin("TITULO");
        ImGui::Text("TEXTO");
        ImGui::End();



        global.window.clear(sf::Color::Black);
        
        ImGui::SFML::Render(global.window);
        global.window.display();

    }
    ImGui::SFML::Shutdown();
    std::cout << "Hello World!\n";
}
