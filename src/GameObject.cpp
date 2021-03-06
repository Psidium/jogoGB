//
//  GameObject.cpp
//  JogoGA
//
//  Created by Psidium on 4/18/16.
//  Copyright © 2016 Psidium. All rights reserved.
//

#include "GameObject.hpp"

GameObject::GameObject() {
}

void GameObject::incCurrentFrame() {
    this->currentFrame = ++currentFrame % this->animation->getFrameCount();
}

void GameObject::setSprite(Animation* animtion) {
    this->animation = animtion;
}

SpriteId* GameObject::getCurrentFrame() {
    return this->animation->getFrame(this->currentFrame);
}
