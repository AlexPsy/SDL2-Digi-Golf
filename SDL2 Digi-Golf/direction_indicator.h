#pragma once
#include <SDL.h>
#include "ball.h"
#include "constant.h"

class DirectionIndicator {
public:
	void Render(SDL_Renderer* renderer, const Ball& ball) const;
};
