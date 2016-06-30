//
//  Hero.cpp
//  JogoGB
//
//  Created by Psidium on 6/20/16.
//  Copyright © 2016 Psidium. All rights reserved.
//

#include "Hero.hpp"

using namespace GLogic;

Projectile* Hero::fireToCoordinate(Point target) {
    return new Projectile(currentStandingSign(), location, target);
}


void Hero::walk(Direction dir) {
    this->currentFacing = dir;
    Point loc = this->location;
    switch (dir) {
        case NORTH:
            loc.x++;
            loc.y--;
            break;
        case SOUTH:
            loc.x--;
            loc.y++;
            break;
        case EAST:
            loc.x++;
            loc.y++;
            break;
        case WEST:
            loc.x--;
            loc.y--;
            break;
        case NORTHEAST:
            loc.x++;
            break;
        case NORTHWEST:
            loc.y--;
            break;
        case SOUTHEAST:
            loc.y++;
            break;
        case SOUTHWEST:
            loc.x--;
            break;
    }
    if (!(loc.x < 0 | loc.y < 0 | loc.x > this->limitMatrix | loc.y > this->limitMatrix)) {
        this->location = loc;
    }
}

Point Hero::getLocation() {
    return location;
}

GameObject* Hero::getGameObject() {
    return gameObj[currentFacing];
}

Hero::Hero(GameObject* gamObj[], int limitMatrix) {
    for (int i = 0; i< 8; i++) {
        this->gameObj[i] = gamObj[i];
    }
    this->currentFacing = HERO_START_FACING;
    this->limitMatrix = limitMatrix;
    this->location.x =0;
    this->location.y =0;
}

