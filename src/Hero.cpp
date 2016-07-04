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
    return new Projectile(LIBRA, location, target);
}

void Hero::walkTo(Point target) {
    if (!walking) {
        this->walking = true;
        this->target = target;
        //calculate facing
        double angle = atan2(pixelLocation.y - target.y, pixelLocation.x - target.x) * 180 / M_PI;
        if (angle < 0) {
            angle += 360;
        }
        if (22.5f >= angle || angle > 337.5f) {
                this->currentFacing = WEST;
        } else if (67.5 >= angle) {
                this->currentFacing = NORTHWEST;
        } else if (112.5 >= angle) {
                this->currentFacing = NORTH;
        } else if (157.5f >= angle) {
                this->currentFacing = NORTHEAST;
        } else if (202.5f >= angle) {
            this->currentFacing = EAST;
        } else if (247.5f >= angle) {
                this->currentFacing = SOUTHEAST;
        } else if (292.5f >= angle) {
                this->currentFacing = SOUTH;
        } else if (337.5f >= angle) {
                this->currentFacing = SOUTHWEST;
        }
        steps = 0;
        double d = sqrt(pow((target.x - pixelLocation.x),2) + pow((target.y - pixelLocation.y),2));
        maximumSteps = ceil(d/HERO_SPEED);
        deltaPoint.x = (target.x - pixelLocation.x)/ maximumSteps;
        deltaPoint.y = (target.y - pixelLocation.y)/ maximumSteps;
    }
}

void Hero::setPixelLocation(Point pixelLocation) {
    this->pixelLocation = pixelLocation;
}

Point Hero::getPixelLocation(){
    return this->pixelLocation;
}

void Hero::tick() {
    if (walking) {
        getGameObject()->incCurrentFrame();
        pixelLocation.x += deltaPoint.x;
        pixelLocation.y += deltaPoint.y;
        steps++;
        if (target == pixelLocation || steps >= maximumSteps) {
            walking = false;
            deltaPoint.x = 0;
            deltaPoint.y = 0;
            steps = 0;
            //avoid any off-by-one
            pixelLocation = target;
        }
    }
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
    if (!(loc.x < 0 | loc.y < 0 | loc.x >= this->limitMatrix | loc.y >= this->limitMatrix)) {
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

