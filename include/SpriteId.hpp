
#ifndef SpriteId_H
#define SpriteId_H

typedef struct Pointf {
    float x;
    float y;

} Pointf;

typedef struct SpriteId {
    Pointf lower_left = {0, 0};
    Pointf upper_left = {0,1};
    Pointf upper_right = {1,1};
    Pointf lower_right = {1, 0};
    bool hidden = false;
    int texture = 0;

} SpriteId;

#endif
