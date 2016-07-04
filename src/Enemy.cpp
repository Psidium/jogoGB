//
//  Enemy.cpp
//  JogoGB
//
//  Created by Psidium on 6/20/16.
//  Copyright © 2016 Psidium. All rights reserved.
//

#include "Enemy.hpp"

using namespace GLogic;

std::map<Sign,SpriteId> Enemy::signToGO;

Point Enemy::getLocation() {
    return location;
}

SpriteId Enemy::getSprite() {
    return Enemy::signToGO[sign];
}

float Enemy::getCurrentHp() {
    return (float)currentHp/ENEMY_MAXIMUM_HP;
}
Enemy* Enemy::receiveDamage(Projectile* proj, Point currentTile) {
    if (!(currentTile == location)) {
        return this;
    }
    if (proj->getSign() == sign) {
        points->addKill();
        delete this;
        return NULL;
    } else if (getElementOfSign(proj->getSign()) == elem) {
        if (--currentHp == 0) {
            points->addKill();
            delete this;
            return NULL;
        }
    }
    return this;
}

Enemy* Enemy::tick() {
    if (++ticker > tickCount) {
        delete this;
        return NULL;
    }
    return this;
}

Enemy::Enemy(Sign sign, Point loc, int tickCount, PointControl* points) {
    this->sign = sign;
    this->elem = getElementOfSign(sign);
    this->location = loc;
    this->points = points;
    this->tickCount = tickCount;
    this->ticker = 0;
    this->currentHp = 2;
}


