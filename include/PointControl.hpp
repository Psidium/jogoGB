//
//  PointControl.hpp
//  JogoGB
//
//  Created by Psidium on 6/20/16.
//  Copyright © 2016 Psidium. All rights reserved.
//

#ifndef PointControl_hpp
#define PointControl_hpp

namespace GLogic {
    class PointControl {
    public:
        void addKill();
        int getPoints();
    private:
        int points;
    };
}

#endif /* PointControl_hpp */
