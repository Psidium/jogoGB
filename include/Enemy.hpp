//
//  Enemy.hpp
//  JogoGB
//
//  Created by Psidium on 6/20/16.
//  Copyright © 2016 Psidium. All rights reserved.
//

#ifndef Enemy_hpp
#define Enemy_hpp

#include <stdio.h>
#include "GLEnums.hpp"
#include "Point.hpp"
#include "Drawable.hpp"
#include "Projectile.hpp"
#include "PointControl.hpp"
#include <map>

#define ENEMY_MAXIMUM_HP 2

namespace GLogic {
    class Enemy {
    public:
        Point getLocation();
        SpriteId getSprite();

        Enemy* receiveDamage(Projectile* proj, Point currentTile);
        Enemy* tick();
        float getCurrentHp();
        Enemy(Sign sign, Point loc, int tickCount, PointControl* points);
        static std::map<Sign, SpriteId> signToGO;
        
    private:
        int ticker, tickCount, currentHp;
        Point location;
        Sign sign;
        SignElement elem;
        PointControl* points;
    };
}

#endif /* Enemy_hpp */
