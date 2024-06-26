#include "Engine/ResourceManager.h"
#include "Engine/SceneManager.h"
#include "Api/LuaConfigLoader.h"
#include "Api/LuaApi.h"
#include "Api/LuaManager.h"

#include <SFML/Graphics.hpp>

#include <memory>
#include "Engine/SparkGlobals.h"

#ifndef NDEBUG
#include <Windows.h>
#endif

int main()
{
    std::shared_ptr<SparkGlobals> sparkGlobals = std::make_shared<SparkGlobals>();

#ifndef NDEBUG
    sparkGlobals->isDebug = WIN32::IsDebuggerPresent();
#endif


    ResourceManager resourceManager(sparkGlobals);

    LuaConfigLoader luaConfigLoader(sparkGlobals, &resourceManager);
    luaConfigLoader.setup();
    luaConfigLoader.init("data/scripts/config.lua");

    std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>(sf::VideoMode(sparkGlobals->windowWidth, sparkGlobals->windowHeight), sparkGlobals->windowTitle);
    window->setFramerateLimit(sparkGlobals->framerateLimit);

    std::shared_ptr<SceneManager> sceneManager = std::make_shared<SceneManager>(&resourceManager, sparkGlobals);
    std::shared_ptr<LuaManager> luaManager = std::make_shared<LuaManager>(sceneManager, window, sparkGlobals);

    if (!luaManager->addLuaState("data/scripts/spark.lua"))
    {
        // Failed loading script
        return 0;
    }

    sf::Clock dtClock;
    float dt;

    while (window->isOpen())
    {
        dt =  dtClock.restart().asSeconds();

        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();

            if (event.type == sf::Event::KeyPressed)
                luaManager->keyDown(event.key.scancode);

            if (event.type == sf::Event::KeyReleased)
                luaManager->keyUp(event.key.scancode);

            if (event.type == sf::Event::MouseButtonPressed)
                luaManager->mouseDown(event.mouseButton.button);

            if (event.type == sf::Event::MouseButtonReleased)
                luaManager->mouseUp(event.mouseButton.button);

            if (event.type == sf::Event::MouseWheelScrolled)
                luaManager->mouseWheelMoved(event.mouseWheelScroll.delta);

            if (event.type == sf::Event::MouseMoved)
                luaManager->mouseMoved(event.mouseMove.x, event.mouseMove.y);
        }

        luaManager->update(dt);
        sceneManager->update(dt);

        window->clear();

        sceneManager->render(window);

        window->display();
    }


    return 0;
}