#include <iostream>
#include <SFML/Graphics.hpp>

#include <memory>
#include <thread>

#include "../imgui/imgui.h"
#include "../imgui/imgui-SFML.h"

#include "Global.h"
#include "Game.h"


#include "entts/Cube.h"
#include "entts/Ground.h"
#include "entts/Wall.h"



void threadPhysicsUpdate(Game* game)
{
    while (game->running)
    {
        game->enttHandler.physicsProcess();

    }
}

void p(int id)
{
    while (true)
    {

    }
}

int main()
{
    Global global;
    Game game(global);

    ImGui::SFML::Init(global.window);



    //Lembra que precisa deletar posteriormente
    myMath::Transform cubeTransform;
    cubeTransform.position = sf::Vector2f(100, 100);
    std::shared_ptr<Cube> myCube = std::make_shared<Cube>(&global, std::string("ALPHA"), cubeTransform);
    game.enttHandler.addEntt(myCube);


    
    myMath::Transform groundPlaneTransform;
    groundPlaneTransform.position = sf::Vector2f(200, 300);
    groundPlaneTransform.rotation = 10;
    std::shared_ptr<Ground> groundPlane = std::make_shared<Ground>(&global, std::string("Ground"), groundPlaneTransform);
    game.enttHandler.addEntt(groundPlane);

    myMath::Transform groundPlane2Transform;
    groundPlane2Transform.position = sf::Vector2f(350, 300);
    groundPlane2Transform.rotation = 90;
    std::shared_ptr<Ground> groundPlane2 = std::make_shared<Ground>(&global, std::string("Ground"), groundPlane2Transform);
    game.enttHandler.addEntt(groundPlane2);
    
    myMath::Transform wall1Transform;
    wall1Transform.position = sf::Vector2f(0, global.initialHeight / 2);
    wall1Transform.rotation = 90;
    std::shared_ptr<Wall> wall1 = std::make_shared<Wall>(&global, std::string("Ground"), wall1Transform);
    game.enttHandler.addEntt(wall1);

    myMath::Transform wall2Transform;
    wall2Transform.position = sf::Vector2f(global.initialWidth, global.initialHeight / 2);
    wall2Transform.rotation = 90;
    std::shared_ptr<Wall> wall2 = std::make_shared<Wall>(&global, std::string("Ground"), wall2Transform);
    game.enttHandler.addEntt(wall2);

    myMath::Transform wall3Transform;
    wall3Transform.position = sf::Vector2f(global.initialWidth / 2, 0);
    std::shared_ptr<Wall> wall3 = std::make_shared<Wall>(&global, std::string("Ground"), wall3Transform);
    game.enttHandler.addEntt(wall3);

    myMath::Transform wall4Transform;
    wall4Transform.position = sf::Vector2f(global.initialWidth / 2, global.initialHeight);
    std::shared_ptr<Wall> wall4 = std::make_shared<Wall>(&global, std::string("Ground"), wall4Transform);
    game.enttHandler.addEntt(wall4);


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

    sf::Texture t1;
    t1.loadFromFile("./resources/spriteSheet01.png");
    global.sceneArray.renderState.texture = &t1;
    global.sceneBuffer.renderState.texture = &t1;
    
    std::thread physicsThread(threadPhysicsUpdate, &game);

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

        //game.enttHandler.physicsProcess();

        game.process();


        //Calculando o FPS
        float fps = 1 / (global.deltaTime);
        int intFps = (int)fps;

        float physicsHeartz = 1/global.actualPhysicsUpdateTime;
        int intHeartz = (int)physicsHeartz;

        fpsText.setString("FPS: " + std::to_string(intFps) + "\nSIM: " + std::to_string(intHeartz));

        //Update e resetando o deltaClock
        global.deltaTime = global.deltaClock.getElapsedTime().asSeconds();
        //std::cout << global.deltaTime << std::endl;
        ImGui::SFML::Update(global.window, global.deltaClock.restart());

        ImGui::Begin("DEBUG");
        ImGui::Text("Entidades: %i", game.enttHandler.getEntityVecSize());
        
        if (ImGui::Button("Adicionar entidade"))
            for (int i = 0; i < spawnNumber; i++)
            {
                myMath::Transform spawnTransform;
                spawnTransform.position = sf::Vector2f(100, 100);
                game.enttHandler.addEntt(std::make_shared<Cube>(&global, std::string("Auto"), spawnTransform));

            }
        
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
        global.window.draw(global.sceneBuffer.vArray, &t1);


        for (int i = 0; i < global.debugVertexArray.size(); i++)
            global.window.draw(global.debugVertexArray.at(i));


        global.sceneArray.vArray.clear();
        global.sceneArray.vArray = global.sceneBuffer.vArray;
        global.sceneBuffer.vArray.clear();

        global.window.draw(global.sceneArray.vArray, global.sceneArray.renderState);
        //After every drawing
        ImGui::SFML::Render(global.window);
        global.window.draw(fpsText);


        global.window.display();


    }
    game.endGame();
    physicsThread.join();
    ImGui::SFML::Shutdown();
}
