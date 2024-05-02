#pragma once

#include "Interface/IComponent.h"
#include "Transform.h"
#include "../Engine/ResourceManager.h"

#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>
#include <memory>

class RectangleComponent : public IComponent
{
public:
    RectangleComponent(std::string key);
    ~RectangleComponent();

    void init(ResourceManager* resourceManager);

    void setSize(float width, float height);
    void setFillColour(unsigned int r, unsigned int g, unsigned int b, unsigned int a);
    void setOutlineThickness(float thickness);
    void setOutlineColour(unsigned int r, unsigned int g, unsigned int b, unsigned int a);
    void setTexture(const std::string& filepath);

    virtual bool isDrawable() { return true; }

    void update(Transform& globalTransform);
    void render(std::shared_ptr<sf::RenderWindow> window);

    std::string key;
private:
    bool mHasTexture;
    std::shared_ptr<sf::Texture> mTexture;

    sf::RectangleShape mRectangleShape;

    sf::Transform mFinalTransform;

    ResourceManager* mResourceManager;
};