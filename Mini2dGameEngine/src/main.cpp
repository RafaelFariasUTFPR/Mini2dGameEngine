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

//#define MULTYTHREAD



#ifdef MULTYTHREAD
std::atomic<bool> isRunning = false;

void runPhysicsThread(EnttHandler *handler, int min, int max)
{
    //return;
    while (isRunning)
    {

        sf::Clock clock;
        handler->threadPhysicsProcess(min, max);
        double delta = clock.getElapsedTime().asSeconds();

        double fps = 1 / delta;
        int intFps = (int)fps;
        std::cout << intFps << std::endl;
        
    }
}
#endif // MULTYTHREAD


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

    groundPlane->physicsComponent->setPosition(sf::Vector2f(200, 300));
    groundPlane->physicsComponent->setRotation(10);

    std::shared_ptr<Ground> groundPlane2 = std::make_shared<Ground>(&global, std::string("Ground"));
    game.enttHandler.addEntt(groundPlane2);

    groundPlane2->physicsComponent->setPosition(sf::Vector2f(350, 300));
    groundPlane2->physicsComponent->setRotation(90);

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

#ifdef MULTYTHREAD

    isRunning = true;
    global.m.native_handle();
    std::thread physicsThread(runPhysicsThread, &game.enttHandler, 0, 30);
    //std::thread physicsThread2(runPhysicsThread, &game.enttHandler, 31, 60);
    //std::thread physicsThread3(runPhysicsThread, &game.enttHandler, 61, 120);


#endif // MULTYTHREAD
    sf::Texture t1;
    t1.loadFromFile("./resources/spriteSheet01.png");
    global.sceneArray.renderState.texture = &t1;
    global.sceneBuffer.renderState.texture = &t1;
    

    while (global.window.isOpen())
    {
#ifdef MULTYTHREAD
#endif // MULTYTHREAD




        global.debugVertexArray.clear();
        
        while (global.window.pollEvent(global.events))
        {
            ImGui::SFML::ProcessEvent(global.events);
            if (global.events.type == sf::Event::Closed)
                global.window.close();

        }

        global.window.setFramerateLimit(fpsLock);

        //LOOP VAI AQUI
#ifndef MULTYTHREAD
        game.enttHandler.physicsProcess();

#endif // !MULTYTHREAD

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
        global.window.draw(global.sceneBuffer.vArray, &t1);


        for (int i = 0; i < global.debugVertexArray.size(); i++)
            global.window.draw(global.debugVertexArray.at(i));
#ifdef MULTYTHREAD
        global.m.lock();
        for (int i = 0; i < global.physicsThreadDebugVertexArray.size(); i++)
            global.window.draw(global.physicsThreadDebugVertexArray.at(i));
        global.physicsThreadDebugVertexArray.clear();
        global.m.unlock();
#endif

        global.sceneArray.vArray.clear();
        global.sceneArray.vArray = global.sceneBuffer.vArray;
        global.sceneBuffer.vArray.clear();

        global.window.draw(global.sceneArray.vArray, global.sceneArray.renderState);
        //After every drawing
        ImGui::SFML::Render(global.window);
        global.window.draw(fpsText);


        global.window.display();


    }
#ifdef MULTYTHREAD
    isRunning = false;
    physicsThread.join();
    //physicsThread2.join();
    //physicsThread3.join();

#endif

    //physicsThread.join();

    game.endGame();
    ImGui::SFML::Shutdown();
}
