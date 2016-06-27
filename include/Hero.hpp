//
//  Hero.hpp
//  JogoGB
//
//  Created by Psidium on 6/20/16.
//  Copyright © 2016 Psidium. All rights reserved.
//

#ifndef Hero_hpp
#define Hero_hpp

#include <stdio.h>
#include "GLEnums.hpp"
#include "Point.hpp"
#include "GameObject.hpp"
#include "Drawable.hpp"
#include "Projectile.hpp"

#define HERO_START_FACING SOUTH

namespace GLogic {
    class Hero: public Drawable {
    public:
        Projectile* fireToCoordinate(Point point);
        void walk(Direction dir);
        Point getLocation();
        GameObject* getGameObject(); //return the gameobject of the facing carinha
        Hero(GameObject* gamObj[], int limitMatrix); //need the 6 facets
    private:
        Point location;
        GameObject* gameObj[8];
        Direction currentFacing;
        int limitMatrix;
    };
}

#endif /* Hero_hpp */
