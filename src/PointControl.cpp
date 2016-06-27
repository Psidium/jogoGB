//
//  PointControl.cpp
//  JogoGB
//
//  Created by Psidium on 6/20/16.
//  Copyright © 2016 Psidium. All rights reserved.
//

#include "PointControl.hpp"

using namespace GLogic;

void PointControl::addKill() {
    points += 2;
}

int PointControl::getPoints() {
    return points;
}
