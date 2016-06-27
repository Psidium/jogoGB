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
#include <map>

#define PROJECTILE_SPEED 100

namespace GLogic {
    class Projectile: public Drawable {
    public:
        Projectile(Sign sign, Point source, Point target);
        Sign getSign();
        Point getLocation();
        GameObject* getGameObject();
        Projectile(GameObject* gamObj);
        ~Projectile();
        static std::map<SignElement, GameObject*> signToProjectile;
    private:
        Sign sign;
        SignElement elem;
        Point source;
        Point target;
        int numberOfMidpoints;
        int round;
    };
}

#endif /* Projectile_hpp */
