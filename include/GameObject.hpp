//
//  GameObject.hpp
//  JogoGA
//
//  Created by Psidium on 4/18/16.
//  Copyright © 2016 Psidium. All rights reserved.
//

#ifndef GameObject_hpp
#define GameObject_hpp

#include <stdio.h>
#include "Animation.hpp"
#include "SpriteId.hpp"

class GameObject {
public:
    GameObject();
    void incCurrentFrame();
    void setSprite(Animation* animtion);
    SpriteId* getCurrentFrame();
private:
    int currentFrame = 0;
    Animation* animation;
};
#endif /* GameObject_hpp */
