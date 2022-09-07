#include <iostream>
#include <SFML/Graphics.hpp>

#include <memory>

#include "../imgui/imgui.h"
#include "../imgui/imgui-SFML.h"

#include "Global.h"
#include "Game.h"


#include "entts/Cube.h"
#include "entts/Ground.h"

int main()
{
    Global global;
    Game game(global);

    ImGui::SFML::Init(global.window);

    
    //Lembra que precisa deletar posteriormente
    std::shared_ptr<Cube> myCube = std::make_shared<Cube>(&global, std::string("ALPHA"));
    game.enttHandler.addEntt(myCube);

    std::shared_ptr<Ground> groundPlane = std::make_shared<Ground>(&global, std::string("Ground"));
    game.enttHandler.addEntt(groundPlane);


    sf::Font arialFont;
    sf::Text fpsText;
    arialFont.loadFromFile("./resources/Silkscreen-Regular.ttf");
    fpsText.setFont(arialFont);
    fpsText.setFillColor(sf::Color::White);
    fpsText.setCharacterSize(12);

    int spawnNumber = 1;
    int fpsLock = 0;
    game.beforePlay();
    game.beginPlay();

    while (global.window.isOpen())
    {
        global.debugVertexArray.clear();
        
        while (global.window.pollEvent(global.events))
        {
            ImGui::SFML::ProcessEvent(global.events);
            if (global.events.type == sf::Event::Closed)
                global.window.close();

        }

        global.window.setFramerateLimit(fpsLock);

        //LOOP VAI AQUI
        game.process();

        //Calculando o FPS
        double fps = 1 / global.deltaTime;
        int intFps = (int)fps;
        fpsText.setString("FPS: " + std::to_string(intFps));

        global.deltaTime = global.deltaClock.getElapsedTime().asSeconds();

        //Update e resetando o deltaClock
        ImGui::SFML::Update(global.window, global.deltaClock.restart());

        ImGui::Begin("DEBUG");
        ImGui::Text("Entidades: %i", game.enttHandler.getEntityVecSize());
        
        if (ImGui::Button("Adicionar entidade"))
            for (int i = 0; i < spawnNumber; i++)
                game.enttHandler.addEntt(std::make_shared<Cube>(&global, std::string("Auto")));
        
        if (ImGui::Button("Remover entidade"))
            for (int i = 0; i < spawnNumber; i++)
                game.enttHandler.deleteEntt(game.enttHandler.getEntityVecSize() - 1);
        
        ImGui::SliderInt("Numero de entidades", &spawnNumber, 1, 500);

        ImGui::SliderInt("FPS lock:", &fpsLock, 5, 120);
        if (ImGui::Button("FPS sem limite"))
            fpsLock = 0;

        ImGui::End();
        global.window.clear(sf::Color::Black);


        //DRAW VAI AQUI



        game.draw();

        for (int i = 0; i < global.debugVertexArray.size(); i++)
            global.window.draw(global.debugVertexArray.at(i));

        //After every drawing
        ImGui::SFML::Render(global.window);
        global.window.draw(fpsText);

        global.window.display();

    }


    game.endGame();
    ImGui::SFML::Shutdown();
}
