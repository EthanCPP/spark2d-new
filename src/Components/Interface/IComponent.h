#pragma once

#include "../Transform.h"

#include <SFML/Graphics.hpp>

#include <string>

class IComponent
{
public:
    virtual bool isDrawable() { return false; }
    virtual void update(Transform& globalTransform) {}
    virtual void render(std::shared_ptr<sf::RenderWindow> window) {}

    virtual float getX() {
        return mLocalTransform.position.x;
    }

    virtual float getY() {
        return mLocalTransform.position.y;
    }

    virtual float getRotation() {
        return mLocalTransform.rotation;
    }

    virtual void setX(float x) {
        mLocalTransform.position.x = x;
    }

    virtual void setY(float y) {
        mLocalTransform.position.y = y;
    }

    virtual void setRotation(float angle) {
        mLocalTransform.rotation = angle;
    }

protected:
    Transform mLocalTransform;
};