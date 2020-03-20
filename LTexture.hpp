//
//  LTexture.hpp
//  SDLProject1
//
//  Created by Daniel Davies on 09/03/2020.
//  Copyright © 2020 Daniel Davies. All rights reserved.
//

#ifndef LTexture_hpp
#define LTexture_hpp


#include <stdio.h>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
class LTexture {
    
public:
    //Initializes variables
    LTexture();
    
    //Deallocates memory
    ~LTexture();
    
    //Loads image at specified path
    bool loadFromFile( std::string path );
    
    //Creates image from font string
    bool loadFromRenderedText( std::string textureText, TTF_Font *font, SDL_Color textColor );
    
    //Deallocates texture
    void free();
    
    //Set color modulation
    void setColor( Uint8 red, Uint8 green, Uint8 blue );
    
    //Set blending
    void setBlendMode( SDL_BlendMode blending );
    
    //Set alpha modulation
    void setAlpha( Uint8 alpha );
    
    //Renders texture at given point
    void render( double x, double y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip );
    
    //Gets image dimensions
    int getWidth();
    int getHeight();
    
private:
    //The actual hardware texture
    SDL_Texture* m_Texture;
    
    //Image dimensions
    int m_Width;
    int m_Height;
    
};



#endif /* LTexture_hpp */
