//
//  LTexture.cpp
//  SDLProject1
//
//  Created by Daniel Davies on 09/03/2020.
//  Copyright © 2020 Daniel Davies. All rights reserved.
//

#include "LTexture.hpp"
#include "Globals.hpp"
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>

//Initializes variables
LTexture::LTexture(){
    
    m_Texture = NULL;
    
    m_Height = 0;
    m_Width = 0;
    
}

//Deallocates memory
LTexture::~LTexture(){
    free();
}

//Loads image at specified path
bool LTexture::loadFromFile( std::string path ){
    
    //get rid of prexisting texture
    free();
    
    SDL_Texture *new_Texture = NULL;
    
    SDL_Surface* loaded_Surface = IMG_Load( path.c_str() );
    if( loaded_Surface == NULL){
        std::cout << "failed to load IMG from File : " << SDL_GetError() << std::endl;
        return false;
    }
    else {
        //colour key image
        SDL_SetColorKey( loaded_Surface, SDL_TRUE, SDL_MapRGB( loaded_Surface->format, 0, 0xFF, 0xFF ) );
        
        new_Texture = SDL_CreateTextureFromSurface( dcd::g_Renderer, loaded_Surface );
        
        if(new_Texture == NULL){
            std::cout << "failed to create texture from surface : " << SDL_GetError() << std::endl;
            return false;
        }
        else{
            //Get image dimensions
            m_Width = loaded_Surface->w;
            m_Height = loaded_Surface->h;
        }
        //Get rid of old loaded surface
        SDL_FreeSurface( loaded_Surface );
    }
    
    //Return success
    m_Texture = new_Texture;
    return m_Texture != NULL;
    
}

bool LTexture::loadFromRenderedText( std::string textureText, TTF_Font *font, SDL_Color textColor ){
    
    //Get rid of preexisting texture
    free();
    
    //Render text surface
    //blended = slow, solid = v fast, shaded
    SDL_Surface* textSurface = TTF_RenderText_Blended( font, textureText.c_str(), textColor );
    if( textSurface == NULL )
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        m_Texture = SDL_CreateTextureFromSurface( dcd::g_Renderer, textSurface );
        if( m_Texture == NULL )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            m_Width = textSurface->w;
            m_Height = textSurface->h;
        }
        
        //Get rid of old surface
        SDL_FreeSurface( textSurface );
    }
    
    //Return success
    return m_Texture != NULL;
    
}

//Deallocates texture
void LTexture::free(){
    //Free texture if it exists
    if( m_Texture != NULL )
    {
        SDL_DestroyTexture( m_Texture );
        m_Texture = NULL;
        m_Width = 0;
        m_Height = 0;
    }
    
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue ){
    //Modulate texture
    SDL_SetTextureColorMod( m_Texture, red, green, blue );
}

//Set blending
void LTexture::setBlendMode( SDL_BlendMode blending ){
    //Set blending function
    SDL_SetTextureBlendMode( m_Texture, blending );
}

//Set alpha modulation
void LTexture::setAlpha( Uint8 alpha ){
    //Modulate texture alpha
    SDL_SetTextureAlphaMod( m_Texture, alpha );
}

//Renders texture at given point
void LTexture::render( double x, double y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip){
    
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { (int)x, (int)y, m_Width, m_Height };
    
    //Set clip rendering dimensions
    if( clip != NULL )
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    
    //Render to screen
    SDL_RenderCopyEx( dcd::g_Renderer, m_Texture, clip, &renderQuad, angle, center, flip );
    
}

//Gets image dimensions
int LTexture::getWidth(){
    return m_Width;
}

int LTexture::getHeight(){
    
    return m_Height;
    
}

