//
//  Projectile.hpp
//  JogoGB
//
//  Created by Psidium on 6/20/16.
//  Copyright © 2016 Psidium. All rights reserved.
//

#ifndef Projectile_hpp
#define Projectile_hpp

#include <stdio.h>
#include "GLEnums.hpp"
#include "Point.hpp"
#include "GameObject.hpp"
#include "Drawable.hpp"
#include "SpriteId.hpp"
#include <map>

#define PROJECTILE_SPEED 30

namespace GLogic {
    class Projectile {
    public:
        Projectile(Sign sign, Point source, Point target);
        Sign getSign();
        Point getLocation();
        SpriteId getSprite();
        Projectile* tick();
        ~Projectile();
        static std::map<SignElement, SpriteId> signToProjectile;
    private:
        Sign sign;
        SignElement elem;
        Point source;
        Point target;
        Point deltaPoint;
        int numberOfMidpoints;
        int round;
        Point currentLocation;
    };
}

#endif /* Projectile_hpp */
