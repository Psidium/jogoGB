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

namespace GLogic {
    class Enemy: public Drawable {
    public:
        Point getLocation();
        virtual int getTextureID() = 0;

        bool receiveDamage(Projectile proj);
        void tick();
        Enemy(Sign sign, Point loc, int tickCount, PointControl* points);
        static std::map<Sign, int> signToGO;
        
    private:
        int ticker, tickCount, currentHp;
        Point location;
        Sign sign;
        SignElement elem;
        PointControl* points;
    };
}

#endif /* Enemy_hpp */
