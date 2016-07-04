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
    friend bool operator== (const Point &c2, const Point &c1) {
        return (c2.x == c1.x && c2.y == c1.y);
    }
    friend bool operator< (const Point &c1, const Point &c2) {
        long maximum = 5000;
        return (c1.x*maximum + c1.y < c2.x * maximum + c2.y );
    }
} Point;

#endif /* Point_hpp */
