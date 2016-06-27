//
//  Drawable.hpp
//  JogoGB
//
//  Created by Psidium on 6/20/16.
//  Copyright © 2016 Psidium. All rights reserved.
//

#ifndef Drawable_hpp
#define Drawable_hpp

#include <stdio.h>
#include <vector>
#include "Point.hpp"
#include "GameObject.hpp"

class Drawable {
public:
    std::vector<Point> getDrawablePoints();
    virtual GameObject* getGameObject();
};

#endif /* Drawable_hpp */
