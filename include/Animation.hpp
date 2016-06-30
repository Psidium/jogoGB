//
//  Animation.hpp
//  JogoGA
//
//  Created by Psidium on 4/18/16.
//  Copyright © 2016 Psidium. All rights reserved.
//

#ifndef Animation_hpp
#define Animation_hpp

#include <stdio.h>
#include <vector>
#include "SpriteId.hpp"

class Animation {
public:
    void addFrame(SpriteId* frame);
    SpriteId* getFrame(int frame);
    int getFrameCount();
    Animation(int frameCount);
    ~Animation();
private:
    int frameCount;
    std::vector<SpriteId*> frames;
};

#endif /* Animation_hpp */
