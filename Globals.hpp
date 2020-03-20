//
//  Globals.hpp
//  SDLProject1
//
//  Created by Daniel Davies on 09/03/2020.
//  Copyright © 2020 Daniel Davies. All rights reserved.
//

#ifndef Globals_hpp
#define Globals_hpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "LTexture.hpp"

namespace dcd{
    
    extern const int SCREEN_WIDTH;
    extern const int SCREEN_HEIGHT;
    
    //The window we'll be rendering to
    extern SDL_Window* g_Window;
    
    //The window renderer
    extern SDL_Renderer* g_Renderer;
    
    //Scene textures
    extern LTexture g_EnemyTexture;
    extern LTexture g_JumperEnemyTexture;
    extern LTexture g_PlayerTexture;
    extern LTexture g_BackgroundTexture;
    extern LTexture g_VignetteTexture;
    
    //Globally used font
    extern TTF_Font *g_Font;
    //text textures
    extern LTexture g_TextTexture;
    extern LTexture g_ScoreTexture;
}


#endif /* Globals_hpp */
