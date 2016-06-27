//
//  Enemy.cpp
//  JogoGB
//
//  Created by Psidium on 6/20/16.
//  Copyright © 2016 Psidium. All rights reserved.
//

#include "Enemy.hpp"

using namespace GLogic;

Point Enemy::getLocation() {
    return location;
}

GameObject* Enemy::getGameObject() {
    return signToGO[sign];
}

bool Enemy::receiveDamage(Projectile proj) {
    if (proj.getSign() == sign) {
        points->addKill();
        delete this;
        return true;
    } else if (getElementOfSign(proj.getSign()) == elem) {
        if (--currentHp == 0) {
            points->addKill();
            delete this;
        }
        return true;
    }
    return false;
}

void Enemy::tick() {
    if (++ticker > tickCount) {
        delete this;
    }
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


