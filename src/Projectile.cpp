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


std::map<SignElement,int> Projectile::signToProjectile;

int Projectile::getTextureID() {
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
    float d = sqrt((source.x-target.x)^2 + (source.y-target.y)^2);
    this->numberOfMidpoints = d/PROJECTILE_SPEED;
    this->currentLocation = source;
}

Point Projectile::getLocation() {
    return currentLocation;
}

void Projectile::tick() {
    Point during;
    during.x = (int)((float)round*(source.x+target.x) / numberOfMidpoints);
    during.y = (int)((float)round*(source.y+target.y) / numberOfMidpoints);
    round++;
    if (round > numberOfMidpoints) {
        delete this;
    }
    currentLocation = during;
}

Projectile::~Projectile() {
    
}
