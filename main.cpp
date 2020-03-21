//
//  main.cpp
//  SDLProject1
//
//  Created by Daniel Davies on 17/02/2020.
//  Copyright © 2020 Daniel Davies. All rights reserved.

#include <time.h>
#include <iostream>
#include <sstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Globals.hpp"
#include "Screen.hpp"
#include "LTexture.hpp"
#include "Square.hpp"
#include "soloud/soloud.h"
#include "soloud/soloud_wav.h"
#include "soloud/soloud_biquadresonantfilter.h"

#undef main

using namespace std;
using namespace dcd;


int main(){

    SDL_Color textColor = { 255, 255, 255 };
    
    enum directions
    {
        UP,
        DOWN,
        LEFT,
        RIGHT,
    };
    
    const int GROUND = 214;
    
    srand(time(NULL));

    SoLoud::Soloud g_Soloud; // SoLoud engine
    SoLoud::Wav g_JumpSound;      // One wave file
    SoLoud::Wav g_MusicSound;      // One wave file

    SoLoud::BiquadResonantFilter gBQRFilter;

    gBQRFilter.setParams(SoLoud::BiquadResonantFilter::LOWPASS, 21000, 2); 

    g_MusicSound.setFilter(SoLoud::BiquadResonantFilter::LOWPASS, &gBQRFilter);
    
    g_Soloud.init();
    
    g_JumpSound.load("jump.wav");
    g_MusicSound.load("rythm.wav");

    int h = g_Soloud.play(g_MusicSound,0.5);
    g_Soloud.setLooping(h, true);

    Screen screen;
    
    if(screen.init() == false){
        cout << "Error initializing SDL " << endl;
    }
    
    if(screen.loadMedia() == false){
        cout << "Error loading media " <<  endl;
    }
    
 
    SDL_Event event;
    
    //jump variables
    bool pJumping = false;
    
    bool eJumping = false;
    
    int jumpDistance = 80;
    
    //gamestate variables
    bool defeat = false;
    bool quit = false;
    bool start = false;
    
    bool released = true;
   
    //time variables
    int interval = 0;
    int lastTime = 0;
    int elapsed = 0;
    
    
    //enemy variables
    double enemySpeed = 0.4;
    int enemyBaseSpeed = 40;
    bool right = true;
    bool jumper = false;
    bool jumped = false;
    bool pointGiven = false;
    
    //score variables
    
    int score = 0;
    std::ostringstream ScoreStream;
    ScoreStream << "0";
    
    Square player((screen.getWidth()/2) - (g_PlayerTexture.getWidth()/2), GROUND, g_PlayerTexture);
    Square enemy(screen.getWidth(), GROUND, g_EnemyTexture);
    

    //game loop
    while(quit == false){
        
        //determines difficulty ramp and max difficulty
        if(enemyBaseSpeed <= 80){
            enemyBaseSpeed = 30 + ((score - 1)/2);
        }
        
        elapsed = SDL_GetTicks();
        const Uint8 *state = SDL_GetKeyboardState(NULL);
        
        //Handle events on queue, put full screen, pause, sound on/off here

        while( SDL_PollEvent( &event ) != 0 )
        {
            //User requests quit
            if( event.type == SDL_QUIT )
            {
                quit = true;
            }
            
            //player jumping
            if( (state[SDL_SCANCODE_SPACE] && !start) || (state[SDL_SCANCODE_UP] && !start)){
                g_Soloud.play(g_JumpSound);
                start = true;
                score = 0;
                
                g_Soloud.fadeFilterParameter(
                h, // Sound handle
                0,            // First filter
                SoLoud::BiquadResonantFilter::FREQUENCY, // What to adjust
                21000,         // Target value
                1); // Time in seconds
            }
            else if( (state[SDL_SCANCODE_SPACE] && !pJumping && released) || (state[SDL_SCANCODE_UP] && !pJumping  && released)){
                //pressed
                g_Soloud.play(g_JumpSound);
                pJumping = true;
                start = true;
                released = false;
            }
            else if( !state[SDL_SCANCODE_SPACE] && !released){
                //released
                released = true;

            }
            if(pJumping){
              player.jump(GROUND, interval);
            }
            
            
        }
        
        if(pJumping){
            player.jump(GROUND, interval);
        }
        
        if(player.getY() == GROUND){
            pJumping = false;
        }
  
        
        
        //enemy spawn check
        if(!enemy.spawned() && start){
            
            //determine enemy type
            if(score > 5 && rand() % 3 == 0){
                jumper = true;
                enemy.setTexture(g_PlayerTexture);
            }
            
            else{
                jumper = false;
                enemy.setTexture(g_EnemyTexture);
            }
    
            
            //create random delay between spawns. is dependadt on computer speed, needs fix
            if(rand() % 100  == 0){
                pointGiven = false;
                
                enemySpeed = ( (enemyBaseSpeed  + (rand() % 25))/100.0);
                
                jumpDistance = enemySpeed*100 + 50;
                
                right = (rand() % 2) == 1;
                
                if(right){
                    enemy.setPos(screen.getWidth(), GROUND);
                }
                
                else{
                    enemy.setPos(0 - g_EnemyTexture.getWidth(), GROUND);
                }
            }
        }
        
        //enemy movement
        else if(start){
            if(right){
                enemy.move(enemySpeed, LEFT, interval);
            }
    
            if(!right){
                enemy.move(enemySpeed, RIGHT, interval);
            }
        }
        
        
        //enemy jumping
        if ( (right && enemy.getX() < SCREEN_WIDTH/2) || (!right && enemy.getX() > SCREEN_WIDTH/2) ){
            jumped = true;
        }
        else{
            jumped = false;
        }
        
        
        if(jumper){
            if( player.nearby(enemy, jumpDistance) && !eJumping && !jumped) {
                eJumping = true;
                g_Soloud.play(g_JumpSound);
            }
            
            if(eJumping){
                enemy.jump(GROUND, interval);
                
            }
            
            if(enemy.getY() == GROUND){
                eJumping = false;
            }
            
        }
        
        /* AutoRun
        if(!jumper && player.nearby(enemy, jumpDistance) && !pJumping){
            pJumping = true;
        }
        */
        
        //collisions
        if(player.colliding(enemy, true, true)){
            defeat = true;

            g_Soloud.fadeFilterParameter(
            h, // Sound handle
            0,            // First filter
            SoLoud::BiquadResonantFilter::FREQUENCY, // What to adjust
            400,         // Target value
            1); // Time in seconds

        }
    
        if(player.colliding(enemy, false, true) && !pointGiven && !defeat){
            score++;
            pointGiven = true;
        }
        
        //Clear screen
        SDL_SetRenderDrawColor( dcd::g_Renderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( dcd::g_Renderer );
        
        //Render background texture to screen
        dcd::g_BackgroundTexture.render( 0, 0, NULL, 0, 0, SDL_FLIP_NONE );
        
        //Render Enemy to the screen
        if(enemy.spawned() == true){
            enemy.render();
        }
        
        //Render Player to the screen
        if(!defeat){
            player.render();
            if(!start){
                dcd::g_TextTexture.render((screen.getWidth()/2) - (g_TextTexture.getWidth()/2), 90, NULL, 0, 0, SDL_FLIP_NONE);
            }
        }
        
        else if(defeat && !enemy.spawned()){
            player.render();
            defeat = false;
            start = false;
        }
        
        
        //update score
        ScoreStream.str("");
        ScoreStream << (score);
        dcd::g_ScoreTexture.loadFromRenderedText( ScoreStream.str(), g_Font, textColor );
        //render score
        dcd::g_ScoreTexture.render((screen.getWidth()/2) - (g_ScoreTexture.getWidth()/2), 300, NULL, 0, 0, SDL_FLIP_NONE );
        //render vignette
        dcd::g_VignetteTexture.render( 0, 0, NULL, 0, 0, SDL_FLIP_NONE );
        
        
        //Update screen
        SDL_RenderPresent( dcd::g_Renderer );

        //massively reduces cpu usage as no longer refrehsing as fast as possible
        SDL_Delay(3);

        interval = elapsed - lastTime;
        lastTime = elapsed;
        
    }

    g_Soloud.deinit();
    screen.close();
    
    return EXIT_SUCCESS;
    
}
