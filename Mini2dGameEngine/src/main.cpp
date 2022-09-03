#include <iostream>
#include <SFML/Graphics.hpp>

#include <memory>

#include "../imgui/imgui.h"
#include "../imgui/imgui-SFML.h"

#include "Global.h"
#include "Game.h"


#include "Cube.h"

int main()
{
    Global global;
    Game game(global);

    ImGui::SFML::Init(global.window);
    game.beforePlay();
    game.beginPlay();
    
    //Lembra que precisa deletar posteriormente
    std::shared_ptr<Cube> myCube = std::make_shared<Cube>(&global, std::string("ALPHA"));
    game.enttHandler.addEntt(myCube);


    sf::Font arialFont;
    sf::Text fpsText;
    arialFont.loadFromFile("./resources/Silkscreen-Regular.ttf");
    fpsText.setFont(arialFont);
    fpsText.setFillColor(sf::Color::White);
    fpsText.setCharacterSize(12);



    //game.enttHandler.addEntt(myCube2);
    while (global.window.isOpen())
    {
        global.deltaTime = global.deltaClock.getElapsedTime().asSeconds();
        
        while (global.window.pollEvent(global.events))
        {
            ImGui::SFML::ProcessEvent(global.events);
            if (global.events.type == sf::Event::Closed)
                global.window.close();

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            for (int i = 0; i < 2; i++)
            {
                std::cout << game.enttHandler.getEntityVecSize()-i << std::endl;

                game.enttHandler.deleteEntt(game.enttHandler.getEntityVecSize()-1);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            
            for (int i = 0; i < 2; i++)
            {
                std::cout << game.enttHandler.getEntityVecSize() << std::endl;
                
                game.enttHandler.addEntt(std::make_shared<Cube>(&global, std::string("Auto")));
            }
        }
        //LOOP VAI AQUI
        game.process();

        //Calculando o FPS
        double fps = 1 / global.deltaTime;
        int intFps = (int)fps;
        fpsText.setString("FPS: " + std::to_string(intFps));



        //Update e resetando o deltaClock
        ImGui::SFML::Update(global.window, global.deltaClock.restart());

        
        ImGui::Begin("TITULO");
        ImGui::Text("TEXTO");
        ImGui::End();
        
        global.window.clear(sf::Color::Black);

        //DRAW VAI AQUI
        game.draw();

        //After every drawing
        ImGui::SFML::Render(global.window);
        global.window.draw(fpsText);

        global.window.display();

    }


    game.endGame();
    ImGui::SFML::Shutdown();
}
