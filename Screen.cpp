//
//  Screen.cpp
//  SDLProject1
//
//  Created by Daniel Davies on 26/02/2020.
//  Copyright © 2020 Daniel Davies. All rights reserved.
//
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Screen.hpp"
#include <iostream>
#include <string>
#include "LTexture.hpp"
#include "Globals.hpp"

namespace dcd{
    
bool Screen::init(){
    
    if( SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL failed to initialize " << SDL_GetError() << std::endl;
        return false;
    }
    
    
    dcd::g_Window = SDL_CreateWindow("Cube Jump v1.2", SDL_WINDOWPOS_UNDEFINED ,SDL_WINDOWPOS_UNDEFINED , SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    
    //checks if window was created successfully
    if(dcd::g_Window == NULL){
        std::cout << "failed to Initialize window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }
    
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        return false;
    }
    
    //Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
        return false;
    }
    
    dcd::g_Renderer = SDL_CreateRenderer(dcd::g_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    
    if(dcd::g_Renderer == NULL){
        std::cout << "failed to Initialize Renderer: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }
    
    return true;
    
}

    
bool Screen::loadMedia(){
    
    //Loading success flag
    bool success = true;
    
    //Load Player texture
    if( !g_PlayerTexture.loadFromFile( "player.png" ) )
    {
        printf( "Failed to load player texture image!\n" );
        success = false;
    }
    //Load Enemy texture
    if( !g_EnemyTexture.loadFromFile( "enemy.png" ) )
    {
        printf( "Failed to load enemy texture image!\n" );
        success = false;
    }
    //load jumper texture
    if( !g_JumperEnemyTexture.loadFromFile( "jumper.png" ) )
    {
        printf( "Failed to load enemy texture image!\n" );
        success = false;
    }
    //Load background texture
    if( !g_BackgroundTexture.loadFromFile( "background.png" ) )
    {
        printf( "Failed to load background texture image!\n" );
        success = false;
    }
    //Load vignette texture
    if( !g_VignetteTexture.loadFromFile( "vignette.png" ) )
    {
        printf( "Failed to load background texture image!\n" );
        success = false;
    }
    else{
        //Set standard alpha blending
        g_VignetteTexture.setBlendMode( SDL_BLENDMODE_MOD );
        //set vignette transparency, higher = more opaque
        g_VignetteTexture.setAlpha(10);
    }
    
    //Open the font
    g_Font = TTF_OpenFont( "Bebas-Regular.ttf", 65 );
    if( g_Font == NULL )
    {
        printf( "Failed to load Bebas-Regular.tf! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    else
    {
        //Render text
        SDL_Color textColor = { 255, 255, 255 };
        if( !g_TextTexture.loadFromRenderedText( "PRESS SPACE TO BEGIN", g_Font, textColor ) )
        {
            printf( "Failed to render text texture!\n" );
            success = false;
        }
        
        if( !g_ScoreTexture.loadFromRenderedText( "0" , g_Font, textColor ) )
        {
            printf( "Failed to render text texture!\n" );
            success = false;
        }
        
    }
    
    return success;
    
    return true;
    
}
    
int Screen::getHeight(){
    return SCREEN_HEIGHT;
}
int Screen::getWidth(){
    return SCREEN_WIDTH;
}

void Screen::close(){
    
    //Free loaded images
    dcd::g_TextTexture.free();
    dcd::g_ScoreTexture.free();

    //Free global font
    TTF_CloseFont( g_Font );
    g_Font = NULL;
    
    //Free loaded images
    dcd::g_PlayerTexture.free();
    dcd::g_BackgroundTexture.free();
    dcd::g_EnemyTexture.free();
    dcd::g_JumperEnemyTexture.free();
    
    //Destroy window
    SDL_DestroyRenderer( dcd::g_Renderer );
    SDL_DestroyWindow( dcd::g_Window );
    dcd::g_Window = NULL;
    dcd::g_Renderer = NULL;
    
    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
    SDL_Quit();
    
}

    
}

