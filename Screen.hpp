//
//  Screen.hpp
//  SDLProject1
//
//  Created by Daniel Davies on 26/02/2020.
//  Copyright © 2020 Daniel Davies. All rights reserved.
//

#ifndef Screen_hpp
#define Screen_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <sstream>

namespace dcd{
    
class Screen{
    
public:
   
    bool init();
    
    //Frees media and shuts down SDL
    void close();
    
    //Loads media
    bool loadMedia();
    
    int getHeight();
    int getWidth();
    void addScore();
    
};

}

#endif /* Screen_hpp */
