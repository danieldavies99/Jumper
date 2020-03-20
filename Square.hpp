//
//  Square.hpp
//  SDLProject1
//
//  Created by Daniel Davies on 17/03/2020.
//  Copyright © 2020 Daniel Davies. All rights reserved.
//

#ifndef Square_hpp
#define Square_hpp

#include <stdio.h>
#include "LTexture.hpp"

class Square{
private:
    int m_W;
    int m_H;
    double m_X;
    double m_Y;
    
    //jump variables
    int m_JTime;
    double m_YVelocity;
    double m_InitialJumpVelocity;
    double m_Gravity;
    
    //texture to be rendered
    LTexture *m_Texture;
    
    

public:
    Square(double x, double y, LTexture &texture);
    void setTexture(LTexture &texture);

    void render();
    bool spawned();
    bool nearby(Square detect, double radius);
    bool colliding(Square collide, bool x, bool y);
    
    //getters
    double getX();
    double getY();
    int getHeight();
    int getWidth();
    
    //position modifiers
    void jump(int ground, int interval);
    void setPos(double x, double y);
    void move(double velocity, short direction, int interval);
};


#endif /* Square_hpp */
