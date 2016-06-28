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
    virtual int getTextureID() = 0;
};

#endif /* Drawable_hpp */
