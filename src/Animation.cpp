//
//  Animation.cpp
//  JogoGA
//
//  Created by Psidium on 4/18/16.
//  Copyright © 2016 Psidium. All rights reserved.
//

#include "Animation.hpp"

Animation::Animation(int frameCount){
    this->frameCount = frameCount;
}

void Animation::addFrame(SpriteId* frame) {
    this->frames.push_back(frame);
}

SpriteId* Animation::getFrame(int frame) {
    return this->frames.at(frame);
}

int Animation::getFrameCount() {
    return this->frameCount;
}

Animation::~Animation() {
    this->frames.clear();
}