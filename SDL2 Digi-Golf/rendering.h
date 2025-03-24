#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "ball.h"

SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* path);
void renderScene(SDL_Renderer* renderer, const Ball& ball, SDL_Texture* ballTexture);


