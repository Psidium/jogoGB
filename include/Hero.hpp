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
#include <math.h>
#include "GLEnums.hpp"
#include "Point.hpp"
#include "GameObject.hpp"
#include "Drawable.hpp"
#include "Projectile.hpp"

#define HERO_START_FACING SOUTH
#define HERO_SPEED 15 

namespace GLogic {
    class Hero {
    public:
        Projectile* fireToCoordinate(Point point, Sign proj_sign);
        void walk(Direction dir);
        void walkTo(Point target);
        Point getLocation();
        void tick();
        GameObject* getGameObject(); //return the gameobject of the facing carinha
        Hero(GameObject* gamObj[], int limitMatrix); //need the 6 facets
        void setPixelLocation(Point pixelLocation);
        Point getPixelLocation();
        void setLocation(Point point);
    private:
        Point pixelLocation;
        Point location;
        GameObject* gameObj[8];
        Direction currentFacing;
        int limitMatrix;
        Point target;
        Point deltaPoint;
        bool walking = false;
        int steps, maximumSteps;
    };
}

#endif /* Hero_hpp */
