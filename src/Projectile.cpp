//
//  Projectile.cpp
//  JogoGB
//
//  Created by Psidium on 6/20/16.
//  Copyright © 2016 Psidium. All rights reserved.
//

#include "Projectile.hpp"
#include "math.h"

using namespace GLogic;


std::map<SignElement,SpriteId> Projectile::signToProjectile;


SpriteId Projectile::getSprite() {
    return Projectile::signToProjectile[elem];
}


Sign Projectile::getSign() {
    return sign;
}

Projectile::Projectile(Sign sign, Point source, Point target) {
    this->sign = sign;
    this->elem = getElementOfSign(sign);
    this->source = source;
    this->target = target;
    this->currentLocation = source;
    
    
    double d = sqrt(pow((target.x - source.x),2) + pow((target.y - source.y),2));
    numberOfMidpoints = ceil(d/PROJECTILE_SPEED);
    deltaPoint.x = (target.x - source.x)/ numberOfMidpoints;
    deltaPoint.y = (target.y - source.y)/ numberOfMidpoints;
}

Point Projectile::getLocation() {
    return currentLocation;
}

Projectile* Projectile::tick() {
    round++;
    currentLocation.x += deltaPoint.x;
    currentLocation.y += deltaPoint.y;
    if (round - 4 > numberOfMidpoints) {
        delete this;
        return NULL;
    }
    return this;
}

Projectile::~Projectile() {
    
}
