# jumper
Made in C++ with the following libraries: SDL2, SDL2_Image, SDL2_ttf, soloud(source included)

Build instructions:

Link the following libraries:
 - SDL2
 - SDL_image
 - SDL_ttf
 The required soloud source files areincluded in the project already.
 Depending on your library install locations you may have to change the #include statements
 ( #include "SDL2/SDL.h" to #include "SDL.h" )
 ( #include "SDL2/SDL_ttf.h" to #include "SDL_ttf.h" )
 ( #include "SDL2/SDL_image.h" to #include "SDL_image.h" )
 
Controls: 
Space - jump

Overview:

The player controls a square that must avoid colliding with enemy squares by jumping over them. Enemy squares gradually increase in speed as the game progresses, their direction is randomized. After a while alternate enemy squares will spawn that jump over the player. the game ends when the player square collides with an enemy.

Some technical features of the game include:
 - Lowpass audio filter sweep on death.
 - Vignette overlay texture.
 - Randomized enemy spawning.
 - Original background music.
