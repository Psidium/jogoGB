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


std::map<SignElement,GameObject*> signToProjectile;

GameObject* Projectile::getGameObject() {
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
}

Point Projectile::getLocation() {
    Point during;
    during.x = (int)((float)round*(source.x+target.x) / numberOfMidpoints);
    during.y = (int)((float)round*(source.y+target.y) / numberOfMidpoints);
    round++;
    return during;
}
