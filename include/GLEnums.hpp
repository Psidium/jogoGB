//
//  Environment.hpp
//  JogoGB
//
//  Created by Psidium on 6/20/16.
//  Copyright © 2016 Psidium. All rights reserved.
//

#ifndef Environment_hpp
#define Environment_hpp

#include <stdio.h>

namespace GLogic {
    enum Sign {
        PEIXES = 0,
        ESCORPIAO = 1,
        CANCER = 2,
        TOURO = 3,
        VIRGEM = 4,
        CAPRICORNIO = 5,
        ARIES = 6,
        LEAO = 7,
        SAGITARIO = 8,
        LIBRA = 9,
        GEMEOS = 10,
        AQUARIO = 11
    };
    enum SignElement {
        AGUA = 0,
        TERRA = 1,
        FOGO = 2,
        AR = 3
    };
    
    static SignElement getElementOfSign(Sign s) {
        switch (s) {
            case PEIXES:
            case ESCORPIAO:
            case CANCER:
                return AGUA;
            case TOURO:
            case VIRGEM:
            case CAPRICORNIO:
                return TERRA;
            case ARIES:
            case LEAO:
            case SAGITARIO:
                return FOGO;
            case LIBRA:
            case GEMEOS:
            case AQUARIO:
                return AR;
        }
    }
    
    enum Direction {
        NORTH,
        SOUTH,
        EAST,
        WEST,
        NORTHEAST,
        NORTHWEST,
        SOUTHEAST,
        SOUTHWEST
    };
}

#endif /* Environment_hpp */
