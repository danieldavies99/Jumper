//
//  Globals.cpp
//  SDLProject1
//
//  Created by Daniel Davies on 09/03/2020.
//  Copyright © 2020 Daniel Davies. All rights reserved.
//

#include "Globals.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

namespace dcd{
    //The window we'll be rendering to
    SDL_Window *g_Window = NULL;
    
    //The window renderer
    SDL_Renderer *g_Renderer = NULL;
    
    //Scene Dimensions
    
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;
    //Scene textures
    LTexture g_EnemyTexture;
    LTexture g_JumperEnemyTexture;
    LTexture g_PlayerTexture;
    LTexture g_BackgroundTexture;
    LTexture g_VignetteTexture;
    
    //Globally used font
    TTF_Font *g_Font = NULL;
    
    //Rendered texture
    LTexture g_TextTexture;
    LTexture g_ScoreTexture;
    
    int g_X = 100;
    
}
