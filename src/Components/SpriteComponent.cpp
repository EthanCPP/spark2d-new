#include "SpriteComponent.h"


SpriteComponent::SpriteComponent(std::string key)
{
    this->key = key;
}

SpriteComponent::~SpriteComponent()
{
}

void SpriteComponent::init(ResourceManager* resourceManager)
{
    mResourceManager = resourceManager;
}

void SpriteComponent::loadTexture(std::string filepath)
{
    mTexture = mResourceManager->getTexture(filepath);
    mSprite.setTexture(*mTexture);
    //mSprite.setOrigin(mSprite.getTextureRect().width / 2, mSprite.getTextureRect().height / 2);
}

void SpriteComponent::update(Transform& globalTransform)
{
    sf::Transform parentTransform;
    parentTransform.translate(globalTransform.position);
    parentTransform.rotate(globalTransform.rotation);

    sf::Transform childTransform;
    childTransform.translate(mLocalTransform.position);
    childTransform.rotate(mLocalTransform.rotation);

    mFinalTransform = parentTransform * childTransform;
}

void SpriteComponent::render(std::shared_ptr<sf::RenderWindow> window)
{
    window->draw(mSprite, mFinalTransform);

}
