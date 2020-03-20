//
//  Square.cpp
//  SDLProject1
//
//  Created by Daniel Davies on 17/03/2020.
//  Copyright © 2020 Daniel Davies. All rights reserved.
//

#include "Square.hpp"
#include "LTexture.hpp"
#include "Globals.hpp"

enum directions
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
};

Square::Square(double x, double y, LTexture &texture): m_X(x), m_Y(y), m_JTime(0), m_YVelocity(0), m_InitialJumpVelocity(0.46), m_Gravity(0.000015){
    m_Texture = &texture;
    m_H = m_Texture->getHeight();
    m_W = m_Texture->getWidth();
}

void Square::setTexture(LTexture &texture){
    m_Texture = &texture;
    m_H = m_Texture->getHeight();
    m_W = m_Texture->getWidth();
}

void Square::jump(int ground, int interval){
    
    m_YVelocity += ( m_InitialJumpVelocity - ( m_Gravity*((m_JTime * m_JTime)/2) ) )*interval;

    m_Y = ground - m_YVelocity;
    
    m_JTime += interval;
    
    if(m_Y >= ground){
        m_Y = ground;
        m_JTime = 0;
    }
    
}

void Square::move(double speed, short direction, int interval){
    switch(direction){
        case UP:
            m_Y -= speed * interval;
            break;
        case DOWN:
            m_Y += speed * interval;
            break;
        case LEFT:
            m_X -= speed * interval;
            break;
        case RIGHT:
            m_X += speed * interval;
            break;
    };
}

void Square::setPos(double x, double y){
    m_X = x;
    m_Y = y;
}

bool Square::spawned(){
    if(m_X > (0 - (m_W + 20 )) && m_X < dcd::SCREEN_WIDTH + 20){
        return true;
    }
    
    return false;
}

bool Square::colliding(Square collide, bool x, bool y){
    
    int topA = m_Y - getHeight();
    int topB = collide.getY() - collide.getHeight();
    
    int bottomA = m_Y;
    int bottomB = collide.getY();
    
    int leftA = m_X;
    int leftB = collide.getX();
    
    int rightA = m_X + getWidth();
    int rightB = collide.getX() + collide.getWidth();
    
    if( bottomA <= topB && x)
    {
        return false;
    }
    
    if( topA >= bottomB && x)
    {
        return false;
    }
    
    if( rightA <= leftB && y)
    {
        return false;
    }
    
    if( leftA >= rightB && y)
    {
        return false;
    }
    
    //If none of the sides from A are outside B
    return true;
}

bool Square::nearby(Square detect, double radius){
    
    if( ( getX() + ( getWidth()/2)) > ( detect.getX() + (detect.getWidth()/2 ) - radius ) && (getX() + (getWidth()/2)) < ( detect.getX() + (detect.getWidth()/2 ) + radius ) ) {
        return true;
    }
    
    return false;
}

int Square::getHeight(){
    return m_H;
}
int Square::getWidth(){
    return m_W;
}

double Square::getX(){
    return m_X;
}

double Square::getY(){
    return m_Y;
}

void Square::render(){
    m_Texture->render(m_X, m_Y, NULL, 0, 0, SDL_FLIP_NONE);
}
