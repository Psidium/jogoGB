//
//  Point.hpp
//  JogoGB
//
//  Created by Psidium on 6/20/16.
//  Copyright © 2016 Psidium. All rights reserved.
//

#ifndef Point_hpp
#define Point_hpp

typedef struct Point {
    int x;
    int y;
    bool operator== (const Point &c1) {
        return (x == c1.x && y == c1.y);
    }
} Point;

#endif /* Point_hpp */
