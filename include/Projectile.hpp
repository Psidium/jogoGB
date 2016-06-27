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

namespace GLogic {
    class Projectile: public Drawable {
    public:
        Projectile(Sign sign, Point source, Point target);
        Sign getSign();
        Point getLocation();
        GameObject* getGameObject();
        Projectile(GameObject* gamObj);
        ~Projectile();
    private:
        Sign sign;
        Point source;
        Point target;
    };
}

#endif /* Projectile_hpp */
